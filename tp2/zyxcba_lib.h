#ifndef ZYXCBA_LIB
#define ZYXCBA_LIB

#include <stdlib.h>
#include <string.h>

#include "turno.h"
#include "datos.h"
#include "lista.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define URGENCIA_REGULAR "REGULAR"
#define URGENCIA_URGENTE "URGENTE"

// Destruye las listas creadas a partir de los archivos csv
// pre: listas creadas
// post : memoria de las listas liberadas
void destruccion_listas(lista_t* pacientes, lista_t* doctores);

// Comado pedir turno
// pre: se ingresa el comando por entrada estandar, se crea turno y datos
// post: se encola los pacientes y por salida estandar se imprime que fue encolado y cuantos pacientes hay
void pedir_turno(const char** parametros, const char* comando, turno_t* turnos, datos_t* datos);

// Comado atender
// pre: se ingresa el comando por entrada estandar, se crea turno y datos
// post: se desencola el paciente del turno y sale por salida estandar que paciente se va a atender
void atender(const char** parametros, turno_t* turnos, datos_t* datos);

// Comado informe
// pre: se ingresa el comando por entrada estandar, se crea turno y datos
// post: se imprime por salida estandar los doctores que se piden en un rango, enumerados, sus datos y cuantos pacientes atendio.
void informe(const char** parametros, datos_t* datos);

#endif