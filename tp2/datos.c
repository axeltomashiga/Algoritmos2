#include <stdlib.h>
#include <string.h>
#include "datos.h"
#include "paciente.h"
#include "doctor.h"


struct datos {
    abb_t* doctores;
    hash_t* especialidades;
    hash_t* pacientes;
};

datos_t* crear_datos(){
    datos_t* datos = malloc(sizeof(datos_t));
    if(!datos) return NULL;

    datos->pacientes = hash_crear(NULL);
	if(!datos->pacientes){
        free(datos);
        return NULL;
    }

	datos->doctores = abb_crear(strcmp, NULL);
	if(!datos->doctores){
		hash_destruir(datos->pacientes);
		free(datos);
		return NULL;
	}

	datos->especialidades = hash_crear(NULL);
	if(!datos->especialidades){
		hash_destruir(datos->pacientes);
		abb_destruir(datos->doctores);
		free(datos);
		return NULL;
	}

    return datos;
}

hash_t* diccionario_pacientes(datos_t* datos){
    return datos->pacientes;
}

hash_t* diccionario_especialidades(datos_t* datos){
    return datos->especialidades;
}

abb_t* arbol_doctores(datos_t* datos){
    return datos->doctores;
}

bool procesar_datos_doctores(datos_t* datos, lista_t* doctores){
    lista_iter_t* doctor = lista_iter_crear(doctores);
    if(!doctor){
        return false;
    }
    while(!lista_iter_al_final(doctor)){
        doctor_t* aux = lista_iter_ver_actual(doctor);
        if(!hash_guardar(datos->especialidades, doctor_especialidad(aux), NULL)) return false;
        if(!abb_guardar(datos->doctores, doctor_nombre(aux), aux)) return false;
		lista_iter_avanzar(doctor);
    }
    lista_iter_destruir(doctor);
    return true;
}

bool procesar_datos_pacientes(datos_t * datos, lista_t* pacientes){
    lista_iter_t* paciente = lista_iter_crear(pacientes);
    if(!paciente){	
        return false;
    }
    while(!lista_iter_al_final(paciente)){
        paciente_t* aux = lista_iter_ver_actual(paciente);
        if(!hash_guardar(datos->pacientes, paciente_nombre(aux), aux)) return false;
		lista_iter_avanzar(paciente);
    }
    lista_iter_destruir(paciente);
    return true;
}

void destruccion_datos(datos_t* datos){
    hash_destruir(datos->pacientes);
    hash_destruir(datos->especialidades);
    abb_destruir(datos->doctores);
    free(datos);
}