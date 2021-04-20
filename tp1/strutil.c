#include "strutil.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *substr(const char *str, size_t n){
    char* cadena_nueva = malloc(sizeof(char) * (n+1));
    if(!cadena_nueva) return NULL;

    size_t i = 0;

    while(str[i] != '\0' && i < n){
        cadena_nueva[i] = str[i];
        i++;
    }
    cadena_nueva[i] = '\0';
    return cadena_nueva;
}

int* inicios_palabras(const char *str, char sep, size_t cant_sep){
    int* inicios = malloc(sizeof(int) * (cant_sep));
    if(!inicios) return NULL;

    inicios[0] = 0;
    int indice_inicios = 1;

    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == sep){
            inicios[indice_inicios] = i + 1;
            indice_inicios++; 
        }
    }
    return inicios;
}

char **split(const char *str, char sep){
    size_t cant_sep = 1;

    for(size_t i = 0; str[i] != '\0'; i++){
        if(str[i] == sep){
            cant_sep++;
        }
    }

    char** cadena_sep = malloc(sizeof(char*) * (cant_sep + 1));
    if(!cadena_sep) return NULL;

    if(cant_sep == 1){
        cadena_sep[0] = substr(str, strlen(str));
        cadena_sep[1] = NULL;
        return cadena_sep;
    }

    int* inicios = inicios_palabras(str, sep, cant_sep);
    if(!inicios) return NULL;

    size_t indice = 0;

    while(indice < cant_sep){
        if(indice + 1 >= cant_sep){
            cadena_sep[indice] = substr(str + inicios[indice], strlen(str + inicios[indice]));
        }
        else{
            cadena_sep[indice] = substr(str + inicios[indice], strlen(str + inicios[indice]) - strlen(str + inicios[indice + 1]) - 1);
        }
        indice++;
    }

    cadena_sep[cant_sep] = NULL;
    free(inicios);
    return cadena_sep;
}


char *join(char **strv, char sep){
    if(!strv) return NULL;
    
    size_t caracteres = 0;
    size_t i = 0;

    while(strv[i] != NULL){
        caracteres += strlen(strv[i]);
        i++;
    }

    char* resultado = calloc((caracteres + i + 1), sizeof(char));
    if(!resultado) return NULL;

    size_t indice = 0;
    size_t palabra_i = 0;
    size_t caracter_i = 0;

    while(strv[palabra_i] != NULL){
        if(strv[palabra_i][caracter_i] == '\0'){
            if(strv[palabra_i + 1] != NULL){
                if(sep != '\0'){
                    resultado[indice] = sep;
                    indice++;
                }
            }
            palabra_i++;
            caracter_i = 0;
            continue;
        }
        resultado[indice] = strv[palabra_i][caracter_i];
        caracter_i++;
        indice++;
    }
    resultado[indice] = '\0';
    return resultado;
}

void free_strv(char *strv[]){
    int i = 0;
    while(strv[i] != NULL){
        free(strv[i]);
        i++;
    }
    free(strv);
}