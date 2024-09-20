//Codigo 4. Ejemplo 2

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para la función sleep

// Función que simula el proceso de carga de un vehículo eléctrico
void *cargar_vehiculo(void *arg) {
    int vehiculo_id = *((int *) arg);  // Obtener el ID del vehículo
    printf("Vehículo %d: Iniciando carga...\n", vehiculo_id);
    sleep(2);  // Simula el tiempo de carga (2 segundos)
    printf("Vehículo %d: Carga completada.\n", vehiculo_id);
    pthread_exit(NULL);  // Terminar el hilo
}

int main() {
    pthread_t hilos[2];  // Array para almacenar los identificadores de los hilos ligeros (vehículos)
    int ids[] = {1, 2};  // IDs de los vehículos

    // Crear hilos ligeros para cada vehículo
    for (int i = 0; i < 2; i++) {
        pthread_create(&hilos[i], NULL, cargar_vehiculo, (void *) &ids[i]);  // Crear un nuevo hilo para cada vehículo
    }

    // Esperar a que ambos vehículos terminen de cargar
    for (int i = 0; i < 2; i++) {
        pthread_join(hilos[i], NULL);  // Esperar a que el vehículo con el ID correspondiente termine su carga
    }

    printf("Programa principal: Todos los vehículos han terminado de cargar.\n");

    return 0;
}
