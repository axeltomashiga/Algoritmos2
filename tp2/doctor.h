#ifndef DOCTOR
#define DOCTOR

#include <stddef.h>


/* ******************************************************************
 *           DEFINICION DEL TIPO DE DATO --> DOCTOR
 * *****************************************************************/


// |Doctor| Es una estructura de datos que contiene tres campos.
// - La especialidad del doctor --> char*
// - El nombre del doctor --> char*
// - La cantidad de pacientes atendidos desde que el sistema inicia --> int
typedef struct doctor doctor_t;


/* ******************************************************************
 *                  PRIMITIVAS DE DOCTOR
 * *****************************************************************/

// Recibe un nombre y una especialidad (Ambos char*) y crea un perfil de un doctor
// Post: La cantidad inicial de atendidos es 0
doctor_t* doctor_crear(const char* nombre, const char* especialidad);

// Devuelve la especialidad de un doctor dado por parámetro
// Pre: El doctor fue creado
char* doctor_especialidad(const doctor_t* doctor);

// Devuelve el nombre de un doctor dado por parámetro
// Pre: El doctor fue creado
char* doctor_nombre(const doctor_t* doctor);

// Devuelve la cantidad de pacientes que atendió un doctor (Dado por parámetro) desde que
// arrancó el sistema
// Pre: El doctor fue creado
size_t doctor_atendio(const doctor_t* doctor);

// Aumenta la cantidad de atendidos de un doctor en una unidad
// Pre: El doctor fue creado
void doctor_sumar_atendidos(doctor_t* doctor);

// Libera la memoria utilizada para guardar la estructura doctor
void doctor_destruir(doctor_t* doctor);

// Es una función Wrapper de doctor_crear
void* constructor_doctor(char** params, void* extra);

#endif
