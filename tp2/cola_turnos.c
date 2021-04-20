#include <string.h>
#include <stdlib.h>
#include "cola_turnos.h"
#include "paciente.h"
#include "doctor.h"
#include "cola.h"

struct cola_turnos{
    cola_t* cola;
    size_t cantidad;
};

cola_turnos_t* cola_turnos_crear(){
    cola_turnos_t* cola_turnos = malloc(sizeof(cola_turnos_t));
    if(!cola_turnos) return NULL;

    cola_turnos->cola = cola_crear();
    if(!cola_turnos->cola){
        free(cola_turnos);
        return NULL;
    }

    cola_turnos->cantidad = 0;
    return cola_turnos;
}

bool cola_turnos_encolar(cola_turnos_t* cola_turnos, void* paciente){
    if(!cola_encolar(cola_turnos->cola, paciente)) return false;
    cola_turnos->cantidad ++;
    return true;
}

void* cola_turnos_desencolar(cola_turnos_t* cola_turnos){
    void* paciente = cola_desencolar(cola_turnos->cola);
    if(!paciente) return NULL;
    cola_turnos->cantidad --;
    return paciente;
}

size_t cola_turnos_cantidad(cola_turnos_t* cola_turnos){
    return cola_turnos->cantidad;
}

bool cola_turnos_esta_vacia(cola_turnos_t* cola_turnos){
    return cola_turnos->cantidad == 0;
}

void cola_turnos_destruir(cola_turnos_t* cola_turnos){
    cola_destruir(cola_turnos->cola, NULL);
    free(cola_turnos);
}