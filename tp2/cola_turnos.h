#ifndef COLA_TURNO
#define COLA_TURNO

#include <stddef.h>
#include <stdbool.h>

/* ******************************************************************
 *           DEFINICION DEL TIPO DE DATO --> COLA_TURNOS
 * *****************************************************************/

// |Cola_turnos| Es un TDA auxiliar utilizado para encolar pacientes urgentes. Consiste en una
// cola enlazada con un contador para facilitar el acceso a la cantidad de pacientes
struct cola_turnos;
typedef struct cola_turnos cola_turnos_t;

/* ******************************************************************
 *                PRIMITIVAS DE COLA_TURNOS
 * *****************************************************************/

// Crea una cola de turnos
// Post: Devuelve una cola vacía
cola_turnos_t* cola_turnos_crear();

// Agrega un paciente al final de la cola. Devuelve false en caso de error
// Pre: La cola fue creada 
// Post: Se agrega un paciente y la cantidad aumenta en una unidad
bool cola_turnos_encolar(cola_turnos_t* cola_turnos, void* paciente);

// Devuelve el paciente que se encuentre en el frente de la cola. Es decir el primer encolado
// de los pacientes de la cola_turno. En caso de error o cuando la cola está vacía, devuelve NULL
// Pre: La cola fue creada
// Post: Hay un paciente menos y la cantidad disminuye una unidad
void* cola_turnos_desencolar(cola_turnos_t* cola_turnos);

// Devuelve la cantidad actual de pacientes encolados en una cola_turnos
// Pre: La cola fue creada
size_t cola_turnos_cantidad(cola_turnos_t* cola_turnos);

// Si la cola_turnos no tiene elementos, devuelve true. En caso contrario, devuelve false
// Pre: La cola fue creada
bool cola_turnos_esta_vacia(cola_turnos_t* cola_turnos);

// Libera la memoria de la cola_turnos
// Pre: La cola fue creada
// Post: Se eliminan todos los pacientes que estaban en la cola
void cola_turnos_destruir(cola_turnos_t* cola_turnos);

#endif