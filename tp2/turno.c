#include <stdio.h>
#include <stdlib.h>
#include "paciente.h"
#include "doctor.h"
#include "hash.h"
#include "heap.h"
#include "cola_turnos.h"
#include "abb.h"
#include "turno.h"

struct turno{
    hash_t* urgente;
    hash_t* regular;
};

int comparar_antiguedad_pacientes(const void* a, const void* b) {
    int anio_a = paciente_inscripcion((paciente_t*)a);
    int anio_b = paciente_inscripcion((paciente_t*)b);

    if (anio_a < anio_b) {
        return 1;
    }
    if (anio_a == anio_b) {
        return 0;
    }
    return -1;
}

void aux_cola_turno_destruir(void* cola){
    cola_turnos_destruir((cola_turnos_t*)cola);
}

void aux_heap_destruir(void* heap){
    heap_destruir((heap_t*)heap, NULL);
}

size_t cantidad_total_pacientes(turno_t* turnos, const char* especialidad){
    heap_t* turnos_regulares = hash_obtener(turnos->regular, especialidad);
    cola_turnos_t* turnos_urgentes = hash_obtener(turnos->urgente, especialidad);
    size_t cant_regulares;
    size_t cant_urgentes;

    if(!turnos_regulares) cant_regulares = 0;
    else cant_regulares = heap_cantidad(turnos_regulares);

    if(!turnos_urgentes) cant_urgentes = 0;
    else cant_urgentes = cola_turnos_cantidad(turnos_urgentes);

    return cant_regulares + cant_urgentes;
}

turno_t* turno_crear(){
    turno_t* turnos = malloc(sizeof(turno_t));
    if(!turnos) return NULL;

    turnos->urgente = hash_crear(aux_cola_turno_destruir);
    if(!turnos->urgente){
        free(turnos);
        return NULL;
    }

    turnos->regular = hash_crear(aux_heap_destruir);
    if(!turnos->regular){
        hash_destruir(turnos->urgente);
        free(turnos);
        return NULL;
    }

    return turnos;
}

void encolar_turno_urgente(turno_t* turnos, const char* especialidad, void* paciente){
    cola_turnos_t* aux_turno_urgente = hash_obtener(turnos->urgente, especialidad);
    if(!aux_turno_urgente){
        aux_turno_urgente = cola_turnos_crear();
        cola_turnos_encolar(aux_turno_urgente, paciente);
        hash_guardar(turnos->urgente, especialidad, aux_turno_urgente);       
    }
    else{
        cola_turnos_encolar(aux_turno_urgente, paciente);
    }
}


void encolar_turno_regular(turno_t* turnos, const char* especialidad, void* paciente){
    heap_t* aux_turno_regular = hash_obtener(turnos->regular, especialidad);
    if(!aux_turno_regular){
        aux_turno_regular = heap_crear(comparar_antiguedad_pacientes);
        heap_encolar(aux_turno_regular, paciente);
        hash_guardar(turnos->regular, especialidad, aux_turno_regular);    
    }
    else{
        heap_encolar(aux_turno_regular, paciente);
    }   
}

void* desencolar_turno_urgente(turno_t* turnos, const char* doctor, void* doctores) {
    doctor_t* doc_aux = abb_obtener((abb_t*)doctores, doctor);
    cola_turnos_t* aux = hash_obtener(turnos->urgente, doctor_especialidad(doc_aux));
    if(!aux || cola_turnos_esta_vacia(aux)) return NULL;

    paciente_t* paciente_aux = (paciente_t*)cola_turnos_desencolar(aux);
    doctor_sumar_atendidos(doc_aux);

    return paciente_aux;
}

void* desencolar_turno_regular(turno_t* turnos, const char* doctor, void* doctores) {
    doctor_t* doc_aux = abb_obtener((abb_t*)doctores, doctor);
    heap_t* aux = hash_obtener(turnos->regular, doctor_especialidad(doc_aux));
    if(!aux || heap_esta_vacio(aux)) return NULL;

    paciente_t* paciente_aux = (paciente_t*)heap_desencolar(aux);
    doctor_sumar_atendidos(doc_aux);

    return paciente_aux;
}


void turnos_destruir(turno_t* turnos){
    hash_destruir(turnos->urgente);
    hash_destruir(turnos->regular);
    free(turnos);
}