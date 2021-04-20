#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "csv.h"
#include "mensajes.h"
#include "datos.h"
#include "turno.h"
#include "doctor.h"
#include "paciente.h"
#include "zyxcba_lib.h"

void procesar_comando(const char* comando, const char** parametros, turno_t* turnos, datos_t* datos) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		pedir_turno(parametros, comando ,turnos, datos);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		atender(parametros, turnos, datos);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		informe(parametros, datos);
	} else {
		printf(ENOENT_CMD, comando);
	}
	return;
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada(turno_t* turnos, datos_t* datos) {
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], (const char**)parametros, turnos, datos);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}

int main(int argc, char** argv) {
	if(argc < 3){
		printf(ENOENT_CANT_PARAMS);
		return 1;
	}

	char* ok = NULL;

	lista_t* doctores_lista = csv_crear_estructura(argv[1], constructor_doctor, NULL);
	if(!doctores_lista){
		printf(ENOENT_ARCHIVO, argv[1]);
		return 1;
	} 
	
	lista_t* pacientes_lista = csv_crear_estructura(argv[2], constructor_paciente, ok);
	if(!pacientes_lista){
		destruccion_listas(NULL, doctores_lista);
		printf(ENOENT_ARCHIVO, argv[2]);
		return 1;
	}

	if(ok){
		destruccion_listas(pacientes_lista, doctores_lista);
		printf(ENOENT_ANIO, ok);
		return 1;
	}
	
	datos_t* datos = crear_datos();
	if(!datos){
		destruccion_listas(pacientes_lista, doctores_lista);
		return 1;
	}

	if(!procesar_datos_doctores(datos, doctores_lista) || !procesar_datos_pacientes(datos, pacientes_lista)){
		destruccion_listas(pacientes_lista, doctores_lista);
		destruccion_datos(datos);
		return 1;
	}

	turno_t* turnos = turno_crear();
	if(!turnos){
		destruccion_listas(pacientes_lista, doctores_lista);
		destruccion_datos(datos);
		return 1;
	}

	procesar_entrada(turnos, datos);

	destruccion_listas(pacientes_lista, doctores_lista);
	destruccion_datos(datos);
	turnos_destruir(turnos);
	return 0;
}