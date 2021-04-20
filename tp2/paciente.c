#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "paciente.h"


struct paciente {
	int anio;
	char* nombre;
};

paciente_t* paciente_crear(const char* nombre, int numero) {
	paciente_t* paciente = malloc(sizeof(paciente_t));
	if (!paciente) return NULL;

	paciente->nombre = strdup(nombre);
	if (!paciente->nombre) {
		free(paciente);
		return NULL;
	}
	paciente->anio = numero;
	return paciente;
}

char* paciente_nombre(const paciente_t* paciente){
	return paciente->nombre;
}

int paciente_inscripcion(const paciente_t* paciente){
	return paciente->anio;
}

void paciente_destruir(paciente_t* paciente) {
	free(paciente->nombre);
	free(paciente);
}

void* constructor_paciente(char** params, void* extra) { 
	if(atoi(params[1]) == 0){
		extra = params[1];
		return NULL;
	}
	return paciente_crear(params[0], atoi(params[1]));
}