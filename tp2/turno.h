#ifndef TURNO
#define TURNO

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *           DEFINICION DEL TIPO DE DATO --> TURNO
 * *****************************************************************/

// |Turno| Es una estructura que tiene dos Diccionarios como subestructuras. Tiene un
// diccionario para turnos urgentes y otro para turnos regulares.
// - Urgentes --> Formato {clave : valor, ... } = {Especialidad, cola_turnos}
// - Regulares --> Formato {clave : valor, ... } = {Especialidad, heap_minimos}
struct turno;
typedef struct turno turno_t;

// Crea la estructura turno
turno_t* turno_crear();

// Agrega un paciente al Diccionario de Urgentes. Lo hace en la cola_turnos de una especialidad
// específica dada por parámetro.
// Pre: Turno ya fue creado
// Post: La cola_turnos de esa especilidad tiene un elemento más 
void encolar_turno_urgente(turno_t* turnos, const char* especialidad, void* paciente);

// Agrega un paciente al Diccionario de Regulares. Lo hace en el heap_minimos de una especialidad
// específica dada por parámetro.
// Pre: Turno ya fue creado
// Post: El heap de esa especilidad tiene un elemento más 
void encolar_turno_regular(turno_t* turnos, const char* especialidad, void* paciente);

// Elimina un paciente del Diccionario de Urgentes. Devuelve el primer paciente de la 
// cola_turnos de una especialidad específica dada por parámetro.
// Pre: Turno ya fue credo
// Post: La cola_turnos de esa especialidad tiene un elemento menos y se le resta uno a su cantidad actual
void* desencolar_turno_urgente(turno_t* turnos, const char* doctor, void* doctores);

// Elimina un paciente del Diccionario de Regulares. Devuelve el paciente de mayor prioridad
// del heap_minimos de una especialidad específica dada por parámetro.
// Pre: Turno ya fue credo
// Post: El heap_minimos tiene un elemento menos
void* desencolar_turno_regular(turno_t* turnos, const char* doctor, void* doctores);

// Devuelve la cantidad de pacientes en total que tiene una especialidad en específico.
// Se tienen en cuenta tanto los pacientes urgentes como regulares
size_t cantidad_total_pacientes(turno_t* turnos, const char* especialidad);

// Libera la memoria de la estructura turno
// Post: Las subestructuras también son liberadas junto con cada uno de sus elementos
void turnos_destruir(turno_t* turnos);

#endif