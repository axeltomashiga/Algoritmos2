#ifndef DATOS
#define DATOS

#include <stdbool.h>
#include "lista.h"
#include "hash.h"
#include "abb.h"

/* ******************************************************************
 *                 TIPO DE DATO ---> DATOS
 * *****************************************************************/

// |Datos| Es una estructura que contiene los datos necesarios para administrar las instrucciones
// de los comandos dados por salida estándar. Cuenta con las siguientes subestructuras:
// 
// - Doctores --> Ordenados en un Arbol Binario de Búsqueda 
//   FORMATO { clave:valor, ...} = { Nombre del doctor: struct doctor_t, ...}
// 
// - Especialidades --> Ordenadas en un Hash o Diccionario
//   FORMATO { clave:valor, ...} = { Especialidad: NULL, ...}
// 
// - Pacientes --> Ordenados en un Hash o Diccionario
//   FORMATO { clave:valor, ...} = { Nombre del paciente: struct paciente_t, ...}
struct datos;
typedef struct datos datos_t;


/* ******************************************************************
 *                    PRIMITIVAS DE DATOS
 * *****************************************************************/

// Crea la estructura con los datos necesarios para arrancar el sistema.
// Post: Las subestructuras se inicializan vacías
datos_t* crear_datos();

// Devuelve el diccionario (o Hash) de los pacientes.
// Pre: Los datos ya fueron inicializados
hash_t* diccionario_pacientes(datos_t* datos);

// Devuelve el diccionario (o Hash) de las especialidades
// Pre: Los datos ya fueron inicializados
hash_t* diccionario_especialidades(datos_t* datos);

// Devuelve el ABB (Árbol Binario de Búsqueda) de los doctores
// Pre: Los datos ya fueron inicializados
abb_t* arbol_doctores(datos_t* datos);

// Recibe una estructura de datos tipo datos_t y una lista de doctores. Procesa los datos de 
// la lista y los guarda en la estructura datos_t. Se encarga de tomar registro de los doctores
// y de sus respectivas especialidades
// Pre: Los datos ya fueron inicializados
// Post: Si la lista está vacía u ocurrió un error al procesar los datos, la función devuelve false
bool procesar_datos_doctores(datos_t* datos, lista_t* doctores);

// Recibe una estructura de datos tipo datos_t y una lista de pacientes. Procesa los datos de la 
// lista y los guarda en la estructura datos_t. Se encarga de tomar registro de los pacientes 
// Pre: Los datos ya fueron inicializados
// Post: Si la lista está vacía u ocurrió un error al procesar los datos, la función devuelve false
bool procesar_datos_pacientes(datos_t * datos, lista_t* pacientes);

// Libera la estructura de datos y sus subestructuras
void destruccion_datos(datos_t* datos);

#endif