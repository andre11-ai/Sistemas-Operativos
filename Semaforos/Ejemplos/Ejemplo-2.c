// Nombre del equipo: S.O. AGREVAL
// Fecha: 25/09/2024
// Versión: 1.1.0
// Programa para simular la llegada de clientes a una sucursal bancaria y la operación
// de un furgón blindado que transporta dinero.
// En una sucursal bancaria, los clientes llegan de manera aleatoria, y cuando se
// acumulan 20 clientes, un furgón blindado es llamado para realizar una operación
// de carga o descarga de dinero. Los semáforos y mutex protegen las variables compartidas
// y aseguran la correcta sincronización entre la llegada de clientes y las operaciones del furgón.
// Este programa utiliza semáforos para coordinar el número de clientes en la sucursal
// y permitir que el furgón realice la operación solo cuando haya suficientes clientes.
// Un mutex garantiza el acceso exclusivo a la variable compartida que cuenta los clientes.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CLIENTES 100       // Número máximo de clientes en la sucursal
#define CLIENTES_POR_FURGON 20 // Número de clientes necesarios para que el furgón llegue

// Definir semáforos y variables de control
sem_t clientes_en_sucursal; // Indica si hay clientes en la sucursal
sem_t operacion_en_curso;   // Controla si el furgón está realizando una operación
pthread_mutex_t mutex;      // Protege el acceso a la variable clientes
int clientes = 0;           // Número de clientes en la sucursal

void *llegada_cliente(void *arg){

    while (1){

        usleep(rand() % 3000000);   // Simula la llegada aleatoria de clientes
        pthread_mutex_lock(&mutex); // Bloquea el acceso a la variable clientes
        clientes++;
        printf("Cliente entró a la sucursal. Clientes en la sucursal: %d\n", clientes);

        // Si hay 20 clientes y no se supera el máximo, el furgón llega
        if (clientes % CLIENTES_POR_FURGON == 0 && clientes <= MAX_CLIENTES){

            printf("\n¡El furgón blindado está llegando! La sucursal se está vaciando...\n\n");
            sem_wait(&operacion_en_curso); // Espera a que el furgón complete su operación

            // Simula que los clientes salen de la sucursal
            for (int i = clientes; i > 0; i--){

                printf("Cliente salió de la sucursal. Clientes en la sucursal: %d\n", i - 1);
                usleep(500000); // Simula el tiempo de salida de cada cliente
            }

            // Furgón realiza la operación
            printf("\nEl furgón blindado puede realizar la operación ahora.\n");
            sem_post(&operacion_en_curso); // Libera el semáforo para permitir la operación
        }

        pthread_mutex_unlock(&mutex);    // Libera el mutex
        sem_post(&clientes_en_sucursal); // Indica que hay clientes en la sucursal
    }

    return NULL;
}

void *operacion_furgon(void *arg){

    while (1){

        sem_wait(&clientes_en_sucursal); // Espera hasta que haya clientes en la sucursal

        // Si hay 20 clientes en la sucursal y no se ha alcanzado el máximo
        if (clientes % CLIENTES_POR_FURGON == 0 && clientes <= MAX_CLIENTES){

            sem_wait(&operacion_en_curso); // Bloquea el semáforo para realizar la operación
            printf("Furgón blindado realizando la operación de carga/descarga de dinero...\n");
            usleep(rand() % 2000000);      // Simula el tiempo de la operación
            sem_post(&operacion_en_curso); // Libera el semáforo al terminar la operación
            printf("Furgón blindado completó la operación.\n");
        }
    }

    return NULL;
}

int main(){

    pthread_t hilo_clientes, hilo_furgon;

    // Inicialización de semáforos y mutex
    sem_init(&clientes_en_sucursal, 0, 0);
    sem_init(&operacion_en_curso, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Creación de hilos para simular la llegada de clientes y la operación del furgón
    pthread_create(&hilo_clientes, NULL, llegada_cliente, NULL);
    pthread_create(&hilo_furgon, NULL, operacion_furgon, NULL);

    // Espera a que los hilos terminen (en este caso, nunca lo harán)
    pthread_join(hilo_clientes, NULL);
    pthread_join(hilo_furgon, NULL);

    // Destrucción de semáforos y mutex
    sem_destroy(&clientes_en_sucursal);
    sem_destroy(&operacion_en_curso);
    pthread_mutex_destroy(&mutex);

    return 0;

}