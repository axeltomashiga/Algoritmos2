#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"

typedef struct nodo{
    struct nodo* izq;
    struct nodo* der;
    void* dato;
    char* clave;    
} nodo_t;

struct abb{
    nodo_t *raiz;
    size_t cantidad;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
    const abb_t* arbol;
    pila_t* pila;
};

nodo_t* nodo_crear(char* clave, void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;

    nodo->izq = NULL;
    nodo->der = NULL;

    nodo->dato = dato;
    nodo->clave = clave;

    return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;
    
    abb->raiz = NULL;
    abb->cantidad = 0;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;

    return abb;
}

bool _abb_guardar(abb_t *arbol, nodo_t* nodo, nodo_t** apuntado, char *clave, void *dato){
    if(!nodo){
        *apuntado = nodo_crear(clave, dato);
        arbol->cantidad++;
        return true;  
    }
    if(arbol->cmp(clave, nodo->clave) < 0){
        return _abb_guardar(arbol, nodo->izq, &nodo->izq, clave, dato);
    } 
    if(arbol->cmp(clave, nodo->clave) > 0){
        return _abb_guardar(arbol, nodo->der, &nodo->der, clave, dato);
    }
    if(arbol->destruir_dato) arbol->destruir_dato(nodo->dato);
    nodo->dato = dato;
    free(clave);
    return true;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    char* copia = strdup(clave);
    if(!copia) return false;

    if(!arbol->raiz){
        nodo_t* nodo = nodo_crear(copia, dato);
        arbol->raiz = nodo;
        arbol->cantidad++;
        return true;   
    }

    if(arbol->cmp(copia, arbol->raiz->clave) < 0) return _abb_guardar(arbol, arbol->raiz->izq, &arbol->raiz->izq, copia, dato);
    if(arbol->cmp(copia, arbol->raiz->clave) > 0) return _abb_guardar(arbol, arbol->raiz->der, &arbol->raiz->der, copia, dato);

    if(arbol->destruir_dato) arbol->destruir_dato(arbol->raiz->dato);
    arbol->raiz->dato = dato;
    free(copia);
    return true;
}


void* eliminar_nodo(abb_t* arbol, nodo_t* borrar, nodo_t* a_borrar_hijo, nodo_t** a_borrar_padre){
    void* aux = borrar->dato;
    free(borrar->clave);
    free(borrar);
    if(a_borrar_hijo){
        *a_borrar_padre = a_borrar_hijo;
    }
    else{
        *a_borrar_padre = NULL;
    }
    return aux;
}

void* buscar_reemplazo(abb_t *arbol, nodo_t* actual, nodo_t** aux_anterior){
    void* dato = actual->dato;
    nodo_t* aux = actual->der;
    nodo_t** anterior = &actual->der;

    while(aux->izq){
        anterior = &aux->izq;
        aux = aux->izq; 
    }

    free(actual->clave);
    actual->clave = strdup(aux->clave);
    if(aux->der){
        actual->dato = eliminar_nodo(arbol, aux, aux->der, anterior);
    }
    else{
        actual->dato = eliminar_nodo(arbol, aux, NULL, anterior);
    }
    return dato;
}

void* _abb_borrar(abb_t *arbol, nodo_t *nodo, nodo_t** anterior, const char *clave){
    if(arbol->cmp(clave, nodo->clave) < 0) return _abb_borrar(arbol, nodo->izq, &nodo->izq, clave);
    if(arbol->cmp(clave, nodo->clave) > 0) return _abb_borrar(arbol, nodo->der, &nodo->der, clave);

    arbol->cantidad--;

    if(!nodo->izq && !nodo->der){
        return eliminar_nodo(arbol, nodo, NULL, anterior);
    }
    else if(!nodo->izq && nodo->der){
        return eliminar_nodo(arbol, nodo, nodo->der, anterior);
    }
    else if(!nodo->der && nodo->izq){
        return eliminar_nodo(arbol, nodo, nodo->izq, anterior);
    }
    else if(nodo->izq && nodo->der){
        return buscar_reemplazo(arbol, nodo, anterior);
    }
    return NULL;
}

void *abb_borrar(abb_t *arbol, const char *clave){
    if(!abb_pertenece(arbol, clave)) return NULL;

    if(arbol->cmp(clave, arbol->raiz->clave) < 0) return _abb_borrar(arbol, arbol->raiz->izq, &arbol->raiz->izq, clave);
    if(arbol->cmp(clave, arbol->raiz->clave) > 0) return _abb_borrar(arbol, arbol->raiz->der, &arbol->raiz->der, clave);
    return _abb_borrar(arbol, arbol->raiz, &arbol->raiz, clave);
}

void *_abb_obtener(const abb_t *arbol, nodo_t* actual, const char* clave) {
    if (arbol->cmp(clave, actual->clave) < 0) {
        return _abb_obtener(arbol,actual->izq,clave);
    }
    if (arbol->cmp(clave, actual->clave) > 0) {
        return _abb_obtener(arbol,actual->der,clave);
    }
    return actual->dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if(!abb_pertenece(arbol, clave)) return NULL;
    return _abb_obtener(arbol, arbol->raiz, clave);
}

bool _abb_pertenece(const abb_t *arbol, nodo_t* actual, const char* clave) {
    if (!actual) {
        return false;
    }
    if (arbol->cmp(clave, actual->clave) < 0) {
        return _abb_pertenece(arbol, actual->izq, clave);
    }
    if (arbol->cmp(clave, actual->clave) > 0) {
        return _abb_pertenece(arbol, actual->der, clave);
    }
    return true;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if(!arbol->raiz) return NULL;
    return _abb_pertenece(arbol, arbol->raiz, clave);
}

size_t abb_cantidad(abb_t *arbol) {
    return arbol->cantidad;
}

void _abb_destruir(abb_t *arbol, nodo_t *actual) {
    if (!actual) {
        return;
    }
    _abb_destruir(arbol,actual->izq);
    _abb_destruir(arbol,actual->der);

    if (arbol->destruir_dato) {
        arbol->destruir_dato(actual->dato);
    }
    free(actual->clave);
    free(actual);
}

void abb_destruir(abb_t *arbol) {
    if(arbol->raiz){
        _abb_destruir(arbol, arbol->raiz);
    }
    free(arbol);
}

//-------------------------------------------------------------------------------------------------------------------------------

bool _abb_in_order(abb_t *arbol, nodo_t* actual, bool visitar(const char *, void *, void *), void *extra){
    if(!actual) return true;

    if(!_abb_in_order(arbol, actual->izq, visitar, extra)) return false;
    if(!visitar(actual->clave, actual->dato, extra)) return false;
    if(!_abb_in_order(arbol, actual->der, visitar, extra)) return false;

    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    if(!arbol) return;
    _abb_in_order(arbol, arbol->raiz, visitar, extra);
}

void _abb_in_order_por_rangos(abb_t *arbol, const char* min, const char* max, nodo_t* actual, bool visitar(const char *, void *, void *), void *extra) {
    
    if (!actual) return;
    
    if (!min || arbol->cmp(actual->clave,min) > 0) {
        _abb_in_order_por_rangos(arbol,min,max,actual->izq,visitar,extra);
    }
    
    if (!min || arbol->cmp(actual->clave,min) >= 0) {
        if(!max || arbol->cmp(actual->clave,max) <= 0){
            visitar(actual->clave,actual->dato,extra);
        }    
    }
    
    if (!max || arbol->cmp(actual->clave,max) < 0) {
        _abb_in_order_por_rangos(arbol,min,max,actual->der,visitar,extra);
    }
    
    return;
}

void abb_in_order_por_rangos(abb_t *arbol, const char* min, const char* max, bool visitar(const char *, void *, void *), void *extra) {
    if (!arbol) return;
    
    _abb_in_order_por_rangos(arbol,min,max,arbol->raiz,visitar,extra);
}

//-------------------------------------------------------------------------------------------------------------------------------
void _apilar_izquierda(nodo_t* nodo, pila_t* pila) {
    if (!nodo) {
        return;
    }
    pila_apilar(pila,(void*)nodo);
    _apilar_izquierda(nodo->izq,pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t *iterador = malloc(sizeof(abb_iter_t));
    if (!iterador) {
        return NULL;
    }
    pila_t* pila = pila_crear();
    if (!pila) {
        free(iterador);
        return NULL;
    }
    iterador->arbol = arbol;
    iterador->pila = pila;
    _apilar_izquierda(arbol->raiz, iterador->pila);
    return iterador;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if(abb_iter_in_al_final(iter)) return false;
    nodo_t* actual = pila_desapilar(iter->pila);
    if(actual->der){
        pila_apilar(iter->pila, actual->der);
        _apilar_izquierda(actual->der->izq, iter->pila);
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    nodo_t* actual = pila_ver_tope(iter->pila);
    if(!actual) return NULL;
    return (const char*) actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}