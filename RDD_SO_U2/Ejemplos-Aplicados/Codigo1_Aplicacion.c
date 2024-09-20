// Código 1. Importacion de Librerias


#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para la función sleep

// Función que simula la impresión de facturas en la primera impresora
void *impresora1(void *arg)
{
    for (int i = 1; i <= 5; ++i)
    {
        printf("Impresora 1: Imprimiendo factura %d\n", i); // Simulación de la impresión de facturas
        sleep(1); // Simula el tiempo de impresión (1 segundo por factura)
    }
    return NULL;
}

// Función que simula la impresión de facturas en la segunda impresora
void *impresora2(void *arg)
{
    for (int i = 1; i <= 5; ++i)
    {
        printf("Impresora 2: Imprimiendo factura %d\n", i); // Simulación de la impresión de facturas
        sleep(1); // Simula el tiempo de impresión (1 segundo por factura)
    }
    return NULL;
}

int main()
{
    // Declaración de identificadores de hilos
    pthread_t hilo1, hilo2;

    // Creación de hilos para las impresoras
    pthread_create(&hilo1, NULL, impresora1, NULL); // El hilo 1 ejecuta la función impresora1
    pthread_create(&hilo2, NULL, impresora2, NULL); // El hilo 2 ejecuta la función impresora2

    // Espera a que los hilos terminen su ejecución
    pthread_join(hilo1, NULL); // Espera a que el hilo de la impresora1 termine
    pthread_join(hilo2, NULL); // Espera a que el hilo de la impresora2 termine

    printf("Programa principal: Todas las facturas han sido impresas\n");

    return 0;
}
