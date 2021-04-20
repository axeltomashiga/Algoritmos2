#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    void *dato;
    struct nodo *siguiente;
}nodo_t;

struct cola{
    nodo_t *prim;
    nodo_t *ult;
};

cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));
    if(!cola) return NULL;

    cola->prim = NULL;
    cola->ult =NULL;

    return cola;
}

nodo_t *nodo_crear(void *valor){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;

    nodo->dato = valor;
    nodo->siguiente = NULL;

    return nodo;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    while(!cola_esta_vacia(cola)){
        nodo_t *aux = cola->prim;
        cola->prim = cola->prim->siguiente;

        if(destruir_dato){
            destruir_dato(aux->dato);
        }
        
        free(aux);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t *nodo = nodo_crear(valor);
    if(!nodo) return false;

    if(!cola->prim){
        cola->prim = nodo;
        cola->ult = nodo;
        return true;
    }
    cola->ult->siguiente = nodo;
    cola->ult = cola->ult->siguiente;
    return true;
}

void *cola_ver_primero(const cola_t *cola){
    if(cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola){
    if(cola_esta_vacia(cola)) return NULL;

    void *elemento= cola->prim->dato;
    nodo_t *aux = cola->prim;
    cola->prim = cola->prim->siguiente;
    free(aux);

    if(!cola->prim){
        cola->ult = NULL;
    } 

    return elemento;
}