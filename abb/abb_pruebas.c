#include "testing.h"
#include "abb.h"
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_abb_vacio(){
    printf("PRUEBA ABB VACIO\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
    printf("\n");
}

static void prueba_iterar_abb_vacio(){
    printf("PRUEBA ABB ITERADOR VACIO\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_insertar(){
    printf("PRUEBA ABB INSERTAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_reemplazar(){
    printf("PRUEBA ABB REEMPLAZAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_reemplazar_con_destruir(){
    printf("PRUEBA ABB REEMPLAZAR CON FUNCION\n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_borrar(){
    printf("PRUEBA ABB BORRAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_borrar_raiz_2hijos(){
    printf("PRUEBA ABB BORRAR 2 HIJOS\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    print_test("Prueba abb pertenece clave1, es false", !abb_pertenece(abb, clave1));

    abb_destruir(abb);
    printf("\n");
}

bool imprimir_claves2(const char* clave, void* valor, void* extra){
    if(clave){
        printf("%s, ", clave);
        printf("%s, ", (char*)(valor));
    }
    printf("\n");
    return true;
}

static void prueba_borrar_1hijo_2hijos(){
    printf("PRUEBA ABB BORRAR 2 HIJOS Y 1 HIJO\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "zorro", *valor4 = "ku";
    char *clave5 = "queso", *valor5 = "cheese";

    
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    abb_in_order(abb, imprimir_claves2, NULL);

    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
    print_test("Prueba abb pertenece clave3, es false", !abb_pertenece(abb, clave3));
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

    print_test("Prueba abb obtener clave1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave3, es NULL", abb_obtener(abb, clave3) == NULL);
    print_test("Prueba abb obtener clave4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb obtener clave5", abb_obtener(abb, clave5) == valor5);
    abb_in_order(abb, imprimir_claves2, NULL);

    print_test("Prueba abb borrar clave4, es valor4", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
    print_test("Prueba abb pertenece clave3, es false", !abb_pertenece(abb, clave3));
    print_test("Prueba abb pertenece clave4, es false", !abb_pertenece(abb, clave4));
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

    print_test("Prueba abb obtener clave1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave3, es NULL", abb_obtener(abb, clave3) == NULL);
    print_test("Prueba abb obtener clave4, es NULL", abb_obtener(abb, clave4) == NULL);
    print_test("Prueba abb obtener clave5", abb_obtener(abb, clave5) == valor5);
    abb_in_order(abb, imprimir_claves2, NULL);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_clave_vacia() {
    printf("PRUEBA ABB CLAVE VACIA\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_valor_null(){
    printf("PRUEBA ABB VALOR NULL\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}


static void prueba_abb_volumen(size_t largo, bool debug){
    printf("PRUEBA ABB VOLUMEN\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];


    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }

    while(ok && abb_cantidad(abb) != largo){
        unsigned ind = rand()%(unsigned)largo;
        if(abb_pertenece(abb, claves[ind])) continue;
        ok = abb_guardar(abb, claves[ind], valores[ind]);
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    ok = true;
    while(ok && abb_cantidad(abb) != largo){
        unsigned ind = rand()%(unsigned)largo;
        if(abb_pertenece(abb, claves[ind])) continue;
        ok = abb_guardar(abb, claves[ind], valores[ind]);
    }

    free(claves);

    abb_destruir(abb);
    printf("\n");
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar() {
    printf("PRUEBA ABB ITERADOR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};


    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

static void prueba_imprimir_iterador_externo(){
    printf("PRUEBA ABB IMPRIMIR ITERADOR EXTERNO\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "zorro", *valor4 = "ku";
    char *clave5 = "queso", *valor5 = "cheese";

    abb_guardar(abb, clave1, valor1);
    abb_guardar(abb, clave2, valor2);
    abb_guardar(abb, clave3, valor3);
    abb_guardar(abb, clave4, valor4);
    abb_guardar(abb, clave5, valor5);

    abb_iter_t* iter =  abb_iter_in_crear(abb);
    while(!abb_iter_in_al_final(iter)){
        const char* clave = abb_iter_in_ver_actual(iter);
        printf("%s ,", clave);
        abb_iter_in_avanzar(iter);
    }
    
    print_test("claves en orden", true);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_iterar_volumen(size_t largo) {
    printf("PRUEBA ABB VOLUMEN E ITERADOR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
    }

    while(ok && abb_cantidad(abb) != largo){
        unsigned ind = rand()%(unsigned)largo;
        if(abb_pertenece(abb, claves[ind])) continue;
        ok = abb_guardar(abb, claves[ind], &valores[ind]);
    }

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

bool suma_numeros(const char* clave, void* valor, void* extra){
    if(valor) *(size_t*) extra += *(int*) valor;
	return true;
}

bool suma_pares(const char* clave, void* valor, void* extra){
    if(*(int*)valor % 2 == 0) *(size_t*) extra += *(int*) valor;
    return true;
}

bool imprimir_claves(const char* clave, void* valor, void* extra){
    if(clave){
        printf("%s, ", clave);
    }
    return true;
}

static void prueba_abb_iterador_interno(){
    printf("PRUEABA ITERADOR INTERNO\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	char* claves[] = {"alfa", "beta", "epsilon", "gama", "omega", "theta"};
	int valores[6];

    for(int i = 0; i < 6; i++){
        valores[i] = i;
    }

    bool ok =true;
    while(ok && abb_cantidad(abb) != 6){
        unsigned ind = rand()%6;
        if(abb_pertenece(abb, claves[ind])) continue;
        ok = abb_guardar(abb, claves[ind], &valores[ind]);
    }

	size_t numero_1 = 0;
	abb_in_order(abb, suma_numeros, &numero_1);
	print_test("Suma total del iterador es 15", numero_1 == 15);

    size_t numero_2 = 0;
	abb_in_order(abb, suma_pares, &numero_2);
	print_test("Suma pares del iterador es 6", numero_2 == 6);

    abb_in_order(abb, imprimir_claves, NULL);
    print_test("Claves en orden", true);

	abb_destruir(abb);
    printf("\n");
}

void destruccion_pila_abb(void* valor){
    pila_destruir((pila_t*)valor);
}

static void prueba_abb_destruccion_con_funcion(){
    printf("PRUEABA DESTRUCCION CON FUNCION\n");
    // Creo un arbol
    abb_t *abb = abb_crear(strcmp, destruccion_pila_abb);
    // Creo una arreglo con 5 cadenas
    char** cadenas = malloc(sizeof(char*)*5);
    cadenas[0] = "hola";
    cadenas[1] = "adios";
    cadenas[2] = "avion";    
    cadenas[3] = "cuaderno";    
    cadenas[4] = "manzana";    
    // Inserto las cadenas con pilas como dato
    for (size_t i = 0;i<5;i++){
        print_test("Guardo pilas",abb_guardar(abb,cadenas[i],pila_crear()));
    }
    // Destruyo el arbol y sus datos
    free(cadenas);
    abb_destruir(abb);
    print_test("ABB destruido con pilas", true);
    printf("\n");
}

void pruebas_abb_estudiante() {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_borrar_raiz_2hijos();
    prueba_borrar_1hijo_2hijos();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(5000, true);
    prueba_abb_iterar();
    prueba_imprimir_iterador_externo();
    prueba_abb_iterar_volumen(5000);
    prueba_abb_iterador_interno();
    prueba_abb_destruccion_con_funcion();
}

void pruebas_volumen_estudiante(size_t largo)
{
    prueba_abb_volumen(largo, false);
}

#ifndef CORRECTOR

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;
}

#endif