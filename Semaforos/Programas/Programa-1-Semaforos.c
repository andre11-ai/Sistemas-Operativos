// Nombre del equipo: S.O. AGREVAL
// Fecha: 24/09/2024
// Version: 1.1.0
// Programa para simular el funcionamiento de una nave industrial que coordina una máquina
// de inyección, un robot de embalaje y un operario de control de calidad, utilizando
// semáforos y mutex.
// Una máquina de inyección deposita piezas en una cinta transportadora de capacidad limitada.
// Un robot recoge las piezas de la cinta una a la vez y las embala.
// Un operario realiza controles de calidad de 3 piezas si hay suficientes de capacidad limitada.
// Si no hay suficientes, espera hasta que estén disponibles.
// El programa utiliza semáforos para coordinar el espacio disponible en la cinta y las
// piezas disponibles para ser recogidas, y un mutex para proteger el acceso a la variable
// compartida que representa el número de piezas en la cinta.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACIDAD_CINTA 10 // Tamaño máximo de la cinta transportadora
#define TIEMPO_INYECCION 1 // Tiempo en segundos que tarda la máquina en inyectar una pieza
#define TIEMPO_RECOGIDA 2  // Tiempo en segundos que tarda el robot en recoger una pieza
#define TIEMPO_CONTROL 3   // Tiempo en segundos que tarda el operario en hacer control de calidad

// Semáforos para gestionar el espacio y las piezas en la cinta
sem_t espacio_disponible; // Semáforo que indica si hay espacio disponible en la cinta
sem_t piezas_disponibles; // Semáforo que indica si hay piezas disponibles en la cinta

// Mutex para proteger el acceso concurrente a la variable piezas_en_cinta
pthread_mutex_t mutex_cinta;

// Variable compartida que lleva el número de piezas en la cinta
int piezas_en_cinta = 0;

void *maquina_inyeccion(void *arg){

    while (1){

        sem_wait(&espacio_disponible); // Espera a que haya espacio en la cinta
        sleep(TIEMPO_INYECCION);       // Simula el tiempo de inyección de una pieza

        // Sección crítica: modificar el número de piezas en la cinta
        pthread_mutex_lock(&mutex_cinta);
        piezas_en_cinta++; // Añadir una pieza a la cinta
        printf("Máquina inyecta una pieza. Piezas en cinta: %d\n", piezas_en_cinta);
        pthread_mutex_unlock(&mutex_cinta);

        sem_post(&piezas_disponibles); // Indica que hay una nueva pieza disponible
    }

    return NULL;
}


void *robot_recoge(void *arg){

    while (1){

        sem_wait(&piezas_disponibles); // Espera a que haya piezas en la cinta
        sleep(TIEMPO_RECOGIDA);        // Simula el tiempo de recogida de una pieza

        // Sección crítica: modificar el número de piezas en la cinta
        pthread_mutex_lock(&mutex_cinta);
        piezas_en_cinta--; // Retirar una pieza de la cinta
        printf("Robot recoge una pieza. Piezas en cinta: %d\n", piezas_en_cinta);
        pthread_mutex_unlock(&mutex_cinta);

        sem_post(&espacio_disponible); // Indica que hay más espacio en la cinta
    }
    
    return NULL;
}


void *operario_control_calidad(void *arg){

    while (1){

        sleep(TIEMPO_CONTROL); // Simula el tiempo entre controles de calidad

        // Sección crítica: acceso al número de piezas en la cinta
        pthread_mutex_lock(&mutex_cinta);
        if (piezas_en_cinta >= 3){

            printf("Operario realiza control de calidad con 3 piezas.\n");
        }
        else{

            printf("Operario no encuentra suficientes piezas para control de calidad.\n");
        }

        pthread_mutex_unlock(&mutex_cinta);

    }

    return NULL;
}

int main(){

    pthread_t hilo_maquina, hilo_robot, hilo_operario;

    // Inicialización de los semáforos
    sem_init(&espacio_disponible, 0, CAPACIDAD_CINTA); // Inicia con todos los espacios disponibles
    sem_init(&piezas_disponibles, 0, 0);               // No hay piezas al inicio
    pthread_mutex_init(&mutex_cinta, NULL);            // Inicializar el mutex para la cinta

    // Crear los hilos para cada tarea
    pthread_create(&hilo_maquina, NULL, maquina_inyeccion, NULL);
    pthread_create(&hilo_robot, NULL, robot_recoge, NULL);
    pthread_create(&hilo_operario, NULL, operario_control_calidad, NULL);

    // Esperar a que los hilos terminen (en este caso, nunca lo harán)
    pthread_join(hilo_maquina, NULL);
    pthread_join(hilo_robot, NULL);
    pthread_join(hilo_operario, NULL);

    // Destruir los semáforos y el mutex (nunca se alcanzará en este ejemplo)
    sem_destroy(&espacio_disponible);
    sem_destroy(&piezas_disponibles);
    pthread_mutex_destroy(&mutex_cinta);

    return 0;
    
}