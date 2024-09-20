//Codigo 5. Ejemplo 3

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para usar la función sleep

// Función que simula el procesamiento de grandes cantidades de datos por un servidor
void *procesar_datos(void *arg) {
    int servidor_id = *((int *)arg);  // Obtener el ID del servidor
    printf("Servidor %d: Iniciando procesamiento de datos...\n", servidor_id);
    sleep(3);  // Simula un procesamiento pesado (3 segundos)
    printf("Servidor %d: Procesamiento de datos completado.\n", servidor_id);
    pthread_exit(NULL);  // Terminar el hilo
}

int main() {
    pthread_t servidores[3];  // Array para almacenar los identificadores de los hilos pesados (servidores)
    int ids[] = {1, 2, 3};  // IDs de los servidores

    // Crear hilos pesados para cada servidor
    for (int i = 0; i < 3; i++) {
        pthread_create(&servidores[i], NULL, procesar_datos, (void *) &ids[i]);  // Crear un nuevo hilo que simula a cada servidor
    }

    // Esperar a que todos los servidores terminen de procesar los datos
    for (int i = 0; i < 3; i++) {
        pthread_join(servidores[i], NULL);  // Esperar a que el servidor con el ID correspondiente termine
    }

    printf("Programa principal: Todos los servidores han terminado de procesar los datos.\n");

    return 0;
}
