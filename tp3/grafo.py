import random

class Grafo():
    def __init__(self, es_pesado = False, es_dirigido = False):
        """Simulacion de grafo, la matriz depndera si es pesado y/o dirigido
        en caso de pesado sera un diccionario de diccionarios y el segundo
        diccionario tendra el vertice conectado como clave y valor el peso
        caso contrario sera una lista de vertices, tambien si es dirigido
        solo se garega el vertice y si no es dirigido se agragan los dos 
        con sus respectivos adyacentes"""
        self.matriz = {}
        self.es_pesado = es_pesado
        self.es_dirigido = es_dirigido

    def agregar_vertice(self, vertice):
        """Agrega vertice si no esta en la matriz"""
        if vertice not in self.matriz:
            if not self.es_pesado:
                self.matriz[vertice] = []
            elif self.es_pesado:
                self.matriz[vertice] = {}

    def borrar_vertice(self, vertice):
        """Borra el verice completo vertice si no esta en la matriz"""
        if not self.es_dirigido:
            if not self.es_pesado:
                for w in self.matriz[vertice]:
                    self.matriz[w].remove(vertice)
            elif self.es_pesado:
                for w in self.matriz[vertice]:
                    self.matriz[w].remove(vertice)
        self.matriz.pop(vertice, None)

    def esta_vertice(self, v):
        """Verificacion si se encuentra un vertice"""
        return v in self.matriz

    def agregar_arista(self, v, w, peso=None):
        """Agrega arista"""
        if not self.es_pesado and peso is not None:
            raise ValueError("Un grafo no pesado no puede admitir peso")
        if w not in self.matriz[v]:
            if not self.es_pesado:
                self.matriz[v].append(w)
                if not self.es_dirigido:
                    self.matriz[w].append(v)
            elif self.es_pesado:
                self.matriz[v][w] = peso
                if not self.es_dirigido:
                    self.matriz[w][v] = peso
    
    def borrar_arista(self, v, w):
        """Borra arista"""
        for e in self.matriz[v]:
            if e.vertice_w == w:
                self.matriz[v].remove(e)
                break

        if not self.es_dirigido:
            for e in self.matriz[w]:
                if e.vertice_w == v:
                    self.matriz[w].remove(e)
                    break
        
    def peso_arista(self, v, w):
        """Devuelve el peso de una arista de v a w"""
        return self.matriz[v][w]

    def obtener_vertices(self):
        """"Devuelve una lista de vertices"""
        return list(self.matriz.keys())

    def adyacentes(self, vertice):
        """Devuelve una lista de una vertices adyacentes a v"""
        if vertice in self.matriz:
            if self.es_pesado:
                return list(self.matriz[vertice].keys())
            else:
                return self.matriz[vertice]
        return []

    def vertice_aleatorio(self):
        """Devuelve un vertice random del grafo"""
        numero = random.randint(0, len(self.matriz)-1)
        vertices_total = list(self.matriz.keys())
        return vertices_total[numero]
    
    def estan_unidos(self, v1, v2):
        """verifico si v y w estan unidos por una arista"""
        return v2 in self.matriz[v1]

    def __str__(self):
        return f"{self.matriz}"