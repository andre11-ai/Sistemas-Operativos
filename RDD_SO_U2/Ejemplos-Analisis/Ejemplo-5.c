// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.1 del Ejemplo 5 Dada por el profesor

// En este modelo, los hilos son gestionados completamente  a nivel de usuario sin soporte directo
// del sistema operativo, proporcionando una implementación más ligera y eficiente de hilos.

// Código 5. Modelo de Hilos Ligeros (Lightweight Threads).

#include <stdio.h>
#include <pthread.h>

// Función que será ejecutada por cada hilo pesado
void *funcion_hilo_pesado(void *arg)
{
    printf("Hilo pesado ejecutado: %d\n", *((int *)arg)); // Imprimir el ID del hilo pesado
    pthread_exit(NULL);                                   // Terminar el hilo pesado
}

int main()
{
    pthread_t hilos[3];    // Array para almacenar los identificadores de los hilos pesados
    int ids[] = {1, 2, 3}; // Array de IDs de los hilos pesados

    // Crear hilos pesados
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&hilos[i], NULL, funcion_hilo_pesado, (void *)&ids[i]); // Crear un nuevo hilo pesado
    }

    // Esperar la finalización de los hilos
    for (int i = 0; i < 3; i++)
    {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo pesado con el ID correspondiente termine
    }

    return 0;
}
