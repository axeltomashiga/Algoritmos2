#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "doctor.h"

struct doctor {
	char* especialidad;
	char* nombre;
	int atendidos;
};

doctor_t* doctor_crear(const char* nombre, const char* especialidad) {
	doctor_t* doctor = malloc(sizeof(doctor_t));
	if (!doctor) return NULL;

	doctor->nombre = strdup(nombre);
	if (!doctor->nombre) {
		free(doctor);
		return NULL;
	}
    doctor->especialidad = strdup(especialidad);
	if (!doctor->especialidad) {
        free(doctor->nombre);
		free(doctor);
		return NULL;
	}
	doctor->atendidos = 0;
	
	return doctor;
}

char* doctor_especialidad(const doctor_t* doctor){
	return doctor->especialidad;
}

char* doctor_nombre(const doctor_t* doctor){
	return doctor->nombre;
}

size_t doctor_atendio(const doctor_t* doctor){
	return doctor->atendidos;
}

void doctor_sumar_atendidos(doctor_t* doctor){
	doctor->atendidos += 1;
}

void doctor_destruir(doctor_t* doctor) {
    free(doctor->especialidad);
	free(doctor->nombre);
	free(doctor);
}

void* constructor_doctor(char** params, void* extra) {
	return doctor_crear(params[0], params[1]);
}