#ifndef INFIX
#define INFIX
#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include "cola.h"
#include "pila.h"
#include "calc_helper.h"
#include "verificaciones.h"

/* algoritmo de shunting yard de notacion posfija

pre: la entrada puede ser uno de los cinco operadores aritméticos + - * / ^, un paréntesis de apertura, (; o de cierre, ),
    un número entero, no negativo y en base decimal.
    Se garantiza, por último, que todas las expresiones de entrada estarán bien formadas: paréntesis balanceados, espaciado conforme a norma, etc.

post: Por salida estandar sale la notacion posfija
*/
char** shunting_yard(char** cadena);

#endif