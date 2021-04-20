from grafo import Grafo
from collections import deque
import random
import heapq

def lista_camino_mas_corto(padres, v):
    """Crea el recorrido atraves del diccionario padres devolviendolo en forma de lista"""
    recorrido = []
    while padres[v] != None:
        recorrido.append(v)
        v = padres[v]
    return recorrido

def recorrido_bfs(grafo, origen, destino, n):
    """Realiza un recorrido bfs sobre el grafo correspondiente, esta funcion se utilizara tanto para el comando camino
    y para el comando rango"""
    visitados = set()
    orden = {}
    padres = {}
    rango = 0
    recorrido = []
    orden[origen] = 0
    padres[origen] = None
    visitados.add(origen)
    cola = deque()
    cola.append(origen)

    while not len(cola) == 0:
        v = cola.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados and destino is None:
                orden[w] = orden[v] + 1
                if orden[w] == n:
                    rango += 1
                if orden[w] > n:
                    return rango, recorrido
                cola.append(w)    
            elif w not in visitados and n is None:
                padres[w] = v
                cola.append(w)
                if w == destino:
                    recorrido = lista_camino_mas_corto(padres, w)
                    return rango, recorrido
            visitados.add(w)
    return rango, recorrido

def comando_camino_mas_corto(grafo, canciones, origen, destino):
    """Ejecuta el comando camino e imprime por la pantalla el recorrido mas corto
    entre una cancion origen a otra cancion destino"""

    if origen not in canciones or destino not in canciones:
        print("Tanto el origen como el destino deben ser canciones")
    else:
        _,recorrido = recorrido_bfs(grafo, origen, destino, None)
        if(len(recorrido) < 2):
            print("No se encontro recorrido")
        else:
            usuario = recorrido.pop()
            cancion = recorrido.pop()
            
            print(f"{origen} --> aparece en playlist --> {grafo.peso_arista(origen, usuario)} --> de --> {usuario} --> tiene una playlist --> {grafo.peso_arista(usuario, cancion)} --> donde aparece --> {cancion}", end ="")

            while len(recorrido)!=0:
                usuario = recorrido.pop()
                print(f" --> aparece en playlist --> {grafo.peso_arista(cancion, usuario)} --> de --> {usuario}", end ="")
                cancion = recorrido.pop()
                print(f" --> tiene una playlist --> {grafo.peso_arista(usuario, cancion)} --> donde aparece --> {cancion}", end ="")
            print()

def comando_rango(grafo, rango, cancion):
    """Ejecuta el comando rango e imprime el resultado de cunatas canciones hay a cierta cancion origen"""
    rango, _ = recorrido_bfs(grafo, cancion, None, rango)
    print(rango)

def filtro_pagerank(pagerank, comando, tipo_recomendacion ,canciones, cantidad):
    """Filtra y ordena los pagerank ya sea del comando mas_importantes o recomendacion,
    en caso de recomenendacion se tendra en cuenta que tipo de recomedacion hace si usuarios o canciones"""
    pagerank_canciones = {}
    pagerank_usuarios = {}
    for clave, valor in pagerank.items():
        if clave in canciones:
            pagerank_canciones[clave] = valor
        else:
            pagerank_usuarios[clave] = valor
    if comando == "mas_importantes" or comando == "recomendacion" and tipo_recomendacion == "canciones":
        return heapq.nlargest(cantidad, pagerank_canciones, key=pagerank_canciones.get)
    else:
        return heapq.nlargest(cantidad, pagerank_usuarios, key=pagerank_usuarios.get)

def calcular_pagerank(grafo):
    """Realiza el algoritmo de pagerank para saber cuales de las canciones son las mas importantes"""
    d = 0.85
    vertices_total = grafo.obtener_vertices()
    n = len(vertices_total)
    pagerank_total = {}
    pagerank_aux = {}
    sumatoria = {}
 
    for v in vertices_total:
        pagerank_total[v] = 1
           
    for _ in range(20):
        for v in vertices_total:
            sumatoria[v] = 0

        for v in vertices_total:
            for w in grafo.adyacentes(v):
                sumatoria[w] += pagerank_total[v]/len(grafo.adyacentes(v))

        for v in vertices_total:
            pagerank_aux[v] = (1 - d / n) + (d * sumatoria[v])
        
        pagerank_total = pagerank_aux
                
    return pagerank_total


def comando_canciones_mas_importantes(comando, pagerank, canciones, cantidad_importantes):
    """Ejecuta el comando mas_importantes, e imprime las canciones mas importantes de acuerdo al cantidad ingresado"""
    i = 0
    importantes = filtro_pagerank(pagerank, comando, None, canciones, cantidad_importantes)
    while i < cantidad_importantes and len(importantes) != 0:
        if i > 0:
            print("; ", end="") 
        i += 1
        cancion = importantes.pop(0)
        print(f"{cancion}", end="")
    print()

def page_rank_personalizado(grafo, dato_canciones, vertice, page_rank_per, pg_act ,limite):
    """Algortimo de pagerank personalizado con una simulacion de randomwalk"""
    if limite == 200:
        return

    adyacentes = grafo.adyacentes(vertice)
    pg_act /= len(adyacentes)

    w = random.choice(adyacentes)
    page_rank_per[w] += pg_act

    page_rank_personalizado(grafo, dato_canciones, w, page_rank_per, pg_act ,limite+1)
    

def comando_recomendaciones(comando, grafo, canciones, vertices, tipo_recomendacion, cantidad_recomendaciones):
    """Ejecuta el comando recomendaciones imprimiendo el resultados dependiendo del tipo (canciones o usuarios) y la cantidad"""
    page_rank_per = {}
    i=0

    for v in grafo.obtener_vertices():
        page_rank_per[v] = 0

    for _ in range(100):
        v = random.choice(vertices)
        page_rank_personalizado(grafo, canciones, v ,page_rank_per, 1, 0)
        
    for v in vertices:
        if v in page_rank_per:
            page_rank_per.pop(v)

    if tipo_recomendacion == "usuarios":
        lista_usuarios = filtro_pagerank(page_rank_per, comando, tipo_recomendacion, canciones, cantidad_recomendaciones)
        if len(lista_usuarios) < cantidad_recomendaciones:
            print("No hay recomendaciones")
        else:
            while i < cantidad_recomendaciones and len(lista_usuarios) != 0:
                if i > 0:
                    print("; ", end="") 
                print(f"{lista_usuarios.pop(0)}", end="")
                i+=1
    
    elif tipo_recomendacion == "canciones":
        lista_canciones = filtro_pagerank(page_rank_per, comando, tipo_recomendacion, canciones, cantidad_recomendaciones)
        if len(lista_canciones) < cantidad_recomendaciones:
            print("No hay recomendaciones")
        while i < cantidad_recomendaciones and len(lista_canciones) != 0:
            if i > 0:
                print("; ", end="") 
            print(f"{lista_canciones.pop(0)}", end="")
            i+=1
    print()

def _camino_hamiltoniano(grafo, origen, vertice, visitados, camino, largo):
    """Realiza el algoritmo camino hamiltoniano para encontrar un ciclo de n canciones a una cancion origen"""
    visitados.add(vertice)
    camino.append(vertice)
    if len(camino) == largo and grafo.estan_unidos(vertice,origen):
        return True
    if len(camino) > largo:
        visitados.remove(vertice)
        camino.pop()
        return False
    for w in grafo.adyacentes(vertice):
        if w not in visitados:
            if _camino_hamiltoniano(grafo,origen,w,visitados,camino,largo):
                return True
    visitados.remove(vertice)
    camino.pop()
    return False

def comando_ciclo(grafo, cancion, largo):
    """Ejecuta el comando ciclo e imprime el recorrido"""
    camino = []
    visitados = set()
    if _camino_hamiltoniano(grafo,cancion,cancion,visitados,camino,largo):
        cadena_final = f"{cancion}"
        for cancion_camino in camino[1::]:
            cadena_final += f" --> {cancion_camino}"
        print(cadena_final + f" --> {cancion}")
    else:
        print("No se encontro recorrido")

def calculo_cluster_vertice(grafo, vertice):
    """Calculo del Cluster con vertice especifico"""
    k = 0 
    c = 0
    adyacentes = grafo.adyacentes(vertice)
    k = len(adyacentes)

    if k < 2:
        return float(0)
    
    for ady_1 in adyacentes:
        for ady_2 in adyacentes:
            if ady_1 == ady_2:
                continue
            if grafo.estan_unidos(ady_1, ady_2):
                c += 1
    return (c)/(k*(k-1))

def calculo_cluster_grafo(grafo):
    """Calculo del Cluster sin vertice especifico"""
    C = 0
    n = len(grafo.obtener_vertices())
    for v in grafo.obtener_vertices():
        C += calculo_cluster_vertice(grafo,v)
    return float(C/n)
    
def comando_clustering(grafo, vertice):
    """Ejecuta el comando clustering e imprime el resultado"""
    if vertice is not None:
        print("{0:.3f}".format(calculo_cluster_vertice(grafo, vertice)))
    else:
        print("{0:.3f}".format(calculo_cluster_grafo(grafo)))