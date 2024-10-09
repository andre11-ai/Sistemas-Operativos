// Nombre del equipo: S.O. AGREVAL
// Fecha: 24/09/2024
// Version: 1.1.2
// Simulación de un comedor militar con múltiples soldados que desean comer en diferentes
// mostradores de comida y postre. Algunos soldados también necesitan abrir bebidas con
// abridores limitados.
// Hay 1000 soldados que intentan comer en un comedor con 5 mostradores de comida y 5
// mostradores de postre.
// Además, hay 60 abridores disponibles que los soldados pueden usar si eligen una bebida que
// requiere uno.
// Los soldados esperan su turno si los recursos (mostradores o abridores) están ocupados.
// El programa utiliza semáforos para gestionar los mostradores y los abridores, y los
// soldados se representan mediante hilos.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SOLDADOS 1000        // Número total de soldados
#define MOSTRADORES_COMIDA 5 // Número de mostradores de comida
#define MOSTRADORES_POSTRE 5 // Número de mostradores de postre
#define ABRIDORES 60         // Número de abridores disponibles

// Semáforos que controlan el acceso a los mostradores y abridores
sem_t mostradores_comida; // Semáforo para los mostradores de comida
sem_t mostradores_postre; // Semáforo para los mostradores de postre
sem_t abridores;          // Semáforo para los abridores

void *soldado(void *arg){

    int id = *((int *)arg); // Obtener el identificador del soldado

    // Simulación de un retraso inicial para evitar que todos los soldados lleguen al mismo tiempo
    usleep(4000000); // 4 segundos
    printf("Soldado %d quiere comer.\n", id);

    // El soldado intenta servirse comida en un mostrador disponible
    sem_wait(&mostradores_comida); // Espera si no hay mostradores de comida disponibles
    printf("Soldado %d está en un mostrador de comida.\n", id);

    // El soldado decide si necesita un abridor (50% de probabilidad)
    if (rand() % 2 == 1){

        sem_wait(&abridores); // Espera si no hay abridores disponibles
        printf("Soldado %d está usando un abridor.\n", id);
        sleep(4);             // Simula el tiempo para abrir una bebida
        sem_post(&abridores); // Libera el abridor
        printf("Soldado %d devolvió el abridor.\n", id);

    }

    // Simula el tiempo que tarda en servirse la comida
    sleep(4);
    sem_post(&mostradores_comida); // Libera el mostrador de comida
    printf("Soldado %d terminó de servir su comida.\n", id);

    // El soldado decide si quiere postre (50% de probabilidad)
    if (rand() % 2 == 1){

        sem_wait(&mostradores_postre); // Espera si no hay mostradores de postre disponibles
        printf("Soldado %d está en un mostrador de postre.\n", id);
        sleep(4);                      // Simula el tiempo para servirse postre
        sem_post(&mostradores_postre); // Libera el mostrador de postre
        printf("Soldado %d terminó de servirse el postre.\n", id);

    }

    // El soldado termina su comida y sale del comedor
    printf("Soldado %d terminó de comer y sale del comedor.\n", id);
    return NULL;

}

int main(){

    pthread_t soldados[SOLDADOS]; // Arreglo de hilos para los soldados
    int id_soldado[SOLDADOS];     // Arreglo para los identificadores de los soldados

    // Inicializar los semáforos
    sem_init(&mostradores_comida, 0, MOSTRADORES_COMIDA); // 5 mostradores de comida
    sem_init(&mostradores_postre, 0, MOSTRADORES_POSTRE); // 5 mostradores de postre
    sem_init(&abridores, 0, ABRIDORES);                   // 60 abridores

    // Crear un hilo por cada soldado
    for (int i = 0; i < SOLDADOS; i++){

        id_soldado[i] = i + 1; // Asignar un identificador a cada soldado
        pthread_create(&soldados[i], NULL, soldado, &id_soldado[i]);
        sleep(2); // Retraso de 2 segundos entre la creación de cada soldado para escalonar la entrada

    }

    // Esperar a que todos los hilos de soldados terminen
    for (int i = 0; i < SOLDADOS; i++){

        pthread_join(soldados[i], NULL);
    
    }

    // Destruir los semáforos al finalizar
    sem_destroy(&mostradores_comida);
    sem_destroy(&mostradores_postre);
    sem_destroy(&abridores);

    return 0;
    
}