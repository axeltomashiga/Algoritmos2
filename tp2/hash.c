#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

#define CAP_MIN 31
#define FACTOR_CARGA 7

enum estado {
    VACIO, OCUPADO, BORRADO
};

typedef struct campo{
  const char* clave;
  void* valor;
  size_t estado;
} campo_t;

struct hash{
  size_t capacidad;
  size_t cantidad;
  size_t borrados;
  hash_destruir_dato_t destruir_dato;
  campo_t* tabla_hash;
};

struct hash_iter{
  const hash_t* hash;
  campo_t campo_act;
  size_t posicion;
};

bool redimensionar_hash(hash_t* hash);
bool hash_pertenece(const hash_t *hash, const char *clave);

size_t hashing(const char *clave, size_t len, size_t cap){
    size_t hash, i;
    for(hash = i = 0; i < len; ++i){
        hash += clave[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (hash%cap);
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;
    
    hash->tabla_hash = malloc(sizeof(campo_t) * (CAP_MIN));

    if(!hash->tabla_hash){
        free(hash);
        return NULL;
    }

    for(size_t i = 0; i < CAP_MIN; i++){
        hash->tabla_hash[i].valor = NULL;
        hash->tabla_hash[i].clave = NULL;
        hash->tabla_hash[i].estado = VACIO;
    }

    hash->capacidad = CAP_MIN;
    hash->cantidad = 0;
    hash->borrados = 0;
    hash->destruir_dato = destruir_dato;
    
    return hash;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    const char *copia = strdup(clave);

    if(((hash->cantidad + hash->borrados) * 10)/ hash->capacidad >= FACTOR_CARGA){
        if(!redimensionar_hash(hash)){
            return false;
        }
    }

    size_t pos = hashing(copia, strlen(copia), hash->capacidad);
    
    while(hash->tabla_hash[pos].estado != VACIO){
        if(hash->tabla_hash[pos].estado == OCUPADO && strcmp(copia, hash->tabla_hash[pos].clave) == 0){  
            if(hash->destruir_dato){
                hash->destruir_dato(hash->tabla_hash[pos].valor);
            }
            hash->tabla_hash[pos].valor = dato;
            free((char*)copia);
            return true;
        }
        pos++;
        if(pos >= hash->capacidad){
            pos = 0;
        }
    }

    hash->tabla_hash[pos].clave = copia;
    hash->tabla_hash[pos].valor = dato;
    hash->tabla_hash[pos].estado = OCUPADO;
    hash->cantidad++;
    return true;
}


void *hash_borrar(hash_t *hash, const char *clave){
    if(!hash_pertenece(hash, clave)) return NULL;

    size_t pos = hashing(clave, strlen(clave), hash->capacidad);
    size_t pos_aux = pos;

    while(hash->tabla_hash[pos].estado != VACIO){
        if(hash->tabla_hash[pos].estado == OCUPADO && strcmp(hash->tabla_hash[pos].clave, clave) == 0){  
            void* aux = hash->tabla_hash[pos].valor;

            hash->tabla_hash[pos].estado = BORRADO;
            hash->tabla_hash[pos].valor = NULL;
            hash->cantidad--;
            hash->borrados++;
            return aux;
        }
        pos++;
        if(pos == pos_aux){
            break;
        }
        if(pos >= hash->capacidad){
            pos = 0;
        }
    }
    return NULL;    
}


void *hash_obtener(const hash_t *hash, const char *clave){
    if(!hash_pertenece(hash, clave)) return NULL;

    size_t pos = hashing(clave, strlen(clave), hash->capacidad);
    size_t pos_aux = pos;

    while(hash->tabla_hash[pos].estado != VACIO){
        if(hash->tabla_hash[pos].estado == OCUPADO && strcmp(hash->tabla_hash[pos].clave, clave) == 0){
            return hash->tabla_hash[pos].valor;
        }
        pos++;
        if(pos == pos_aux){
            break;
        }
        if(pos >= hash->capacidad){
            pos = 0;
        }
    }
    return NULL;
}


bool hash_pertenece(const hash_t *hash, const char *clave){
    size_t pos = hashing(clave, strlen(clave), hash->capacidad);
    size_t pos_aux = pos;

    while(hash->tabla_hash[pos].estado != VACIO){
        if(hash->tabla_hash[pos].estado == OCUPADO && strcmp(hash->tabla_hash[pos].clave, clave) == 0){
            return true;
        }
        pos++;
        if(pos == pos_aux){
            return false;
        }
        if(pos >= hash->capacidad){
            pos = 0;
        }
    }
    return false;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

void hash_destruir(hash_t *hash){
    for(size_t i = 0; i < hash->capacidad; i++){
        if(hash->destruir_dato && hash->tabla_hash[i].estado == OCUPADO){
            hash->destruir_dato(hash->tabla_hash[i].valor);
        }
        free((char*)hash->tabla_hash[i].clave);
    }
    free(hash->tabla_hash);
    free(hash);
}

bool redimensionar_hash(hash_t *hash){
    size_t nueva_capacidad = hash->capacidad * 31;

    campo_t *nueva_tabla = malloc(sizeof(campo_t) * nueva_capacidad);
    if(!nueva_tabla) return false;

    for(size_t i = 0; i < nueva_capacidad; i++){
        nueva_tabla[i].valor = NULL;
        nueva_tabla[i].clave = NULL;
        nueva_tabla[i].estado = VACIO;
    }
    
    for(size_t i = 0; i < hash->capacidad; i++){
        if(hash->tabla_hash[i].estado == OCUPADO){
            const char* clave = hash->tabla_hash[i].clave;

            size_t pos_nueva = hashing(clave, strlen(clave), nueva_capacidad);

            while(nueva_tabla[pos_nueva].estado != VACIO){
                pos_nueva++;
                if(pos_nueva >= nueva_capacidad){
                    pos_nueva = 0;
                }
            }
            nueva_tabla[pos_nueva] = hash->tabla_hash[i];
        }
    }
    
    free(hash->tabla_hash);
    hash->capacidad = nueva_capacidad;
    hash->borrados = 0;
    hash->tabla_hash = nueva_tabla;
    return true;
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t *hash_iter = malloc(sizeof(hash_iter_t));
    if(!hash_iter) return NULL;

    size_t i = 0;

    hash_iter->hash = hash;
    hash_iter->posicion = i;
    hash_iter->campo_act = hash->tabla_hash[i];
    

    while(hash->tabla_hash[i].estado != OCUPADO){
        i++;
        if(i >= hash->capacidad){
            hash_iter->posicion = i;
            return hash_iter;
        }
    }

    hash_iter->campo_act = hash->tabla_hash[i];
    hash_iter->posicion = i;

    return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    size_t i = iter->posicion;
    i++;
    
    while(i < iter->hash->capacidad && iter->hash->tabla_hash[i].estado != OCUPADO){
        i++;
    }

    if(i >= iter->hash->capacidad){
        iter->posicion = i ;
        return false;
    }

    iter->campo_act = iter->hash->tabla_hash[i];
    iter->posicion = i;
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if(hash_iter_al_final(iter)) return NULL;
    return iter->campo_act.clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->posicion >= iter->hash->capacidad;
}

void hash_iter_destruir(hash_iter_t* iter){
    free(iter);
}