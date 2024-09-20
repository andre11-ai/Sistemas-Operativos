// Código 2. Bibliotecas.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Para usar la función sleep

// Estructura para pasar múltiples argumentos a la función del hilo
typedef struct {
    int thread_id;
    char* order;
    int preparation_time;
} ThreadArgs;

// Función que se ejecutará en el primer hilo (Cocinero 1)
void* prepareOrder1(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    printf("Cocinero %d: Preparando %s...\n", thread_args->thread_id, thread_args->order);
    sleep(thread_args->preparation_time); // Simula el tiempo de preparación
    printf("Cocinero %d: %s listo!\n", thread_args->thread_id, thread_args->order);
    pthread_exit(NULL); // Terminar el hilo
}

// Función que se ejecutará en el segundo hilo (Cocinero 2)
void* prepareOrder2(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    printf("Cocinero %d: Preparando %s...\n", thread_args->thread_id, thread_args->order);
    sleep(thread_args->preparation_time); // Simula el tiempo de preparación
    printf("Cocinero %d: %s listo!\n", thread_args->thread_id, thread_args->order);
    pthread_exit(NULL); // Terminar el hilo
}

int main() {
    // Definir la estructura de argumentos para cada cocinero
    ThreadArgs args1 = {1, "Hamburguesa con papas", 3};  // Pedido 1: Hamburguesa con papas (3 segundos)
    ThreadArgs args2 = {2, "Pizza grande", 5};           // Pedido 2: Pizza grande (5 segundos)

    // Declarar las variables de hilo
    pthread_t thread1, thread2;

    // Crear los hilos y pasar las funciones junto con los argumentos
    if (pthread_create(&thread1, NULL, prepareOrder1, (void*)&args1) != 0) {
        perror("Error al crear el hilo para el primer cocinero"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, prepareOrder2, (void*)&args2) != 0) {
        perror("Error al crear el hilo para el segundo cocinero"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen su ejecución
    if (pthread_join(thread1, NULL) != 0) {
        perror("Error al unir el hilo del primer cocinero"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Error al unir el hilo del segundo cocinero"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    // Imprimir mensaje del hilo principal
    printf("Hilo principal: Ambos pedidos están listos.\n");

    return 0;
}
