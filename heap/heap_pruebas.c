#ifndef HEAP_PRUEBAS
#define HEAP_PRUEBAS

#include "testing.h"
#include "heap.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define VOL 20000

int comparacion_numero(const void* a, const void* b){
    if(*(int*)a > *(int*)b) return 1;
    if(*(int*)a == *(int*)b) return 0;
    return -1;
}

int comparacion_pila(const void* a, const void* b){
    if(*(int*)pila_ver_tope((pila_t*)a) > *(int*)pila_ver_tope((pila_t*)b)) return 1;
    if(*(int*)pila_ver_tope((pila_t*)a) == *(int*)pila_ver_tope((pila_t*)b)) return 0;
    return -1;
}

int comparacion_char(const void* a, const void* b){
    return strcmp((char*)a, (char*)b);
}

static void prueba_heap_vacio(){
    printf("PRUEBA HEAP VACIO\n");
    heap_t* heap = heap_crear(comparacion_numero);

    print_test("El heap debe existir", heap);
    print_test("Heap vacio debe ser true", heap_esta_vacio(heap));
    print_test("Heap cantidad es igual a 0", heap_cantidad(heap) == 0);
    print_test("Heap ver max debe ser NULL", heap_ver_max(heap) == NULL);
    print_test("Heap desencolar debe ser NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);
    printf("\n");
}

static void prueba_heap_encolar(){
    printf("PRUEBA HEAP ENCOLAR\n");
    heap_t* heap = heap_crear(comparacion_numero);

    size_t arreglo[5];
    arreglo[0] = 100;
    arreglo[1] = 50;
    arreglo[2] = 30;
    arreglo[3] = 450;
    arreglo[4] = 310;
    bool ok = true;

    for(int i = 0; i < 5; i++){
        ok = heap_encolar(heap, &arreglo[i]);
        if(!ok) break;
    }    
    print_test("Se pudo encolar los datos", ok);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Heap maximo es 450", *(int*)heap_ver_max(heap) == 450);
    print_test("Heap cantidad es 5", heap_cantidad(heap) == 5);

    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);
    printf("\n");
}

static void prueba_heap_desencolar(){
    printf("PRUEBA HEAP DESENCOLAR\n");
    heap_t* heap = heap_crear(comparacion_numero);

    size_t arreglo[5];
    arreglo[0] = 100;
    arreglo[1] = 50;
    arreglo[2] = 30;
    arreglo[3] = 450;
    arreglo[4] = 310;

    for(int i = 0; i < 5; i++){
        heap_encolar(heap, &arreglo[i]);
    }
    print_test("Heap cantidad es 5", heap_cantidad(heap) == 5);
    print_test("Heap maximo es correcto", *(int*)heap_ver_max(heap) == 450);
    print_test("Heap desencolar es el maximo", *(int*)heap_desencolar(heap) == 450);
    print_test("Heap cantidad es 4", heap_cantidad(heap) == 4);
    print_test("Heap maximo es correcto", *(int*)heap_ver_max(heap) == 310);
    print_test("Heap desencolar es el maximo", *(int*)heap_desencolar(heap) == 310);
    print_test("Heap cantidad es 3", heap_cantidad(heap) == 3);
    print_test("Heap maximo es correcto", *(int*)heap_ver_max(heap) == 100);
    print_test("Heap desencolar es el maximo", *(int*)heap_desencolar(heap) == 100);
    print_test("Heap cantidad es 2", heap_cantidad(heap) == 2);
    print_test("Heap maximo es correcto", *(int*)heap_ver_max(heap) == 50);
    print_test("Heap desencolar es el maximo", *(int*)heap_desencolar(heap) == 50);
    print_test("Heap cantidad es 1", heap_cantidad(heap) == 1);
    print_test("Heap maximo es correcto", *(int*)heap_ver_max(heap) == 30);
    print_test("Heap desencolar es el maximo", *(int*)heap_desencolar(heap) == 30);
    print_test("Heap cantidad es 0", heap_cantidad(heap) == 0);

    print_test("Heap maximo en heap vaciado es NULL", heap_ver_max(heap) == NULL);
    print_test("Heap desencolar en heap vaciado es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);
    printf("\n");
}

static void prueba_crear_arreglo() {
    printf("PRUEBA CREAR ARREGLO\n");
    // Creo un arreglo de 5 elementos
    int arreglo[5] = {2,3,1,5,4};
    void** elementos = malloc(sizeof(void*) * 5);
    for(int i = 0; i < 5; i++){
        elementos[i] = &arreglo[i];
    }
    // Creo un heap a partir de ese arreglo
    heap_t *heap = heap_crear_arr(elementos, 5, comparacion_numero);

    print_test("El heap fue creado a partir de un arreglo",heap);
    print_test("El heap no está vacío",!heap_esta_vacio(heap));
    print_test("El máximo del heap es el máximo del arreglo",*(int*)heap_ver_max(heap) == 5);
    print_test("La cantidad coincide con el tamaño del arreglo",heap_cantidad(heap) == 5);
    print_test("Desencolar da el maximo", *(int*)heap_desencolar(heap) == 5);
    print_test("La cantidad coincide con el tamaño del arreglo", heap_cantidad(heap) == 4);
    print_test("El máximo del heap cambia",*(int*)heap_ver_max(heap) == 4);

    heap_destruir(heap,NULL);
    print_test("Heap destruido", true);
    free(elementos);
    printf("\n");
}

void destruccion_pila(void* e){
    pila_destruir((pila_t*)e);
}

static void prueba_destruccion_datos() {
    printf("PRUEBA CON DESTRUCCION DE DATOS\n");
    heap_t *heap_pila = heap_crear(comparacion_pila);
    // Encolo pilas alojadas en memoria dinámica
    int arreglo[3];

    for(int i = 0;i<3;i++) {
        arreglo[i] = i;
    }

    pila_t* pila_1 = pila_crear();
    pila_t* pila_2 = pila_crear();
    pila_t* pila_3 = pila_crear();

    pila_apilar(pila_1, &arreglo[0]);
    pila_apilar(pila_2, &arreglo[1]);
    pila_apilar(pila_3, &arreglo[2]);

    print_test("Encolo pila",heap_encolar(heap_pila, pila_1));
    print_test("Encolo pila",heap_encolar(heap_pila, pila_2));
    print_test("Encolo pila",heap_encolar(heap_pila, pila_3));
    print_test("El maximo es la ultima pila", (pila_t*)heap_ver_max(heap_pila) == pila_3);
    print_test("La cantidad del heap es 3", heap_cantidad(heap_pila) == 3);

    // Libero con pila_destruir
    heap_destruir(heap_pila, destruccion_pila);
    print_test("Heap destruido con destruccion de pilas", true);

    // Encolo cadenas alojadas en la pila de llamadas
    heap_t *heap_cadena = heap_crear(comparacion_char);
    
    char* cadena_1 = "AGUA";
    char* cadena_2 = "HACHA";
    char* cadena_3 = "ZORRO";

    print_test("Encolo cadena_1",heap_encolar(heap_cadena, cadena_1));
    print_test("Encolo cadena_2",heap_encolar(heap_cadena, cadena_2));
    print_test("Encolo cadena_3",heap_encolar(heap_cadena, cadena_3));

    print_test("El maximo es la ultima cadena", (char*)heap_ver_max(heap_cadena) == cadena_3);
    print_test("La cantidad del heap es 3", heap_cantidad(heap_cadena) == 3);
    print_test("Desencolo", heap_desencolar(heap_cadena));
    print_test("El maximo es la penúltima cadena", (char*)heap_ver_max(heap_cadena) == cadena_2);
    print_test("La cantidad del heap es 2", heap_cantidad(heap_cadena) == 2);
    print_test("Desencolo", heap_desencolar(heap_cadena));

    heap_destruir(heap_cadena,NULL);
    print_test("Heap destruido sin función de destrucción", true);
    printf("\n");
}

static void prueba_volumen_heap() {
    printf("PRUEBA VOLUMEN\n");
    heap_t *heap = heap_crear(comparacion_numero);

    int numeros[VOL];
    bool encolar = true;

    for (int i = 0; i < VOL; i++) {
        numeros[i] = i;
        if (!heap_encolar(heap, &numeros[i])){
            encolar = false;
            break;
        }
    }

    print_test("El heap encolo correctamente", encolar);
    print_test("El heap tiene VOL elementos",heap_cantidad(heap) == VOL);
    print_test("El máximo es correcto",*(int*)heap_ver_max(heap) == VOL - 1);
    print_test("El heap no está vacío",!heap_esta_vacio(heap));
    
    bool desencolar = true;
    for (size_t j = 0; j < VOL; j++) {
        if (*(int*)heap_ver_max(heap) != VOL - j - 1) {
            desencolar = false;
            break;
        }
        if(*(int*)heap_desencolar(heap) != VOL - j - 1){
            desencolar = false;
            break;
        }
    }

    print_test("Se desencolo correctamente", desencolar);
    print_test("El heap ahora está vacío",heap_esta_vacio(heap));
    print_test("No se puede seguir desencolando",!heap_desencolar(heap));
    print_test("Se puede seguir encolando",heap_encolar(heap, &numeros[2]));
    print_test("El heap ya no está vacío",!heap_esta_vacio(heap));
    print_test("El heap tiene la cantidad correcta",heap_cantidad(heap) == 1);

    heap_destruir(heap,NULL);
    print_test("Heap destruido", true);
    printf("\n");
}

static void prueba_heapsort(){
    printf("PRUEBA HEAPSORT\n");
    int numeros[7] = {7,1,2,3,30,10,80};
    void* arreglo[7];

    for(int i = 0; i < 7; i++){
        arreglo[i] = &numeros[i];
    }

    heap_sort(arreglo, 7, comparacion_numero);

    for(int i = 0; i < 7; i++){
        printf("%d ,", *(int*)arreglo[i]);
    }
    print_test("De un arreglo desordenado, lo ordena de menor a mayor", true);

    int numeros_2[9] = {7,1,20,2,30,10,150,66,100};
    void* arreglo_2[9];

    for(int i = 0; i < 9; i++){
        arreglo_2[i] = &numeros_2[i];
    }

    heap_sort(arreglo_2, 9, comparacion_numero);

    for(int i = 0; i < 9; i++){
        printf("%d ,", *(int*)arreglo_2[i]);
    }
    print_test("De un arreglo desordenado, lo ordena de menor a mayor", true);

    printf("\n");
}

void pruebas_heap_estudiante(){
    prueba_heap_vacio();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_crear_arreglo();
    prueba_destruccion_datos();
    prueba_volumen_heap();
    prueba_heapsort();
}

#ifndef CORRECTOR  

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  
}

#endif
#endif


