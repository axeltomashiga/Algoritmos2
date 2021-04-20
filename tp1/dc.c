#include "dc.h"
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool calculadora(char** cadena, calc_num* extra){
    calc_num i = 0;
    calc_num numero_1;
    calc_num numero_2;
    calc_num numero_3;
    calc_num aux;

    struct calc_token token;

    pilanum_t* numeros_pila = pilanum_crear();
    if(!numeros_pila) return false;

    while(cadena[i] != NULL){
        if(!calc_parse(cadena[i], &token)){
            pilanum_destruir(numeros_pila);
            return false;
        }

        if(token.type == TOK_NUM){
            apilar_num(numeros_pila, token.value);
            i++;
            continue;
        }

        else if(token.type == TOK_OPER){
            if(!desapilar_num(numeros_pila, &numero_1)){
                pilanum_destruir(numeros_pila);
                return false;
            }
    
            if(token.oper.op == OP_ADD){
                if(!desapilar_num(numeros_pila, &numero_2)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, (numero_2 + numero_1));
            }
            else if(token.oper.op == OP_SUB){
                if(!desapilar_num(numeros_pila, &numero_2)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, (numero_2 - numero_1));
            }
            else if(token.oper.op == OP_MUL){
                if(!desapilar_num(numeros_pila, &numero_2)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, (numero_2 * numero_1));
            }
            else if(token.oper.op == OP_DIV){
                if(!desapilar_num(numeros_pila, &numero_2)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                if(numero_1 == 0){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, (numero_2 / numero_1));
            }
            else if(token.oper.op == OP_LOG){
                if(!desapilar_num(numeros_pila, &numero_2) || (numero_1 < 2 || numero_2 < 1)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, (log(numero_2)/log(numero_1)));
            }
            else if(token.oper.op == OP_POW){
                if(!desapilar_num(numeros_pila, &numero_2) || numero_1 < 0){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, pow(numero_2, numero_1));
            }
            else if(token.oper.op == OP_RAIZ){
                if(numero_1 < 0){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                apilar_num(numeros_pila, sqrt(numero_1));
            }
            else if(token.oper.op == OP_TERN){
                if(!desapilar_num(numeros_pila, &numero_2) || !desapilar_num(numeros_pila, &numero_3)){
                    pilanum_destruir(numeros_pila);
                    return false;
                }
                aux = numero_3 ? numero_2 : numero_1;
                apilar_num(numeros_pila, aux);
            }
            i++;
            continue;
        }
        pilanum_destruir(numeros_pila);
        return false;
    }
    desapilar_num(numeros_pila, extra);
    if(!pila_esta_vacia(numeros_pila) || i <= 1){
        pilanum_destruir(numeros_pila);
        return false;
    }
    pilanum_destruir(numeros_pila);
    return true;
}

int main(){
    char* linea = NULL;
    size_t tam = 0;

    char** cadena;
    calc_num numero;

    while((getline(&linea, &tam, stdin)) != EOF){
        cadena = dc_split(linea);
        if(!calculadora(cadena, &numero)){
            fprintf(stdout,"%s\n", "ERROR");
        }else{
            fprintf(stdout, "%ld\n", numero);
        }
        free_strv(cadena);
    }
    free(linea);
    return 0;
}