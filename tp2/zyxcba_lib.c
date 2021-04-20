#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "mensajes.h"
#include "paciente.h"
#include "doctor.h"
#include "abb.h"
#include "hash.h"
#include "zyxcba_lib.h"

// funcion auxiliar para poder destruir el dato paciente_t en la funcion destruir lista
void aux_paciente_destruir(void* paciente){
	paciente_destruir((paciente_t*)paciente);
}

// funcion auxiliar para poder destruir el dato doctor_t en la funcion destruir lista
void aux_doctor_destruir(void* doctor){
	doctor_destruir((doctor_t*)doctor);
}

void destruccion_listas(lista_t* pacientes, lista_t* doctores){
    if(pacientes){
        lista_destruir(pacientes, aux_paciente_destruir);
    }
    if(doctores){
        lista_destruir(doctores, aux_doctor_destruir);
    }
}

void pedir_turno(const char** parametros, const char* comando, turno_t* turnos, datos_t* datos) {
	bool ok = false;
    if(!parametros[0] || !parametros[1] || !parametros[2]){
        printf(ENOENT_PARAMS, COMANDO_PEDIR_TURNO);
    }
    else if(!hash_pertenece(diccionario_pacientes(datos), parametros[0])){
        printf(ENOENT_PACIENTE, parametros[0]);
    }
    else if(!hash_pertenece(diccionario_especialidades(datos), parametros[1])){
        printf(ENOENT_ESPECIALIDAD, parametros[1]);
    }
    else if(strcmp(parametros[2], URGENCIA_URGENTE) == 0){
        encolar_turno_urgente(turnos, parametros[1], hash_obtener(diccionario_pacientes(datos), parametros[0]));
		ok = true;
    }
	else if(strcmp(parametros[2], URGENCIA_REGULAR) == 0){
        encolar_turno_regular(turnos, parametros[1], hash_obtener(diccionario_pacientes(datos), parametros[0]));
		ok = true;
    }
	else{
		printf(ENOENT_URGENCIA, parametros[2]);
	}
	if(ok){
		printf(PACIENTE_ENCOLADO, parametros[0]);
    	printf(CANT_PACIENTES_ENCOLADOS, cantidad_total_pacientes(turnos, parametros[1]), parametros[1]);
	}
}

void atender(const char** parametros, turno_t* turnos, datos_t* datos){
	if(!parametros[0]){
		printf(ENOENT_PARAMS, COMANDO_ATENDER);
		return;
	}
	if(!abb_pertenece(arbol_doctores(datos), parametros[0])){
        printf(ENOENT_DOCTOR, parametros[0]);
		return;
    }
	doctor_t* doctor = abb_obtener(arbol_doctores(datos), parametros[0]);
	paciente_t* paciente = desencolar_turno_urgente(turnos, parametros[0], arbol_doctores(datos));
    if(!paciente) {
		paciente = desencolar_turno_regular(turnos, parametros[0], arbol_doctores(datos));
        if(!paciente){
			printf(SIN_PACIENTES);
			return;
		}
    }
	printf(PACIENTE_ATENDIDO, paciente_nombre(paciente));
    printf(CANT_PACIENTES_ENCOLADOS, cantidad_total_pacientes(turnos, doctor_especialidad(doctor)), doctor_especialidad(doctor));
}

// funcion visitar del abb in order para poder contar los doctores que hay en el rango pedido
bool sumar_contador(const char* doctor, void* dato, void* extra){
    *(int*)extra += 1;
    return true;
}

// funcion visitar del abb in order para imprimir los datos del doctor
bool imprimir_datos(const char* doctor, void* dato, void* extra){
    char* especialidad = doctor_especialidad((doctor_t*)dato);
    unsigned long int atendio = doctor_atendio((doctor_t*)dato);
    printf(INFORME_DOCTOR, *(unsigned long int*)extra, doctor, especialidad, atendio);
    *(unsigned long int*)extra += 1;
    return true;
}

// funcion auxiliar para imprimir los datos del doctor por salida estandar
void imprimir_informe(abb_t* doctores ,const char* min, const char* max) {
    unsigned long int contador = 0;
    abb_in_order_por_rangos(doctores, min, max, sumar_contador, &contador);
    printf(DOCTORES_SISTEMA, contador);

    unsigned long int indice = 1;
    abb_in_order_por_rangos(doctores, min, max, imprimir_datos, &indice);
}

void informe(const char** parametros, datos_t* datos) {
    if (!parametros[1]) {
        printf(ENOENT_PARAMS,COMANDO_INFORME);
    }
    else {
		const char* minimo = (parametros[0][0] == '\0' ? NULL : parametros[0]);
    	const char* maximo = (parametros[1][0] == '\0' ? NULL : parametros[1]);
        imprimir_informe(arbol_doctores(datos), minimo, maximo);
    }
}