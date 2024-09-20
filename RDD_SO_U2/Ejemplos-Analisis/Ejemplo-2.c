// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.1 del Ejemplo 2 Dada por el profesor

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Código 2. Hilos asíncronos.

// Estructura para pasar múltiples argumentos a la función del hilo
typedef struct
{
    int thread_id;
    char *message;
} ThreadArgs;

// Función que se ejecutará en el primer hilo
void *threadFunction1(void *args)
{
    ThreadArgs *thread_args = (ThreadArgs *)args;
    printf("Hilo %d: %s\n", thread_args->thread_id, thread_args->message);
    pthread_exit(NULL); // Terminar el hilo
}

// Función que se ejecutará en el segundo hilo
void *threadFunction2(void *args)
{
    ThreadArgs *thread_args = (ThreadArgs *)args;
    printf("Hilo %d: %s\n", thread_args->thread_id, thread_args->message);
    pthread_exit(NULL); // Terminar el hilo
}

int main()
{
    // Definir la estructura de argumentos para cada hilo
    ThreadArgs args1 = {1, "Hola desde el primer hilo!"};
    ThreadArgs args2 = {2, "Hola desde el segundo hilo!"};

    // Declarar las variables de hilo
    pthread_t thread1, thread2;

    // Crear los hilos y pasar las funciones junto con los argumentos
    if (pthread_create(&thread1, NULL, threadFunction1, (void *)&args1) != 0)
    {
        perror("Error al crear el primer hilo"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, threadFunction2, (void *)&args2) != 0)
    {
        perror("Error al crear el segundo hilo"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen su ejecución
    if (pthread_join(thread1, NULL) != 0)
    {
        perror("Error al unir el primer hilo"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0)
    {
        perror("Error al unir el segundo hilo"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    // Imprimir mensaje del hilo principal
    printf("Hilo principal: Ambos hilos han terminado su ejecución.\n");

    return 0;
}