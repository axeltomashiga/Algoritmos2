#include "pila.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>


static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();
    // print_test( ... pila_esta_vacia(pila) ... );

    //Una pila recien creada ver_tope y desapilar es invalido(NULL)
    print_test("Se verifica que no se puede desapilar en una pila recien creada", pila_desapilar(pila) == NULL);
    print_test("Se verifica que el tope de una pila vacia sea NULL(invalido)", pila_ver_tope(pila) == NULL);

    //Una pila recien creada esta vacia
    print_test("Se crea la pila y se verifica que este vacía",pila_esta_vacia(pila) == true);

    pila_destruir(pila);
    print_test("La pila de la prueba esta vacia se destruyo", true);
}

static void prueba_apilar(void){
    pila_t *pila = pila_crear();
    //Inicializo un puntero para apilarlo
    int x = 1;
    int* puntero = &x;

    //Apilo un elemento
    print_test("Se apila un elemento y verifico que se apilo", pila_apilar(pila, puntero) == true);
    print_test("Se verifica que no este vacia", pila_esta_vacia(pila) == false);

    //Veo que el tope sea el elemento que apile
    print_test("Verifico que el tope sea igual a lo apilado", *(int*)pila_ver_tope(pila) == 1);

    //Apilar NULL y veo que el nuevo tope sea el NULL
    print_test("Se verifica que se pueda apilar el NULL", pila_apilar(pila, NULL) == true);
    print_test("Se verifica que el nuevo tope sea NULL", pila_ver_tope(pila) == NULL);

    //Apilo otro elemento y verifico que el tope sea el nuevo elemento
    int y = 2;
    int* puntero_2 = &y;
    print_test("Apilo otro elemento y verifico que se apilo", pila_apilar(pila, puntero_2) == true);
    print_test("Verifico que el tope sea igual a lo ultimo apilado", *(int*)pila_ver_tope(pila) == 2); 

    pila_destruir(pila);
    print_test("La pila de la prueba apilar se destruyo", true);
}

static void prueba_desapilar(void){
    pila_t *pila = pila_crear();

    int arreglo[2] = {1,2};

    //Apilo un elemento
    print_test("Verifico que se haya apilado el elemento", pila_apilar(pila, &arreglo[0]));

    //Desapilo el unico elemento apilado y verifico que sea lo mismo que apile
    print_test("Desapilo el unico elemento apilado y se verifica que sea el mismo que se apilo", *(int*)pila_desapilar(pila) == 1);

    //La pila vaciada debe actuar como una pila vacia (ver tope y desapilar invalidas)
    print_test("Verifico que la pila este vacía ya que se desapiló el unico elemento", pila_esta_vacia(pila)==true);
    print_test("Verifico que no se puede desapilar la pila vaciada", pila_desapilar(pila) == NULL);
    print_test("Verifico que la pila vaciada no tiene tope", pila_ver_tope(pila) == NULL);
    print_test("Verifico que se pueda apilar devuleta el elemento", pila_apilar(pila, &arreglo[0]) == true);

    //Apilo un elemento en total 2
    pila_apilar(pila, &arreglo[1]);
    print_test("Desapilo el elemento apilado y se verifica que sea el mismo que se apilo", *(int*)pila_desapilar(pila) == 2);
    print_test("Verifico que el tope sea el elemento que fue apilado anteriormento", *(int*)pila_ver_tope(pila) == 1);

    pila_destruir(pila);
    print_test("La pila de la prueba desapilar se destruyó", true);
}

static void prueba_volumen(void){
    pila_t *pila = pila_crear();
    
    //Declaro un arreglo que seran los valores a apilar y un contador que me ayude con las verificaciones
    int arreglo[100000];
    int indice_arreglo = 99999;

    //Asigno los valores del arreglo
    for(int i = 0; i<100000; i++){
        arreglo[i] = i;
    }
    
    //Declaro booleanos para verificaciones
    bool apilo=false, tope=false;

    //Apilo los valores del arreglo y verifico el tope
    for(int j = 0; j < 100000; j++){
        apilo = pila_apilar(pila, &arreglo[j]);
        tope = (*(int*)pila_ver_tope(pila) == arreglo[j]);
        if(apilo == false || tope == false) break;
    }

    // Verifico que de haya apila y que el tope sea lo mismo que lo apilado
    print_test("Verifico que se haya apilado muchos elementos", apilo == true);
    print_test("Verifico que se el tope funcione como una pila", tope == true);

    //Declaro un booleano para verificar el desapilado
    bool desapilado=false, tope_desapilar=false;

    //Vacio la pila y verifico que este en el orden apilado y el tope cocuerde a lo apilado del indice_arreglo al 0
    while(!pila_esta_vacia(pila)){
        tope_desapilar = (*(int*)pila_ver_tope(pila) == arreglo[indice_arreglo]);
        desapilado = (*(int*)pila_desapilar(pila) == arreglo[indice_arreglo]);
        indice_arreglo--;
        if(desapilado == false) break;
    }

    //Verifico que los desapilados sean igual a los apilados
    print_test("Verifico que lo desapilado concuerde con lo apilado", desapilado == true);
    print_test("Verifico que los topes hayan concordado", tope_desapilar == true);
    print_test("La pila desapilada tiene que estar vacia", pila_esta_vacia(pila) == true);
    
    pila_destruir(pila);
    print_test("La pila de prueba apilar muchos se destruyo", true);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_apilar();
    prueba_desapilar();
    prueba_volumen();
    
    // ...
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
