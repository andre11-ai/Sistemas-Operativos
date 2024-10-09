// Nombre del equipo: S.O. AGREVAL
// Fecha: 25/09/2024
// Versión: 1.1.0
// Programa para simular operaciones bancarias concurrentes utilizando hilos y mutex.
// Este programa simula dos operaciones bancarias concurrentes: un retiro y un depósito.
// Utiliza hilos para realizar cada operación de manera simultánea, y un mutex para
// proteger el acceso a la variable compartida `saldo`, que representa el saldo de una cuenta
// bancaria. El mutex asegura que las operaciones de retiro y depósito no se realicen
// al mismo tiempo, evitando posibles condiciones de carrera (race conditions).


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Declaración del mutex
pthread_mutex_t mutex;

// Variable compartida que representa el saldo de la cuenta bancaria
int saldo = 0;

void *realizarRetiro(void *arg){

    int monto = *(int *)arg;    // Obtener el monto a retirar
    pthread_mutex_lock(&mutex); // Bloquear el acceso a la variable saldo
    printf("Realizando retiro de %d\n", monto);
    saldo -= monto; // Actualizar el saldo
    printf("Saldo restante: %d\n", saldo);
    pthread_mutex_unlock(&mutex); // Liberar el mutex
    pthread_exit(NULL);

}

void *realizarDeposito(void *arg){

    int monto = *(int *)arg;    // Obtener el monto a depositar
    pthread_mutex_lock(&mutex); // Bloquear el acceso a la variable saldo
    printf("Realizando depósito de %d\n", monto);
    saldo += monto; // Actualizar el saldo
    printf("Saldo actual: %d\n", saldo);
    pthread_mutex_unlock(&mutex); // Liberar el mutex
    pthread_exit(NULL);

}

int main(){

    pthread_t hiloRetiro, hiloDeposito;
    int montoRetiro = 100;   // Monto del retiro
    int montoDeposito = 200; // Monto del depósito

    // Inicialización del mutex
    pthread_mutex_init(&mutex, NULL);

    // Crear los hilos para realizar el retiro y el depósito
    pthread_create(&hiloRetiro, NULL, realizarRetiro, &montoRetiro);
    pthread_create(&hiloDeposito, NULL, realizarDeposito, &montoDeposito);

    // Esperar a que ambos hilos terminen su ejecución
    pthread_join(hiloRetiro, NULL);
    pthread_join(hiloDeposito, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;

}
