#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#define MIN 10

struct heap{
    void** arreglo;
    size_t cantidad;
    size_t tam;
    cmp_func_t cmp;
};

// Intercambia dos posiciones en un arreglo de punteros genéricos
void swap(void* arreglo[], size_t pos_1, size_t pos_2){
    void* aux = arreglo[pos_2];
    arreglo[pos_2] = arreglo[pos_1];
    arreglo[pos_1] = aux;
}

// Dada la posición de un hijo, devuelve la de su padre 
size_t pos_padre(size_t hijo){
    return (hijo-1)/2;
}

// Dada la posición de un padre, devuelve la de su hijo izquierdo
size_t pos_hijo_izq(size_t padre, size_t cantidad){
    if((padre*2) + 1 >= cantidad) return padre;
    return (padre*2) + 1;
}

// Dada la posición de un padre, devuelve la de su hijo derecho
size_t pos_hijo_der(size_t padre, size_t cantidad){
    if((padre*2) + 2 >= cantidad) return padre;
    return (padre*2) + 2;
}

// Devuelve el máximo entre tres elementos de un arreglo 
size_t maximo(void* arreglo[], size_t padre, size_t hijo_izq, size_t hijo_der, cmp_func_t cmp){
    size_t max = (cmp(arreglo[hijo_izq], arreglo[hijo_der]) < 0) ? hijo_der : hijo_izq;

    return (cmp(arreglo[padre], arreglo[max]) < 0) ? max : padre;
}


// Función auxiliar recursiva que intercambia posiciones entre un hijo (Dado por parámetro)
// y su padre. Mientras el hijo sea mayor que su padre, intercambiarán posiciones hasta alcanzar
// la invariante de heap de máximos
void upheap(void* arreglo[], size_t hijo, cmp_func_t cmp){ // heap maximos, encolar
    if(hijo == 0) return;
    size_t padre = pos_padre(hijo);
    if(cmp(arreglo[padre], arreglo[hijo]) < 0){
        swap(arreglo, padre, hijo);
        upheap(arreglo, padre, cmp);
    }
}

// Función auxiliar recursiva que intercambia posiciones entre un padre (Dado por parámetro)
// y sus hijos. Mientras el padre sea menor que el menos prioritario de sus hijos, 
// intercambiarán posiciones hasta alcanzar la invariante de heap de máximos
void downheap(void* arreglo[], size_t cantidad, size_t padre, cmp_func_t cmp){// heap maximos, desencolar
    if(padre == cantidad) return;
    size_t hijo_izq = pos_hijo_izq(padre, cantidad);
    size_t hijo_der = pos_hijo_der(padre, cantidad);

    size_t max = maximo(arreglo, padre, hijo_izq, hijo_der, cmp);
    if(max != padre){
        swap(arreglo, padre, max);
        downheap(arreglo, cantidad, max, cmp);
    }
}

// Ajusta el tamaño del heap a una cantidad dada por parámetro
bool heap_redimensionar(heap_t* heap, size_t nuevo_tam){
    void** nuevo_arreglo = realloc(heap->arreglo, sizeof(void*) * nuevo_tam);
    if(!nuevo_arreglo) return false;

    heap->arreglo = nuevo_arreglo;
    heap->tam = nuevo_tam;

    return true;
}

// Función auxiliar que ordena un arreglo cualquiera para que cumpla la condición de heap de máximos
void heapify_max(void* arreglo[], size_t cantidad, cmp_func_t cmp){
    for(int i = (int)cantidad/2; i >= 0; i--){
        downheap(arreglo, cantidad, i, cmp);
    }
}

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;

    heap->arreglo = malloc(sizeof(void*) * MIN);
    if(!heap->arreglo){
        free(heap);
        return NULL;
    }
    heap->cantidad = 0;
    heap->tam = MIN;
    heap->cmp = cmp;
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;

    heap->arreglo = malloc(sizeof(void*) * n);
    if (!heap->arreglo) {
        free(heap);
        return NULL;
    }
    
    for(size_t i = 0; i < n; i++){
        heap->arreglo[i] = arreglo[i];
    }

    heapify_max(heap->arreglo, n, cmp);

    heap->cantidad = n;
    heap->tam = n;
    heap->cmp = cmp;
    return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if (!heap) {
        return;
    }
    if(destruir_elemento){
        for(size_t i = 0; i < heap->cantidad; i++){
            destruir_elemento(heap->arreglo[i]);
        }
    }
    free(heap->arreglo);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cantidad == 0;
}

bool heap_encolar(heap_t *heap, void *elem){
    if(heap->cantidad == heap->tam){
        if(!heap_redimensionar(heap, heap->tam * 2)) return false;
    }
    heap->arreglo[heap->cantidad] = elem;
    upheap(heap->arreglo, heap->cantidad, heap->cmp);
    heap->cantidad++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;
    return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap) {
    if(heap_esta_vacio(heap)) return NULL;

    void* dato = heap->arreglo[0];
    swap(heap->arreglo, 0, heap->cantidad-1);
    heap->cantidad--;

    if (heap->cantidad * 4 == heap->tam && heap->tam != MIN) {
        heap_redimensionar(heap, heap->tam/2);
    }

    downheap(heap->arreglo, heap->cantidad, 0, heap->cmp);
    return dato;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(!elementos || cant < 2) return;

    heapify_max(elementos, cant, cmp);
    for(int i = (int)(cant - 1); i > 0; i--){
        swap(elementos, 0, i);
        downheap(elementos, i, 0, cmp);
    }
}
