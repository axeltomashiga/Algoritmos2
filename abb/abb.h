#ifndef ABB
#define ABB

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

typedef struct abb_iter abb_iter_t;

// Crea la estructura del arbol binario de busqueda, NULL caso contrario
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda el dato en el lugar correspondiente
// pre: arbol creado
// post: dato guardado
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Borra el dato de la clave, NULL caso de error o no pertenezca
// pre: arbol creado
// post: borra el dato
void *abb_borrar(abb_t *arbol, const char *clave);

// Obtiene el dato de la clave buscada, NULL caso de error o no pertenezca
// pre: arbol creado
// post: devuelve el valor si esta
void *abb_obtener(const abb_t *arbol, const char *clave);

// Indica si la clave pertenece a traves de un booleano
// pre: arbol creado
// post: indica si la clave pertenece o no
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad del arbol
// pre: arbol creado
// post: devuelve el valor de la cantidad del arbol
size_t abb_cantidad(abb_t *arbol);

// Destruye el arbol
// pre: arbol creado
// post: memoria del arbol liberada
void abb_destruir(abb_t *arbol);

// Iterador interno inorder
// pre: arbol creado
// post: el iterador se encuentra en el primer elemento
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

// Crea el iterador externo
// pre: arbol creado
// post: el iterador se encuentra en el primer elemento
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza el iterador externo
// pre: arbol e iterador creados
// post: avanza el iterador al siguiente elemento
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Ve el actual iterador externo
// pre: arbol e iterador creados
// post: devuelve la clave
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Verifica iterador externo al final
// pre: arbol e iterador creados
// post: devuelve booleano
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador externo
// pre: arbol e iterador creados
// post: memoria del iterador liberada
void abb_iter_in_destruir(abb_iter_t* iter);

#endif