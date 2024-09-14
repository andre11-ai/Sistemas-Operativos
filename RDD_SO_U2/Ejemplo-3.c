// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.1 del Ejemplo 3 Dada por el profesor

// En este modelo, varios hilos de usuario se mapean a un número menor de hilos del sistema operativo,
// permitiendo una implementación más eficiente y adaptativa de hilos.

// Código 3. Modelo de Hilos Independientes (M:N Mapping).

#include <stdio.h>
#include <pthread.h>

// Función que será ejecutada por cada hilo
void *funcion_hilo(void *arg)
{
    printf("Hilo ejecutado: %d\n", *((int *)arg)); // Imprimir el ID del hilo
    pthread_exit(NULL);                            // Terminar el hilo
}

int main()
{
    pthread_t hilos[4];       // Array para almacenar los identificadores de los hilos
    int ids[] = {1, 2, 3, 4}; // Array de IDs de los hilos

    // Crear hilos
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&hilos[i], NULL, funcion_hilo, (void *)&ids[i]); // Crear un nuevo hilo
    }

    // Esperar la finalización de los hilos
    for (int i = 0; i < 4; i++)
    {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo con el ID correspondiente termine
    }

    return 0;
}