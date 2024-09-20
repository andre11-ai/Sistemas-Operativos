//Codigo 3. Ejemplo 1

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para usar la función sleep

// Función que simula el escaneo de artículos por cada cajero
void *escaneo_cajero(void *arg) {
    int cajero_id = *((int *)arg);  // Obtener el ID del cajero
    printf("Cajero %d: Escaneando artículos...\n", cajero_id);
    sleep(1);  // Simula el tiempo de escaneo de los artículos
    printf("Cajero %d: Ha terminado de escanear los artículos.\n", cajero_id);
    pthread_exit(NULL);  // Terminar el hilo
}

int main() {
    pthread_t cajeros[4];  // Array para almacenar los identificadores de los hilos (cajeros)
    int ids[] = {1, 2, 3, 4};  // IDs de los cajeros

    // Crear hilos para cada cajero
    for (int i = 0; i < 4; i++) {
        pthread_create(&cajeros[i], NULL, escaneo_cajero, (void *) &ids[i]);  // Crear hilo que representa a cada cajero
    }

    // Esperar a que cada cajero termine de escanear
    for (int i = 0; i < 4; i++) {
        pthread_join(cajeros[i], NULL);  // Esperar a que el cajero termine su tarea
    }

    printf("Programa principal: Todos los cajeros han terminado de escanear.\n");

    return 0;
}
