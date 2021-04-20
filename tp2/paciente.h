#ifndef PACIENTE
#define PACIENTE

/* ******************************************************************
 *           DEFINICION DEL TIPO DE DATO --> PACIENTE
 * *****************************************************************/

// |Paciente| Es una estructura que contiene dos campos:
// - Año de inscripción --> int
// - Nombre del paciente --> char*
struct paciente;
typedef struct paciente paciente_t;


/* ******************************************************************
 *                            PRIMITIVAS
 * *****************************************************************/

// Recibe un nombre (char*) y un año de inscripción (int) y crea un paciente
// Post: El paciente fue creado
paciente_t* paciente_crear(const char* nombre, int numero);

// Devuelve el nombre de un paciente dado por parámetro
// Pre: El paciente fue creado
char* paciente_nombre(const paciente_t* paciente);

// Devuelve el año de inscripción de un paciente dado por parámetro
// Pre: El paciente fue creado
int paciente_inscripcion(const paciente_t* paciente);

// Libera la memoria utilizada para guardar la estructura paciente
void paciente_destruir(paciente_t* paciente);

// Función Wrapper de paciente_crear
void* constructor_paciente(char** params, void* extra);

#endif
