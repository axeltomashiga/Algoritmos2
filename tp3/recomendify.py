#!/usr/bin/python3
import sys
import funciones_tp3
from grafo import Grafo

COMANDOS = ("camino", "mas_importantes", "recomendacion", "ciclo", "rango", "clustering")

def procesar_comandos(texto, datos):
    """
    La función recibe un archivo de texto auxiliar con los comandos a ejecutar, dos grafos de donde se obtendrán las conclusiones 
    y una tupla con datos que serán necesarios dependiendo del comando. Se encarga de ejecutar el comando solicitado linea por línea
    """
    grafo_1 = None
    grafo_2 = None
    pagerank = None

    for linea in texto:
        linea = linea.rstrip('\n').lstrip().split(' ')
        comando = linea.pop(0)
        if comando in (COMANDOS[0],COMANDOS[1],COMANDOS[2]) and grafo_1 is None:
            grafo_1 = hacer_grafo_1(datos)
        if comando in (COMANDOS[3],COMANDOS[4],COMANDOS[5]) and grafo_2 is None:
            grafo_2 = hacer_grafo_2(datos)

        if COMANDOS[0] in comando:
            canciones_camino = ' '.join(linea).split(' >>>> ')
            funciones_tp3.comando_camino_mas_corto(grafo_1, datos[1] ,canciones_camino[0], canciones_camino[1])

        elif COMANDOS[1] in comando:
            if pagerank is None:
                pagerank = funciones_tp3.calcular_pagerank(grafo_1)
            funciones_tp3.comando_canciones_mas_importantes(comando, pagerank, datos[1], int(linea[0]))

        elif COMANDOS[2] in comando:
            tipo_recomendacion = linea.pop(0)
            numero = linea.pop(0)
            canciones_recomendacion = ' '.join(linea).split(' >>>> ')
            funciones_tp3.comando_recomendaciones(comando, grafo_1, datos[1], canciones_recomendacion, tipo_recomendacion, int(numero))
            
        elif COMANDOS[3] in comando:
            numero_ciclo = linea.pop(0)
            cancion_ciclo = " ".join(linea)
            funciones_tp3.comando_ciclo(grafo_2,cancion_ciclo, int(numero_ciclo))

        elif COMANDOS[4] in comando:
            numero_rango = linea.pop(0)
            cancion_rango = " ".join(linea)
            funciones_tp3.comando_rango(grafo_2,int(numero_rango), cancion_rango)

        elif COMANDOS[5] in comando:
            if len(linea) == 0:
                cancion_clustering = None
            else:
                cancion_clustering = " ".join(linea)
            funciones_tp3.comando_clustering(grafo_2,cancion_clustering)
                

def cargar_datos_tsv(archivo_tsv):
    """ 
    Se encarga de procesar los datos del archivo .tsv. La información obtenida servirá para el armado de los grafos y para
    mejorar la rapidez de ciertos comandos en caso de ser necesario. Devuelve 3 elementos:
    
    | lista_datos | --> Se trata de una lista donde se encuentran todas las líneas del archivo tsv. Cada elemento es una cadena
    donde cada campo separado por un \t en el archivo tsv, está separado por un la cadena ' << '
    
    | playlist | --> Es un diccionario con el nombre de las listas de reproducción como claves y una lista de canciones como valor 
    -FORMATO --> { playlist_1: [cancion_1, canción_2], playlist_2 : [canción_3, ... ], ... }
    
    | canciones | ---> Es un conjunto o set() con todas las canciones que aparecen en el archivo

    Devuelve una tupla con los elementos en éste orden --> (lista_datos, canciones, playlist)
    """

    lista_datos = []
    playlist = {}
    canciones = set()
    header = True

    with open(archivo_tsv, "r") as archivo_tsv_e:
        for linea in archivo_tsv_e:
            if header:
                header = False
                continue
            
            parametros = linea.rstrip("\n").split("\t")
            num_id, usuario_id, pista, artista, playlist_num, playlist_nombre, generos = parametros

            playlist.setdefault(f"{playlist_nombre}",[]).append(f"{pista} - {artista}")
            canciones.add(f"{pista} - {artista}")
            lista_datos.append(f"{num_id} >> {usuario_id} >> {pista} >> {artista} >> {playlist_num} >> {playlist_nombre} >> {generos}")

    return lista_datos, canciones, playlist

def hacer_grafo_1(datos):
    """
    Recibe los datos cargados del archivo tsv para armar dos grafos de los cuales se obtendrán las conclusiones en los distintos
    comandos. Se armael grafo 1:
    
    | G1 | --> Es un grafo bipartito no dirigido en el cual hay un grupo con los nombres de las listas de reproducción y otro con 
    los nombres de las canciones y su autor/banda correspondiente. Las canciones que pertenezcan a una determinada lista (O varias
    según sea el caso), estarán conectadas por con una arista
    
    Devuelve G1
    """
    G1 = Grafo(True, False)

    for dato in datos[0]:
        _, usuario_id, pista, artista, _, playlist_nombre, _ = dato.split(' >> ')
        if not G1.esta_vertice(usuario_id):
            G1.agregar_vertice(usuario_id)
        if not G1.esta_vertice(f"{pista} - {artista}"):
            G1.agregar_vertice(f"{pista} - {artista}")
        G1.agregar_arista(usuario_id, f"{pista} - {artista}", playlist_nombre)
    return G1


def hacer_grafo_2(datos):
    """Recibe los datos cargados del archivo tsv para armar dos grafos de los cuales se obtendrán las conclusiones en los distintos
    comandos. Se armael grafo 2:

    | G2 | --> Es un grafo no dirigido donde están conectadas todas las canciones que pertenezcan a una misma lista de reproducción.
    Si una canción aparece en más de una playlist, sus adyacentes serán las canciones de ambas listas de reproducción.
    Devuelve G2"""
    G2 = Grafo(False, False)

    for _, canciones in datos[2].items():
        for cancion in canciones:
            G2.agregar_vertice(cancion)

        for cancion_1 in canciones:
            for cancion_2 in canciones:
                if cancion_1 == cancion_2:
                    continue
                G2.agregar_arista(cancion_1, cancion_2)

    return G2

def recomendify(archivo, comandos):
    datos = cargar_datos_tsv(archivo)
    procesar_comandos(comandos, datos)

recomendify(sys.argv[1], sys.stdin)