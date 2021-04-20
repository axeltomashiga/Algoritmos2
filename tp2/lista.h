#ifndef _LISTA_H
#define _LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

//Crea la pila.
//Post: Se crea la lista y la devuelve vacia, si hay algun error devuelve NULL.
lista_t *lista_crear(void);

//Devuelve true si la lista esta vacia, false en caso contrario.
//Pre: La lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

//Agraga el dato dado a la lista. Devuelve false si no se agrega.
//Pre: La lista fue creada.
//Post: Se agrega el dato en en la primera posicion.
bool lista_insertar_primero(lista_t *lista, void *dato);

//Agraga el dato dado a la lista. Devuelve false si no se agrega.
//Pre: La lista fue creada.
//Post: Se agrega el dato en en la ultima posicion.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//Elimina el dato dado a la lista. Devuelve el dato, o NULL si esta vacia
//Pre: La lista fue creada
//Post: Se elimina el dato en en la primera posicion y la devuelve
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve el valor del largo de la lista, la lista vacia es 0.
//Pre: La lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Iterador interno, aplica la funcion visitar a los datos de la lista.
// Pre: La lista fue creada.
// Post: Aplica la funcion visitar sin modificar los datos de la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Iterador externo se crea el iterador externo.
// Post: Se crea el iterador, devuelve NULL en caso de falla.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza la posicion del iterador externo.
// Pre: La lista y el iterador externo fueron creados.
// Post: El iterador avanza de posicion devuelve false en caso contrario.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato de las posicion actual del interador.
// Pre: La lista y el iterador fueron creados.
// Post: Devuelve el dato de la posicion actual del iterador sin modificar la lista.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Verifica que el iterador externo este en el final
// Pre: La lista y el iterador fueron creados.
// Post: Devuelve true si esta al final o falso en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador externo.
// Pre: El iterador fue creado.
// Post: Se libero la memoria pedido para el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega el dato el la posicion del iterador.
// Pre: La lista y el iterador fueron creada.
// Post: El dato fue agragado sevuelve false en caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el elemento y devuelve el dato de la pos actual de la lista.
// Pre: La lista y el iterador fueron creados.
// Post: El elemento de la lista fue eliminado.
void *lista_iter_borrar(lista_iter_t *iter);

#endif