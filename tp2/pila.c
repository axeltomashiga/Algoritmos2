#include "pila.h"

#include <stdlib.h>

#define MIN_CAPACIDAD 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool redimensionar(pila_t *pila, size_t nueva_capacidad);
/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if(pila == NULL) return NULL;

    pila->datos = malloc(sizeof(void*) * MIN_CAPACIDAD);
    if(pila->datos == NULL){
        free(pila);
        return NULL;
    }
    
    pila->cantidad = 0;
    pila->capacidad = MIN_CAPACIDAD;
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    if(pila == NULL) return false;

    if(pila->capacidad == pila->cantidad){
        if(!redimensionar(pila, pila->capacidad * 2)) return false;
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)) return NULL;
    void* elemento = pila->datos[pila->cantidad-1];
    return elemento;
}

void *pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)) return NULL;

    void* elemento = pila->datos[pila->cantidad-1];
    pila->cantidad--;
    
    if(4 * pila->cantidad == pila->capacidad){
       if(pila->capacidad / 2 > MIN_CAPACIDAD){
           redimensionar(pila, pila->capacidad / 2);
       }         
    }
    return elemento;    
}

bool redimensionar(pila_t *pila, size_t nueva_capacidad){
    void **nuevos_datos = realloc(pila->datos, nueva_capacidad * sizeof(void*));

    if(nuevos_datos == NULL) return false;

    pila->datos = nuevos_datos;
    pila->capacidad = nueva_capacidad;

    return true; 
}