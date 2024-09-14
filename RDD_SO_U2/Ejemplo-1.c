// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.1 de Ejemplo 1 Dada por el profesor

// Importación de librerías

// Código 1. Hilos ligeros.

#include <stdio.h>   // Librería de entrada y salida estándar
#include <pthread.h> // Librería POSIX estándar en lenguaje C para Linux

// Función que se ejecutará en el primer hilo

void *funcionHilo1(void *arg)
{
    for (int i = 1; i <= 5; ++i)
    {                                      // Ciclo for inicializado en 1 con condición de paro cuando el contador es mayor a 5
        printf("Hilo 1: Mensaje %d\n", i); // Impresión en pantalla de mensajes del primer hilo
    }
    return NULL; // Se retorna NULL para finalizar la ejecución de la función
}

// Función que se ejecutará en el segundo hilo

void *funcionHilo2(void *arg)
{
    for (int i = 1; i <= 5; ++i)
    {                                      // Ciclo for inicializado en 1 con condición de paro cuando el contador es mayor a 5
        printf("Hilo 2: Mensaje %d\n", i); // Impresión en pantalla de mensajes del segundo hilo
    }
    return NULL; // Se retorna NULL para finalizar la ejecución de la función
}

int main()
{
    // Declaración de identificadores de hilos
    pthread_t hilo1, hilo2; // Se declaran 2 estructuras de datos con pthread_t

    // Creación de hilos
    pthread_create(&hilo1, NULL, funcionHilo1, NULL); // Se crea proceso, el cual hilo1 ejecuta con la rutina funcionHilo1
    pthread_create(&hilo2, NULL, funcionHilo2, NULL); // Se crea proceso, el cual hilo2 ejecuta con la rutina funcionHilo2

    // Espera a que los hilos terminen su ejecución
    pthread_join(hilo1, NULL); // Se espera a que hilo1 termine su ejecución
    pthread_join(hilo2, NULL); // Se espera a que hilo2 termine su ejecución

    printf("Programa principal: Hilos finalizados\n"); // Impresión en pantalla de finalización de programa principal

    return 0;
}

