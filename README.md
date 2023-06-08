<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

- Para compilar y correr pruebas locales con makefile:

```
make
```

- Para compilar y correr ejemplo con makefile:

```
make valgrind-ejemplo
```

- Para compilar y correr pruebas de la catedra con makefile:

```
make valgrind-chanutron
```
---
##  Funcionamiento

Este programa implementa el TDA Hash, o tabla de Hash, con su iterador interno. El programa recibe los datos necesarios que entrega el usuario (claves, valores, funciones, etc.), y realiza las operaciones válidas del TDA. Particularmente, al crear el TDA, recibe un numero entero positivo que va a ser la capacidad inicial de la tabla. En caso de exceder esa capacidad, el Hash se encarga de agrandar esa capacidad para mantener funcional a la tabla, operacion que vamos a llamar "rehashear".
Por otro lado, para las demás operaciones reciben claves que están emparejadas con el valor que representan, con lo que el TDA maneja únicamente las claves mediante una función, la cual vamos a llamar función de Hash.
### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas

1. Qué es un diccionario

3. Qué es una función de hash y qué características debe tener

4. Qué es una tabla de Hash y sus diferentes métodos de resolución de colisiones 
