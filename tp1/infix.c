#include "infix.h"
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** shunting_yard(char** cadena){
    cola_t* salida = cola_crear();
    pila_t* signos = pila_crear();
    size_t i = 0;
    struct calc_token token;

    size_t cantidad = 0;
    while(cadena[cantidad] != NULL){
        cantidad++;
    }
    char** res = malloc(sizeof(char*) * (cantidad+1));
    if(!res){
        pila_destruir(signos);
        cola_destruir(salida, NULL);
        return NULL;
    }

    while(cadena[i]){
        if(!calc_parse(cadena[i], &token)){
            cola_destruir(salida, NULL);
            pila_destruir(signos);
            return NULL;
        }

        if(token.type == TOK_NUM){
            cola_encolar(salida, cadena[i]);
        }
        else if(token.type == TOK_OPER){
            while(!pila_esta_vacia(signos) && *(char*)pila_ver_tope(signos) != '(' && precedencia((char*)pila_ver_tope(signos),cadena[i]) != MENOR && !asociativo_derecha(cadena[i])){
                cola_encolar(salida, pila_desapilar(signos));
            }
            pila_apilar(signos, cadena[i]);            
        }
        else if(token.type == TOK_LPAREN){
            pila_apilar(signos, cadena[i]);
        }
        else if(token.type == TOK_RPAREN){
            while(!pila_esta_vacia(signos) && *(char*)pila_ver_tope(signos) != '('){
                cola_encolar(salida, pila_desapilar(signos));
            }
            if(pila_desapilar(signos) == NULL){
                pila_destruir(signos);
                cola_destruir(salida, NULL);
                return NULL;
            }
        }
        i++;
    }
    while(!pila_esta_vacia(signos)){
        cola_encolar(salida, pila_desapilar(signos));
    }

    size_t indice = 0;
    while(!cola_esta_vacia(salida)){
        res[indice] = (char*) cola_desencolar(salida);
        indice++;
    }
    pila_destruir(signos);
    cola_destruir(salida, NULL);
    res[indice] = NULL;
    return res;
}


int main(){
    char* linea = NULL;
    size_t tam = 0;

    char** cadena;
    char** nueva_cadena;
    char* linea_impresion;

    while((getline(&linea, &tam, stdin)) != EOF){
        cadena = infix_split(linea);
        nueva_cadena = shunting_yard(cadena);
        linea_impresion = join(nueva_cadena, ' ');
        if(linea_impresion == NULL){
            fprintf(stdout, "%s\n", "ERROR");
        }
        else{
            fprintf(stdout,"%s\n", linea_impresion);
        }
        free_strv(cadena);
        free(nueva_cadena);
        free(linea_impresion);
    }
    free(linea);
    return 0;
}
