#include "cola.h"
#include "testing.h"
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>

// void pila_destruir(void *pila);

static void prueba_cola_vacia(void){
    printf("INICIO PRUEBA COLA VACIA:\n");
    cola_t *cola = cola_crear();
    
    print_test("Pruebo que esta vacia", cola_esta_vacia(cola));
    print_test("Pruebo que desencolar en cola vacia es igual a NULL", cola_desencolar(cola) == NULL);
    print_test("Pruebo ver primero en cola vacia es igual a NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
    print_test("La cola de cola vacia fue destruida", true);
    printf("\n");
}

static void prueba_encolar(void){
    printf("INICIO PRUEBA COLA ENCOLAR:\n");
    cola_t *cola = cola_crear();
    int a = 5;
    int b = 1;
    print_test("Pruebo que la cola este vacia", cola_esta_vacia(cola));
    print_test("Pruebo que se pueda encolar NULL", cola_encolar(cola, NULL));
    print_test("Pruebo que la cola no este vacia", !cola_esta_vacia(cola));
    print_test("Pruebo que se pueda encolar un elemento", cola_encolar(cola, &a));
    print_test("Pruebo que ver primero sea el elemento encolado", cola_ver_primero(cola) == NULL);
    print_test("Pruebo que se pueda encolar otro elemento", cola_encolar(cola, &b));
    print_test("Pruebo que ver primero sea igual al primer elemento encolado", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
    print_test("La cola de prueba encolar fue destuida", true);
    printf("\n");
}

static void prueba_desencolar(void){
    printf("INICIO DE PRUEBA DESENCOLAR:\n");
    cola_t *cola = cola_crear();
    int a = 3;
    int b = 2;
    int c = 5;

    print_test("Pruebo que la cola este vacia", cola_esta_vacia(cola));
    cola_encolar(cola, &a);
    cola_encolar(cola, &b);
    cola_encolar(cola, &c);    
    print_test("Pruebo que el elemento desencolado sea el primero encolado", *(int*)cola_desencolar(cola) == a);
    print_test("Pruebo que el ver primero sea el segundo elemento encolado", *(int*)cola_ver_primero(cola) == b);
    
    while(!cola_esta_vacia(cola)){
        cola_desencolar(cola);
    }
    print_test("Preubo que la cola se vacio", cola_esta_vacia(cola));
    print_test("Pruebo que la cola vaciada ver primero es igual a NULL", cola_ver_primero(cola) == NULL);
    print_test("Pruebo que la cola vaciada desencolar es igual a NULL", cola_desencolar(cola) == NULL);
    print_test("Pruebo que se pueda encolar nuevamente", cola_encolar(cola, &a));
    
    cola_destruir(cola, NULL);
    print_test("La cola de prueba desencolar fue destruida", true);
    printf("\n");
}

static void prueba_volumen(void){
    printf("INICIO DE PRUEBA VOLUMEN:\n");
    cola_t *cola = cola_crear();
    int arreglo[10000];
    
    for(int i = 0; i < 10000; i++){
        arreglo[i] = i;
    }
    
    print_test("Pruebo que la cola este vacia", cola_esta_vacia(cola));

    for(int j = 0; j < 10000; j++){
        cola_encolar(cola, &arreglo[j]);
    }

    print_test("Pruebo que la cola no este vacia", !cola_esta_vacia(cola));

    bool desencolado = false;
    bool primero_desencolado = false;
    int indice = 0;

    while(!cola_esta_vacia(cola)){
        primero_desencolado = (*(int*)cola_ver_primero(cola) == arreglo[indice]);
        desencolado = (*(int*)cola_desencolar(cola) == arreglo[indice]);
        if(primero_desencolado == false || desencolado == false) break;
        indice++;
    }

    print_test("Pruebo que el orden de la cola sea correcto, el primero de la cola es el primero del arreglo", primero_desencolado);
    print_test("Pruebo que lo desencolado esten en el orden de lo encolado el primero de la cola es el primero del arreglo", desencolado);
    print_test("Pruebo que la cola este vacia", cola_esta_vacia(cola));
    
    cola_destruir(cola, NULL);
    print_test("La cola de prueba desencolar fue destruida", true);
    printf("\n");
}

static void prueba_destruir_con_funcion(void){
    printf("INICIO DE PRUEBA DESTRUIR CON FUNCION:\n");
    cola_t *cola = cola_crear();
    int arreglo[10];
    
    pila_t *pila = pila_crear();
        
    print_test("Pruebo que la cola este vacia", cola_esta_vacia(cola));

    for(int i = 0; i < 10; i++){
        arreglo[i] = i;
    }

    for(int j = 0; j < 10; j++){
        pila_apilar(pila, &arreglo[j]);
    }

    print_test("Pruebo que se pueda encolar una pila", cola_encolar(cola, pila));
    print_test("Pruebo que la cola no este vacia", !cola_esta_vacia(cola));
    

    cola_destruir(cola, (void (*)(void*))pila_destruir);
    print_test("La cola de prueba destruir y la pila fueron destruidas", true);
    printf("\n");
}

static void prueba_destruir_free(void){
    printf("INICIO DE PRUEBA DESTRUIR CON FREE\n");
    cola_t *cola = cola_crear();
    int *arreglo = malloc(sizeof(int) * 10);
    
    for(int i = 0; i < 10; i++){
        arreglo[i] = i;
    }

    print_test("Pruebo que la cola esta vacia", cola_esta_vacia(cola));
    print_test("Pruebo que se encole el arreglo", cola_encolar(cola, arreglo));
    print_test("Pruebo que la cola no este vacia", !cola_esta_vacia(cola));
    
    cola_destruir(cola, free);

    print_test("La cola fue destruida", true);
    printf("\n");
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_encolar();
    prueba_desencolar();
    prueba_volumen();
    prueba_destruir_con_funcion();
    prueba_destruir_free();
    
    // ...
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
