// Nombre del equipo: S.O. AGREVAL
// Fecha: 25/09/2024
// Version: 1.1.0
// Programa para simular el acceso sincronizado a una sección crítica por parte de dos hilos utilizando semáforos.
// Este programa crea dos hilos: el hilo principal y un hilo secundario. Ambos hilos
// tienen acceso a una sección crítica protegida por un semáforo. El semáforo asegura
// que un solo hilo puede acceder a la sección crítica a la vez.
// El semáforo `mutex` se utiliza para garantizar que los hilos no ingresen a la sección
// crítica simultáneamente. El hilo secundario imprime un mensaje cuando entra en la
// sección crítica, y el hilo principal lo hace también en su respectiva sección crítica.
// El programa asegura que el hilo secundario complete su ejecución antes de que el
// hilo principal acceda a su sección crítica, evitando problemas de sincronización.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declaración del semáforo
sem_t mutex;

/*
 * Función del hilo secundario.
 * Este hilo accede a la sección crítica, imprime un mensaje y luego libera el semáforo.
 */
void *thread_func(void *arg){

    sem_wait(&mutex); // Bloquea el semáforo para acceder a la sección crítica
    printf("Sección critica del hilo\n");
    sem_post(&mutex); // Libera el semáforo
    return NULL;

}

int main(){

    pthread_t thread;

    // Inicialización del semáforo con valor 1 (disponibilidad inicial)
    sem_init(&mutex, 0, 1);

    // Crear el hilo secundario
    pthread_create(&thread, NULL, thread_func, NULL);

    // Esperar a que el hilo secundario termine su ejecución
    pthread_join(thread, NULL);

    // Sección crítica del hilo principal
    sem_wait(&mutex); // Bloquea el semáforo para acceder a la sección crítica
    printf("Sección critica del hilo principal\n");
    sem_post(&mutex); // Libera el semáforo

    // Destruye el semáforo
    sem_destroy(&mutex);

    return 0;
    
}
