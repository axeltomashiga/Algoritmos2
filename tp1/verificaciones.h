#ifndef VERIFICACIONES
#define VERIFICACIONES
#include <stdbool.h>

typedef enum precedencia{
    MAYOR, IGUAL, MENOR
} precedencia_t;

//verifica si el signo a es de precedencia mayor, menor o igual b
//devuelve el valor del enum MAYOR, IGUAL, MENOR
precedencia_t precedencia (const char* a, const char* b);


//verifica que el signo sea asociativo a la derecha
bool asociativo_derecha(const char* a);

#endif