#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7

typedef struct nodo {
	char *clave;
	void *elemento;
	nodo_t *siguiente;
} nodo_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	nodo_t **vector;
};

size_t funcion_hash(char *clave)
{

}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;

	hash->vector = calloc(capacidad, sizeof(nodo_t *));
	if (!hash->vector) {
		free(hash);
		return NULL;
	}
	hash->capacidad = capacidad;
	hash->cantidad = 0;

	return hash;
}

nodo_t *crear_nodo(char *clave, void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;

	nodo->clave = clave;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

nodo_t *buscar_nodo_por_clave(nodo_t *nodo, char *clave)
{
	if (!nodo)
		return NULL;

	if (!strcmp(nodo->clave, clave))
		return nodo;

	return buscar_nodo_por_clave(nodo->siguiente, clave);
}

void rehash(hash_t *hash)
{

}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = funcion_hash(clave);

	nodo_t *nodo = hash->vector[posicion];
	while (nodo != NULL) {
		if (!strcmp(nodo->clave, clave)) {
			nodo->elemento = elemento;
			return hash;
		}

		nodo = nodo->siguiente;
	}
	nodo_t *nodo = crear_nodo(clave, elemento);
	if (!nodo)
		return NULL;

	hash->vector[posicion] = nodo;

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	size_t posicion = funcion_hash(clave);
	nodo_t *nodo = buscar_nodo_por_clave(hash->vector[posicion], clave);
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	size_t posicion = funcion_hash(clave);
	nodo_t *nodo = buscar_nodo_por_clave(hash->vector[posicion], clave);
	return nodo->elemento;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	size_t posicion = funcion_hash(clave);
	nodo_t *nodo = buscar_nodo_por_clave(hash->vector[posicion], clave);
	return nodo != NULL;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;

	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;

	return n;
}
