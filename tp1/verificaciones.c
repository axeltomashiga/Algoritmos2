#include "verificaciones.h"

precedencia_t precedencia(const char* a, const char* b){
    int primero;
    int segundo;
    if(*a == '+' || *a == '-') primero = 0;
    if(*a == '/' || *a == '*') primero = 1;
    if(*a == '^') primero = 2;
    if(*b == '+' || *b == '-') segundo = 0;
    if(*b == '/' || *b == '*') segundo = 1;
    if(*b == '^') segundo = 2;
    
    if(primero > segundo) return MAYOR;
    if(primero == segundo) return IGUAL;
    return MENOR;
}

bool asociativo_derecha(const char* a){
    return *a == '^';
}