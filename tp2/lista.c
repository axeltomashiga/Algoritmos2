#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_lista_t;

struct lista{
    nodo_lista_t* prim;
    nodo_lista_t* ult;
    size_t largo;
};

struct lista_iter{
    nodo_lista_t* ant;
    nodo_lista_t* act;
    lista_t* lista;
};

//IMPLEMENTACION LISTA
lista_t *lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;

    return lista;
}

nodo_lista_t* nodo_lista_crear(void *valor){
    nodo_lista_t *nodo = malloc(sizeof(nodo_lista_t));
    if(!nodo) return NULL;
    
    nodo->dato = valor;
    nodo->prox = NULL;

    return nodo;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_lista_t* nodo = nodo_lista_crear(dato);
    if(!nodo) return false;

    if(!lista->prim){
        lista->ult = nodo;
    } else {
        nodo->prox = lista->prim;
    }

    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_lista_t* nodo = nodo_lista_crear(dato);
    if(!nodo) return false;

    if(!lista->prim){
        lista->prim = nodo;
        lista->ult = nodo;
    } else {
        lista->ult->prox = nodo;
        lista->ult = lista->ult->prox;
    }

    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(!lista->prim) return NULL;
    nodo_lista_t* aux = lista->prim;
    void* elemento = lista->prim->dato;

    lista->prim = lista->prim->prox;
    
    if(lista->prim == NULL){
        lista->ult = NULL;
    }
    
    free(aux);
    lista->largo--;

    return elemento;
}

void *lista_ver_primero(const lista_t *lista){
    if(!lista->prim) return NULL;
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    if(!lista->ult) return NULL;
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while(!lista_esta_vacia(lista)){
        nodo_lista_t* aux = lista->prim;

        if(destruir_dato){
            destruir_dato(aux->dato);
        }

        lista->prim = lista->prim->prox;
        free(aux);
    }
    free(lista);
}

//ITERADOR INTERNO
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_lista_t* aux = lista->prim;
    while(aux && visitar(aux->dato, extra)){
        aux = aux->prox;
    }
}

//ITERADOR EXTERNO
lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(!iter) return NULL;

    iter->ant = NULL;
    iter->act = lista->prim;
    iter->lista = lista;
    
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(!iter->act) return false;

    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(!iter->act) return NULL;
    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_lista_t* nodo = nodo_lista_crear(dato);
    if(!nodo) return false;

    if(!iter->ant){
        iter->lista->prim = nodo;
    }

    if(!iter->act){
        iter->lista->ult = nodo;
    }

    if(iter->ant){
        iter->ant->prox = nodo;
    }

    nodo->prox = iter->act;
    iter->act = nodo;
    iter->lista->largo++;
    return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
    if(iter->act == NULL) return NULL;

    nodo_lista_t* aux = iter->act;
    void* elemento = iter->act->dato;

    if(!iter->act->prox){
        iter->lista->ult = iter->ant;
    }

    if(!iter->ant){
        iter->lista->prim = aux->prox;
    }

    if(iter->ant){
        iter->ant->prox = iter->act->prox;
    }

    iter->act = iter->act->prox;
    free(aux);
    iter->lista->largo--;
    return elemento;
}