#include "lista.h"
#include "pila.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#define MAX_VOL 10000

static void prueba_lista_vacia(void){
    printf("INICIO DE LA PRUEBA LISTA VACIA\n");
    lista_t* lista = lista_crear();
    print_test("Pruebo que la lista creada este vacia", lista_esta_vacia(lista));
    print_test("Pruebo que ver primero la lista vacia devuelva NULL", lista_ver_primero(lista) == NULL);
    print_test("Pruebo que ver ultimo la lista vacia devuelva NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Pruebo que borrar primero la lista vacia devuelva NULL", lista_borrar_primero(lista) == NULL);
    print_test("Pruebo que largo de la lista vacia sea 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
    print_test("La lista de prueba lista vacia fue destruida", true);
    printf("\n");
}

static void prueba_lista_insertar(void){
    printf("INICIO DE LA PRUEBA LISTA INSERTAR\n");
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 3;
    print_test("Pruebo que la lista creada este vacia", lista_esta_vacia(lista));
    print_test("Pruebo que insertar primero la lista agregue el elemento", lista_insertar_primero(lista, &a));
    print_test("Pruebo que la lista no este vacia", !lista_esta_vacia(lista));
    print_test("Pruebo que ver primero la lista sea el elemento insertado", *(int*)lista_ver_primero(lista) == a);
    print_test("Pruebo que ver ultimo la lista sea el elemento insertado", *(int*)lista_ver_ultimo(lista) == a);

    print_test("Pruebo que insertar primero la lista agregue el elemento", lista_insertar_primero(lista, &b));
    print_test("Pruebo que ver primero sea el nuevo elemento agregado", *(int*)lista_ver_primero(lista) == b);
    print_test("Pruebo que ver ultimo la lista sea el ultimo elemento", *(int*)lista_ver_ultimo(lista) == a);

    print_test("Pruebo que insertar ultimo la lista agregue el elemento", lista_insertar_ultimo(lista, &c));
    print_test("Pruebo que ver primero sea el primer elemento", *(int*)lista_ver_primero(lista) == b);
    print_test("Pruebo que ver ultimo la lista sea el ultimo elemento agregado", *(int*)lista_ver_ultimo(lista) == c);

    lista_destruir(lista, NULL);
    print_test("La lista de prueba lista insertar fue destruida", true);
    printf("\n");
}

static void prueba_lista_borrar(void){
    printf("INICIO DE LA PRUEBA LISTA BORRAR\n");
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 3;
    print_test("Pruebo que la lista creada este vacia", lista_esta_vacia(lista));
    lista_insertar_ultimo(lista, &a);
    lista_insertar_ultimo(lista, &b);
    lista_insertar_ultimo(lista, &c);
    print_test("Pruebo que la lista no este vacia", !lista_esta_vacia(lista));

    print_test("Pruebo que ver primero sea el primer elemento de la lista", *(int*)lista_ver_primero(lista) == a);
    print_test("Pruebo que borrar primero me de el primer elemento de la lista", *(int*)lista_borrar_primero(lista) == a);
    print_test("Pruebo que ver primero sea el segundo elemento de la lista despues del borrado del primer elemento", *(int*)lista_ver_primero(lista) == b);
    print_test("Pruebo que ver ultimo la lista sea el ultimo elemento", *(int*)lista_ver_ultimo(lista) == c);

    print_test("Pruebo que borrar primero me de el primer elemento de la lista", *(int*)lista_borrar_primero(lista) == b);
    print_test("Pruebo que ver primero sea el segundo elemento de la lista despues del borrado del primer elemento", *(int*)lista_ver_primero(lista) == c);
    print_test("Pruebo que ver ultimo la lista sea el ultimo elemento", *(int*)lista_ver_ultimo(lista) == c);  

    print_test("Pruebo que borrar primero me de el primer elemento de la lista", *(int*)lista_borrar_primero(lista) == c);

    print_test("Pruebo que la lista este vacia", lista_esta_vacia(lista));
    print_test("Pruebo ver primero lista vaciada devuelva NULL", lista_ver_primero(lista) == NULL);
    print_test("Pruebo ver ultimo lista vaciada devuelva NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Pruebo que borrar primero de la lista vaciada devuelva NULL", lista_borrar_primero(lista) == NULL);
    print_test("Pruebo que se pueda insertar una vez mas", lista_insertar_ultimo(lista, &a));

    lista_destruir(lista, NULL);
    print_test("La lista de prueba lista borrar fue destruida", true);
    printf("\n");
}

static void prueba_lista_volumen(void){
    printf("INICIO DE LA PRUEBA LISTA VOLUMEN\n");
    lista_t* lista = lista_crear();
    int arreglo[MAX_VOL];
    for(int i = 0; i < MAX_VOL; i++){
        arreglo[i] = i;
    }
    for(int i = 0; i < MAX_VOL; i++){
        lista_insertar_ultimo(lista, &arreglo[i]);
    }

    bool borrado = false;
    bool orden = false;
    int indice = 0;

    while(!lista_esta_vacia(lista)){
        orden = *(int*)lista_ver_primero(lista) == arreglo[indice] && *(int*)lista_ver_ultimo(lista) == arreglo[MAX_VOL - 1];
        borrado = *(int*)lista_borrar_primero(lista) == arreglo[indice];
        indice++;
    }

    print_test("Pruebo el borrado en orden correcto", borrado);
    print_test("Pruebo el ver primero y ultimo en orden correcto", orden);

    lista_destruir(lista, NULL);
    print_test("La lista de prueba lista volumen fue destruida", true);
    printf("\n");
}

static void prueba_lista_destruir_con_funcion(void){
    printf("INICIO DE LA PRUEBA LISTA DESTRUIR CON FUNCION\n");
    //pruebo con free
    lista_t* lista = lista_crear();
    int* valor = malloc(sizeof(int));
    valor[0] = 1;
    lista_insertar_primero(lista, valor);
    lista_destruir(lista, free);
    print_test("La lista con free fue destruida", true);
    
    //pruebo con pila destruir
    lista_t* lista_2 = lista_crear();
    pila_t* pila = pila_crear();
    int a = 4;
    pila_apilar(pila, &a);
    lista_insertar_ultimo(lista_2, pila);
    lista_destruir(lista_2, (void(*)(void*))pila_destruir);
    print_test("La lista con pila destruir fue destruida", true);

    printf("\n");
}

bool suma_numeros_pares(void* elemento, void* extra){
    if(*(int*) elemento % 2 == 0){
        *(int*) extra += *(int*)elemento;
    }
    return true;
}

bool primer_numero_impar(void* elemento, void* extra){
    if(*(int*) elemento % 2 == 0) return true;
    else{
        *(int*) extra = *(int*) elemento;
        return false;
    }
}

bool imprimir_datos(void* elemento, void* extra){
    int *contador = extra;
    printf("%d. %d", ++(*contador), *(int*) elemento);

    return true;  // seguir iterando
}

static void prueba_iterador_interno(void){
    printf("INICIO DE LA PRUEBA INTERARDOR INTERNO DE LA LISTA\n");
    lista_t* lista = lista_crear();
    lista_t* lista_2 = lista_crear();
    int arreglo[5];
    
    for(int i = 0; i < 5; i++){
        arreglo[i] = i;
    }

    for(int i = 0; i < 5; i++){
        lista_insertar_ultimo(lista, &arreglo[i]);
    }

    int suma_pares = 0;
    int suma_pares_2 = 0;
    lista_iterar(lista, suma_numeros_pares, &suma_pares);
    lista_iterar(lista_2, suma_numeros_pares, &suma_pares_2);
    print_test("Suma pares de la lista {0,1,2,3,4} debe ser 6", suma_pares == 6);
    print_test("Suma pares en lista vacia es 0", suma_pares_2 == 0);

    int numero_impar = 0;
    int numero_impar_2 = 0;
    lista_iterar(lista, primer_numero_impar, &numero_impar);
    lista_iterar(lista_2, primer_numero_impar, &numero_impar_2);
    print_test("Primer numero impar de la lista {0,1,2,3,4} debe ser 1", numero_impar == 1);
    print_test("Primer numero impar en lista vacia es 0 definido en la variable a pasar", numero_impar_2 == 0);

    int cont_1 = 0;
    printf("Los datos de la lista son {0,1,2,3,4}: ");
    lista_iterar(lista, imprimir_datos, &cont_1);
    print_test("el iterador imprimio los elementos correctos", true);

    int cont_2 = 0;
    printf("Los datos de la lista vacia es vacio: ");
    lista_iterar(lista_2, imprimir_datos, &cont_2);
    print_test("el iterador no imprimio nada", true);

    lista_destruir(lista, NULL);
    lista_destruir(lista_2, NULL);
    print_test("Las listas usadas fueron destruidas", true);
    printf("\n");
}

static void prueba_iterador_externo(void){
    printf("INICIO DE LA PRUEBA INTERARDOR EXTERNO DE LA LISTA\n");
    lista_t* lista = lista_crear();
    lista_t* lista_2 = lista_crear();
    int arreglo[5];
    
    for(int i = 0; i < 5; i++){
        arreglo[i] = i;
    }

    for(int i = 0; i < 5; i++){
        lista_insertar_ultimo(lista, &arreglo[i]);
        lista_insertar_ultimo(lista_2, &arreglo[i]);
    }

    lista_iter_t* iter = lista_iter_crear(lista);
    lista_iter_t* iter_2 = lista_iter_crear(lista_2);
    int suma_pares = 0;

    while(!lista_iter_al_final(iter)){
        if(*(int*) lista_iter_ver_actual(iter) % 2 == 0){
            suma_pares += *(int*) lista_iter_ver_actual(iter);
        }
        lista_iter_avanzar(iter);
    }
    
    print_test("El sumar pares de interador externo debe ser 6", suma_pares == 6);

    //Prueba muy particular de iterador externo lista, con elementod 0,1,2,3,4 corta cuando vea 6, que va a ser agregado cuando actual sea suma_pares/2 -> 6/2
    //esta prueba es para verificar si el agregado funciona correctamente en conjunto al avanzar en un ciclo.
    while(*(int*)lista_iter_ver_actual(iter_2) != suma_pares){
        if(*(int*)lista_iter_ver_actual(iter_2) == (suma_pares/2)){
            lista_iter_insertar(iter_2, &suma_pares);
            continue;
        }
        lista_iter_avanzar(iter_2); 
    }

    print_test("El actual del segundo iterador debe ser el resultado de suma_pares", *(int*)lista_iter_ver_actual(iter_2) == suma_pares);

    //Pruebas impresion 1
    lista_iter_t* iter_3 = lista_iter_crear(lista_2);
    
    //Imprimo la lista 2 como estaba
    printf("Se usa la lista 2 que se le fue agregado valor suma_pares de datos {0,1,2,6,3,4}: ");
    while(!lista_iter_al_final(iter_3)){
        printf("%d, ", *(int*) lista_iter_ver_actual(iter_3));
        lista_iter_avanzar(iter_3);
    }
    print_test("se imprimio lo correcto", true);

    // Quito el valor que agregue en la lista 2 de la prueba especifica
    print_test("Quito el actual del iter 2 que fue lo agregado a la lista 2 igual a suma pares", *(int*)lista_iter_borrar(iter_2) == suma_pares);

    //Prueba impresion 2
    lista_iter_t* iter_4 = lista_iter_crear(lista_2);
    
    //Imprimo la lista 2 pero el valor que se le agrego de suma pares se quito
    printf("Se usa la lista 2 que se le fue quitado valor suma_pares de datos {0,1,2,3,4}: ");
    while(!lista_iter_al_final(iter_4)){
        printf("%d, ", *(int*) lista_iter_ver_actual(iter_4));
        lista_iter_avanzar(iter_4);
    }
    print_test("se imprimio lo correcto", true);


    //Pruebo que el iter_2 pueda avanzar hasta el final
    while(!lista_iter_al_final(iter_2)){
        lista_iter_avanzar(iter_2);
    }
    print_test("El iter_2 esta alf final", lista_iter_al_final(iter_2));
    print_test("El iter al final el acutal es NULL", lista_iter_ver_actual(iter_2) == NULL);

    lista_destruir(lista, NULL);
    lista_destruir(lista_2, NULL);
    lista_iter_destruir(iter);
    lista_iter_destruir(iter_2);
    lista_iter_destruir(iter_3);
    lista_iter_destruir(iter_4);

    print_test("Las listas e iteradores externos fueron destruidos", true);
    printf("\n");
}


static void prueba_iterador_externo_2(void){
    printf("INICIO DE LA PRUEBA INTERARDOR EXTERNO 2 DE LA LISTA\n");
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int arreglo[5];
    
    for(int i = 0; i < 5; i++){
        arreglo[i] = i;
    }

    for(int i = 0; i < 5; i++){
        lista_iter_insertar(iter, &arreglo[i]);
    }

    print_test("Largo de la lista es 5", lista_largo(lista) == 5);
    int a = 40; 
    
    //insertar al principio;
    lista_iter_insertar(iter, &a);
    print_test("El primero de la lista es el valor a", *(int*)lista_ver_primero(lista) == a);
    print_test("El largo pasa a ser 6", lista_largo(lista) == 6);
    lista_iter_borrar(iter);
    print_test("El primero de la lista volvio a ser el anterior", *(int*)lista_ver_primero(lista) == 4);
    print_test("Largo de la lista vuelve a ser 5", lista_largo(lista) == 5);

    //insertar final
    while(!lista_iter_al_final(iter)){
        lista_iter_avanzar(iter);
    }
    print_test("El iterador esta al final", lista_iter_al_final(iter));

    lista_iter_insertar(iter, &a);

    print_test("Al agregar en el final el iterador ya no esta en el final", !lista_iter_al_final(iter));

    print_test("El ultimo de la lista es el valor a", *(int*)lista_ver_ultimo(lista) == a);
    print_test("El largo pasa a ser 6", lista_largo(lista) == 6);
    lista_iter_borrar(iter);
    print_test("El ultimo de la lista volvio a ser el anterior", *(int*)lista_ver_ultimo(lista) == 0);
    print_test("Largo de la lista vuelve a ser 5", lista_largo(lista) == 5);

    //insertar muchos en el medio
    lista_iter_t* iter_2 = lista_iter_crear(lista);
    lista_iter_avanzar(iter_2);
    lista_iter_avanzar(iter_2);

    int arreglo_2[MAX_VOL];

    for(int i = 0; i < MAX_VOL; i++){
        arreglo_2[i] = i;
    }
    for(int i = 0; i < MAX_VOL; i++){
        lista_iter_insertar(iter_2, &arreglo_2[i]);
    }

    print_test("Veo que el actual sea el correcto", *(int*)lista_iter_ver_actual(iter_2) == arreglo_2[MAX_VOL-1]);
    print_test("El primero de la lista tiene que ser el anterior porque se insertaron al medio", *(int*)lista_ver_primero(lista) == arreglo[4]);
    print_test("El ultimo de la lista tiene que ser el anterior porque se insertaron al medio", *(int*)lista_ver_ultimo(lista) == arreglo[0]);
    print_test("La cantidad de la lista es correcta", lista_largo(lista) == MAX_VOL + 5);

    while(!lista_iter_al_final(iter_2)){
        lista_iter_avanzar(iter_2);
    }
    print_test("El iterador 2 esta al final", lista_iter_al_final(iter_2));
    print_test("No se puede eliminar con el iterador al final y devuelve NULL", lista_iter_borrar(iter_2) == NULL);
    print_test("La cantidad de la lista es igual", lista_largo(lista) == MAX_VOL + 5);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    lista_iter_destruir(iter_2);
    print_test("Las listas e iteradores externos fueron destruidos", true);
    printf("\n");
}


static void prueba_iterador_externo_3(void){
    printf("PRUEBA ITERADOR 3\n");
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int a = 4;

    print_test("Lista vacia", lista_esta_vacia(lista));
    print_test("Lista vacia largo es 0", lista_largo(lista) == 0);
    print_test("Iter esta al final si la lista esta vacia", lista_iter_al_final(iter));
    print_test("Insertar con iter", lista_iter_insertar(iter, &a));
    print_test("Se cambio el inicio", *(int*)lista_ver_primero(lista) == a);
    print_test("Se cambio el final", *(int*)lista_ver_ultimo(lista) == a);
    print_test("Lista con elemento insertado largo es 1", lista_largo(lista) == 1);
    print_test("Iter no esta al final si la lista si se agrgo un elemento", !lista_iter_al_final(iter));
    print_test("Elimino elemento con el iter", *(int*)lista_iter_borrar(iter) == a);
    print_test("Se cambio el inicio a NULL", lista_ver_primero(lista) == NULL);
    print_test("Se cambio el final a NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Lista vaciada largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    print_test("La lista e iterador externo fueron destruidos", true);
    printf("\n");
}


void pruebas_lista_estudiante() {
    prueba_lista_vacia();
    prueba_lista_insertar();
    prueba_lista_borrar();
    prueba_lista_volumen();
    prueba_lista_destruir_con_funcion();
    prueba_iterador_interno();
    prueba_iterador_externo();
    prueba_iterador_externo_2();
    prueba_iterador_externo_3();
}


#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
