#include "pa2m.h"
#include "src/hash.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACIDAD 50
#define CAPACIDAD_REHASH 5
#define MAX_CLAVE 10
#define MAX_VECTOR 100

typedef struct {
	size_t id;
	size_t salud;
	char *nombre_entrenador;
	char *nombre;
} pkm_para_destruir_t;

typedef struct par {
	int valor;
	char clave[MAX_CLAVE];
} par_t;

bool leer_valores(const char *clave, void *valor_ingresado, void *aux)
{
	if (!clave)
		return false;

	aux = aux;
	int *valor = valor_ingresado;
	printf("La clave %s guarda: %i\n", clave, *valor);
	return true;
}

bool leer_primeros_5(const char *clave, void *valor_ingresado, void *aux)
{
	if (!clave)
		return false;

	int *contador = aux;
	int *valor = valor_ingresado;
	printf("La clave %s guarda: %i\n", clave, *valor);
	*contador = *contador + 1;
	if (*contador < 5)
		return true;

	return false;
}

void pruebas_de_creacion_y_destruccion_del_hash()
{
	hash_t *hash1 = hash_crear(CAPACIDAD);
	pa2m_afirmar(hash1 != NULL,
		     "Se puede crear una tabla de hash con exito");
	pa2m_afirmar(!hash_cantidad(hash1), "La tabla de hash esta vacia");

	hash_destruir(hash1);

	hash_t *hash2 = hash_crear(1);
	pa2m_afirmar(
		hash2 != NULL,
		"Se puede crear una tabla de hash con una capacidad menor a 3");

	hash_destruir(hash2);
}

void pruebas_insertar_y_destruir()
{
	hash_t *hash = hash_crear(CAPACIDAD);
	par_t par[MAX_VECTOR];
	void *anterior = NULL;
	int numeros[] = { 1, 2 };

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");

	pa2m_afirmar(hash_insertar(hash, par[0].clave, &numeros[0],
				   &anterior) != NULL,
		     "Se puede insertar un valor en la tabla de hash");

	pa2m_afirmar(hash_insertar(hash, par[1].clave, NULL, &anterior) != NULL,
		     "Se puede insertar un NULL en la tabla de hash");

	pa2m_afirmar(
		!anterior,
		"No se encuentra un valor anterior, si no insertan claves repetidas");

	pa2m_afirmar(
		hash_insertar(hash, par[2].clave, &numeros[0], &anterior) !=
			NULL,
		"Se pueden insertar valores iguales con claves diferentes");

	pa2m_afirmar(hash_insertar(hash, par[0].clave, &numeros[1],
				   &anterior) != NULL,
		     "Se puede modificar un valor insertado");

	int *valor_anterior = (int *)anterior;
	pa2m_afirmar(
		*valor_anterior == numeros[0],
		"Se puede encontrar el anterior valor insertado con la misma clave");

	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "Se insertar 3 valores y la tabla tiene 3");

	hash_destruir(hash);
}

void pruebas_quitar_y_destruir()
{
	hash_t *hash = hash_crear(CAPACIDAD);
	par_t par[MAX_VECTOR];
	int numeros[] = { 1, 2, 3, 4, 5, 6, 7 };
	void *anterior = NULL;

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");
	strcpy(par[3].clave, "Clave4");
	strcpy(par[4].clave, "Clave5");
	strcpy(par[5].clave, "Clave6");
	strcpy(par[6].clave, "Clave7");

	pa2m_afirmar(!hash_quitar(hash, par[0].clave),
		     "No se pueden quitar valores de un hash vacio");

	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		par[i].valor = numeros[i];
		hash_insertar(hash, par[i].clave, &par[i].valor, NULL);
	}

	for (int i = 1; i < 6; i++) {
		int *valor = hash_quitar(hash, par[i].clave);
		pa2m_afirmar(*valor == numeros[i],
			     "Se puede quitar un valor de la tabla de hash");
	}

	par[6].valor = 10;
	hash_insertar(hash, par[6].clave, &par[6].valor, &anterior);
	pa2m_afirmar(hash_quitar(hash, par[6].clave) == &par[6].valor,
		     "Quitar un valor modificado devuelve el valor correcto");

	pa2m_afirmar(
		!hash_quitar(hash, par[6].clave),
		"Quitar un valor ya quitado (no esta mas en el hash) devuelve NULL");

	pa2m_afirmar(!hash_quitar(hash, "Clave_que_no_existe"),
		     "No se puede quitar un valor que no se inserto");

	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "Se insertan 7 valores, se quitan 6, y la tabla tiene 1");

	hash_destruir(hash);
}

void pruebas_buscar_valores_por_clave()
{
	hash_t *hash = hash_crear(CAPACIDAD);
	par_t par[MAX_VECTOR];
	int numeros[] = { 1, 2, 3, 4, 5 };
	void *anterior = NULL;

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");
	strcpy(par[3].clave, "Clave4");
	strcpy(par[4].clave, "Clave5");

	pa2m_afirmar(!hash_contiene(hash, par[0].clave),
		     "No se encuentran valores en una tabla de hash vacia");

	pa2m_afirmar(!hash_obtener(hash, par[0].clave),
		     "No se obtienen valores de una tabla de hash vacia");

	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		par[i].valor = numeros[i];
		hash_insertar(hash, par[i].clave, &par[i].valor, NULL);
	}

	for (int i = 0; i < 4; i++) {
		pa2m_afirmar(hash_contiene(hash, par[i].clave),
			     "Se puede encontrar el valor en la tabla de hash");

		int *valor = hash_obtener(hash, par[i].clave);

		pa2m_afirmar(
			*valor == numeros[i],
			"Se puede obtener el valor encontrado en la tabla");
	}

	par[4].valor = 10;
	hash_insertar(hash, par[4].clave, &par[4].valor, &anterior);
	pa2m_afirmar(hash_contiene(hash, par[4].clave),
		     "Se puede encontrar el valor modificado en la tabla");

	pa2m_afirmar(hash_obtener(hash, par[4].clave) == &par[4].valor,
		     "Se puede obtener el valor modificado de la tabla");

	pa2m_afirmar(!hash_contiene(hash, "Clave_que_no_existe"),
		     "No se puede encontrar un valor que no se inserto");

	pa2m_afirmar(!hash_obtener(hash, "Clave_que_no_existe"),
		     "No se puede obtener un valor que no se inserto");

	hash_quitar(hash, par[0].clave);
	pa2m_afirmar(!hash_contiene(hash, par[0].clave),
		     "No se puede encontrar un valor quitado del hash");

	pa2m_afirmar(!hash_obtener(hash, par[0].clave),
		     "No se puede obtener un valor quitado del hash");

	hash_destruir(hash);
}

void pruebas_insertar_y_rehashear()
{
	hash_t *hash = hash_crear(CAPACIDAD_REHASH);
	par_t par[MAX_VECTOR];
	bool hubo_error = false;

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");
	strcpy(par[3].clave, "Clave4");
	strcpy(par[4].clave, "Clave5");
	strcpy(par[5].clave, "Clave6");
	strcpy(par[6].clave, "Clave7");
	strcpy(par[7].clave, "Clave8");

	int i;
	for (i = 0; i < 3; i++) {
		par[i].valor = i;
		hash_insertar(hash, par[i].clave, &par[i].valor, NULL);
	}
	par[i].valor = i;
	pa2m_afirmar(hash_insertar(hash, par[i].clave, &par[i].valor, NULL) !=
			     NULL,
		     "Se provoca un rehash y no se genera un error");

	for (int i = 0; i < hash_cantidad(hash); i++) {
		if (!hash_contiene(hash, par[i].clave))
			hubo_error = true;
	}
	pa2m_afirmar(!hubo_error && hash_cantidad(hash) == 4,
		     "Se encuentran todos los valores despues del rehash");
	hubo_error = false;

	for (i = (int)hash_cantidad(hash); i < 7; i++) {
		par[i].valor = i;
		if (!hash_insertar(hash, par[i].clave, &par[i].valor, NULL))
			hubo_error = true;
	}
	pa2m_afirmar(!hubo_error && hash_cantidad(hash) == 7,
		     "Se pueden seguir insertando valores sin error");
	hubo_error = false;

	par[i].valor = i;
	pa2m_afirmar(hash_insertar(hash, par[i].clave, &par[i].valor, NULL) !=
			     NULL,
		     "Se provoca otro rehash y no se genera un error");

	for (int i = 0; i < hash_cantidad(hash); i++) {
		if (!hash_contiene(hash, par[i].clave))
			hubo_error = true;
	}
	pa2m_afirmar(!hubo_error && hash_cantidad(hash) == 8,
		     "Se encuentran todos los valores despues del rehash");
	hubo_error = false;

	for (int i = 0; i < 8; i++) {
		if (hash_quitar(hash, par[i].clave) != &par[i].valor)
			hubo_error = true;

		if (hash_contiene(hash, par[i].clave))
			hubo_error = true;
	}
	pa2m_afirmar(!hubo_error && !hash_cantidad(hash),
		     "Se pueden quitar todos los valores correctamente");
	hubo_error = false;

	char clave[MAX_VECTOR];
	memset(clave, 0, MAX_VECTOR);
	for (i = 0; i < 55; i++) {
		for (int j = 0; j < 94; j++) {
			clave[i] = (char)(j + 32);
			if (!hash_insertar(hash, clave, NULL, NULL))
				hubo_error = true;
		}
	}

	pa2m_afirmar(
		!hubo_error && hash_cantidad(hash) == 5170,
		"Se pueden insertar 5170 valores y el rehash no genera error");
	hubo_error = false;

	memset(clave, 0, MAX_VECTOR);
	for (i = 0; i < 55; i++) {
		for (int j = 0; j < 94; j++) {
			clave[i] = (char)(j + 32);
			if (!hash_contiene(hash, clave))
				hubo_error = true;
		}
	}

	pa2m_afirmar(!hubo_error,
		     "Se pueden encontrar los 5170 valores insertados");
	hubo_error = false;

	hash_destruir(hash);
}

void pruebas_hash_iterador_interno()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	pa2m_afirmar(!hash_con_cada_clave(hash, leer_valores, NULL),
		     "Iterar un hash vacio devuelve 0 valores iterados");

	par_t par[MAX_VECTOR];
	int numeros[] = { 1, 2, 3, 4, 5, 6, 7 };
	int contador = 0;

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");
	strcpy(par[3].clave, "Clave4");
	strcpy(par[4].clave, "Clave5");
	strcpy(par[5].clave, "Clave6");
	strcpy(par[6].clave, "Clave7");

	for (int i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		par[i].valor = numeros[i];
		hash_insertar(hash, par[i].clave, &par[i].valor, NULL);
	}

	printf("\n");
	pa2m_afirmar(hash_con_cada_clave(hash, leer_valores, NULL) ==
			     hash_cantidad(hash),
		     "Se puede iterar el hash y se leen todos los elementos");

	printf("\n");
	pa2m_afirmar(hash_con_cada_clave(hash, leer_primeros_5, &contador) == 5,
		     "Se puede iterar el hash y se leen todos los elementos");

	hash_destruir(hash);
}

void pruebas_de_operaciones_del_tda_hash()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_de_creacion_y_destruccion_del_hash();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR VALORES Y DESTRUIR HASH");
	pruebas_insertar_y_destruir();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR VALORES Y DESTRUIR HASH");
	pruebas_quitar_y_destruir();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR VALORES POR CLAVE");
	pruebas_buscar_valores_por_clave();

	pa2m_nuevo_grupo("PRUEBAS DEL ITERADOR INTERNO");
	pruebas_hash_iterador_interno();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR Y REHASHEAR");
	pruebas_insertar_y_rehashear();
}

/*
-----------------------------------------------------------------------------
*/

void pruebas_de_destruir_todo_en_el_hash()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	par_t par[MAX_VECTOR];
	void *anterior = NULL;

	strcpy(par[0].clave, "Clave1");
	strcpy(par[1].clave, "Clave2");
	strcpy(par[2].clave, "Clave3");
	strcpy(par[3].clave, "Clave4");
	strcpy(par[4].clave, "Clave5");

	int i = 0;
	hash_insertar(hash, par[i].clave, malloc(sizeof(int)), NULL);

	i++;
	hash_insertar(hash, par[i].clave, malloc(sizeof(float)), NULL);

	i++;
	hash_insertar(hash, par[i].clave, malloc(sizeof(char)), NULL);

	i++;
	hash_insertar(hash, par[i].clave, malloc(sizeof(void *)), NULL);

	i++;
	hash_insertar(hash, par[i].clave, malloc(sizeof(pkm_para_destruir_t)),
		      NULL);

	i++;
	hash_insertar(hash, par[2].clave, malloc(sizeof(char)), &anterior);

	free(anterior); //No se pierde memoria, si se devuelve y se libera correctamente el valor reservado
	hash_destruir_todo(hash, free);
}

/*
-------------------------------------------------------------------------------
*/

void pruebas_del_tda_hash_con_parametros_nulos()
{
	hash_t *hash = hash_crear(CAPACIDAD);
	const char clave[MAX_CLAVE] = "Clave";

	pa2m_afirmar(!hash_insertar(NULL, clave, NULL, NULL),
		     "Insertar valores a un hash que no existe da error");

	pa2m_afirmar(!hash_insertar(hash, NULL, NULL, NULL),
		     "Insertar valores con una clave que no existe da error");

	pa2m_afirmar(!hash_quitar(NULL, clave),
		     "Quitar valores de un hash que no existe da error");

	pa2m_afirmar(!hash_quitar(hash, NULL),
		     "Quitar valores con una clave que no existe da error");

	pa2m_afirmar(!hash_obtener(NULL, clave),
		     "Obtener valores de un hash que no existe da error");

	pa2m_afirmar(!hash_obtener(hash, NULL),
		     "Obtener valores con una clave que no existe da error");

	pa2m_afirmar(!hash_contiene(NULL, clave),
		     "Buscar valores de un hash que no existe da error");

	pa2m_afirmar(!hash_contiene(hash, NULL),
		     "Buscar valores con una clave que no existe da error");

	pa2m_afirmar(!hash_cantidad(NULL),
		     "Un tabla de hash que no existe tiene 0 valores");

	pa2m_afirmar(!hash_con_cada_clave(NULL, leer_valores, NULL),
		     "Iterar una tabla de hash que no existe da error");

	pa2m_afirmar(
		!hash_con_cada_clave(hash, NULL, NULL),
		"Iterar una tabla de hash con una funcion que no existe da error");

	hash_destruir(hash);
}

/*
-------------------------------------------------------------------------------
*/

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-HASH -----------");

	pa2m_nuevo_grupo(
		"--- PRUEBAS DE LAS OPERACIONES DE LA TABLA DE HASH ---");
	pruebas_de_operaciones_del_tda_hash();
	printf("\n");

	pa2m_nuevo_grupo("--- PRUEBAS DEL DESTRUCTOR DE LA TABLA DE HASH ---");
	printf("Liberar la tabla de hash y sus valores no debe perder memoria");
	pruebas_de_destruir_todo_en_el_hash();
	printf("\n");

	pa2m_nuevo_grupo("--- PRUEBAS DE FUNCIONES CON PARAMETROS NULOS ---");
	pruebas_del_tda_hash_con_parametros_nulos();

	return pa2m_mostrar_reporte();
}
