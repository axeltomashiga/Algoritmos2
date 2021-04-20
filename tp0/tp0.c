#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0){
        return -1;
    }
    int indice_maximo = 0;
    for (int i = 1; i < n; i++){
        if (vector[indice_maximo] < vector[i]){
            indice_maximo = i;
        }
    }
    return indice_maximo;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    for(int i = 0; i < n1 && i < n2; i++){
        if (vector1[i] < vector2[i]){
            return -1;
        } else if (vector1[i] > vector2[i]){
            return 1;
        }
    }
    if (n1 < n2){
        return -1;
    } else if (n1 > n2){
        return 1;
    }
    return 0;
}


void seleccion(int vector[], int n) {
    if (n == 0){
        return;
    }
    int pos_max = maximo(vector, n);
    swap(&vector[n-1], &vector[pos_max]);
    seleccion(vector, n-1);
}
