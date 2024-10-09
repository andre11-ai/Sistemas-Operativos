/*
Nombre del equipo: S.O. AGREVAL
Fecha: 08/10/2024
Version: 1.5
Este programa en C simula el ensamblaje de automóviles en una línea de producción utilizando 
recursividad, semáforos, y hilos. Cada automóvil consta de 5 partes: estructura, chasis, 
motor, llantas e interiores, cada una con un ID único. El programa permite ensamblar varios
vehículos simultáneamente (dos a la vez) y genera un archivo de texto (reporte.txt) donde se 
registran los IDs de los automóviles y sus respectivas partes. Además, los pasos del 
ensamblaje son mostrados en pantalla de forma secuencial, indicando el progreso detallado de 
cada parte ensamblada.
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Para usar sleep()
#include <stdlib.h> // Para usar rand()

#define NUM_PARTES 5

typedef struct {
    int id;
    int id_estructura;
    int id_chasis;
    int id_motor;
    int id_llantas;
    int id_interiores;
} Automovil;

sem_t ensamblando_auto; // Semáforo para controlar ensamblaje
FILE* archivo;

// Función recursiva para ensamblar cada parte del auto
void ensamblar_parte(Automovil* auto_ensamblado, int parte) {
    if (parte > NUM_PARTES) {
        return; // Condición de finalización
    }

    if (parte == 1) {
        printf("Vehículo ID %d: Trayendo estructura\n", auto_ensamblado->id);
        sleep(1);
    } else if (parte == 2) {
        printf("Vehículo ID %d: Armando chasis\n", auto_ensamblado->id);
        sleep(1);
    } else if (parte == 3) {
        printf("Vehículo ID %d: Insertando motor\n", auto_ensamblado->id);
        sleep(1);
    } else if (parte == 4) {
        printf("Vehículo ID %d: Poniendo e inflando llantas\n", auto_ensamblado->id);
        sleep(1);
    } else if (parte == 5) {
        printf("Vehículo ID %d: Instalando interiores\n", auto_ensamblado->id);
        sleep(1);
    }

    ensamblar_parte(auto_ensamblado, parte + 1); // Llamada recursiva para la siguiente parte
}

// Función para ensamblar un auto completo (usando recursividad)
void* ensamblar_auto(void* arg) {
    Automovil* auto_ensamblado = (Automovil*)arg;

    sem_wait(&ensamblando_auto); // Esperar hasta que el ensamblaje anterior termine

    // Generar IDs únicos para cada parte del auto
    auto_ensamblado->id_estructura = rand() % 10000;
    auto_ensamblado->id_chasis = rand() % 10000;
    auto_ensamblado->id_motor = rand() % 10000;
    auto_ensamblado->id_llantas = rand() % 10000;
    auto_ensamblado->id_interiores = rand() % 10000;

    // Ensamblar el automóvil paso por paso usando recursividad
    ensamblar_parte(auto_ensamblado, 1);

    // Probar el auto al final
    printf("Vehículo ID %d: Probando auto\n", auto_ensamblado->id);
    sleep(1);

    printf("Vehículo ID %d: Auto listo\n", auto_ensamblado->id);
    sleep(1);

    // Escribir en el archivo TXT el ID del vehículo y de cada parte
    fprintf(archivo, "Vehiculo ID:%d Estructura ID:%d Chasis ID:%d Motor ID:%d Llantas ID:%d Interiores ID:%d\n", 
            auto_ensamblado->id, 
            auto_ensamblado->id_estructura, 
            auto_ensamblado->id_chasis, 
            auto_ensamblado->id_motor, 
            auto_ensamblado->id_llantas, 
            auto_ensamblado->id_interiores);

    // Imprimir la misma información en pantalla
    printf("Vehiculo ID:%d Estructura ID:%d Chasis ID:%d Motor ID:%d Llantas ID:%d Interiores ID:%d\n", 
            auto_ensamblado->id, 
            auto_ensamblado->id_estructura, 
            auto_ensamblado->id_chasis, 
            auto_ensamblado->id_motor, 
            auto_ensamblado->id_llantas, 
            auto_ensamblado->id_interiores);

    sem_post(&ensamblando_auto); // Permitir que el siguiente hilo comience

    return NULL;
}

int main() {
    int num_autos;

    // Solicitar el número de vehículos a ensamblar
    printf("Ingresa el número de vehículos a ensamblar: ");
    scanf("%d", &num_autos);

    // Abrir archivo para escribir el reporte
    archivo = fopen("reporte.txt", "w");
    if (archivo == NULL) {
        printf("Error abriendo archivo\n");
        return 1;
    }

    sem_init(&ensamblando_auto, 0, 2); // Permitir ensamblar 2 autos a la vez

    pthread_t hilos[num_autos];
    Automovil autos[num_autos];

    // Recursión para crear los hilos (sin ciclo)
    void crear_hilo(int i) {
        if (i >= num_autos) {
            return; // Condición de finalización
        }
        autos[i].id = i + 1; // Asignar un ID único al auto
        pthread_create(&hilos[i], NULL, ensamblar_auto, &autos[i]);

        crear_hilo(i + 1); // Llamada recursiva para crear el siguiente hilo
    }

    crear_hilo(0); // Iniciar creación de hilos con recursividad

    // Esperar a que todos los hilos terminen (recursivamente)
    void esperar_hilos(int i) {
        if (i >= num_autos) {
            return; // Condición de finalización
        }
        pthread_join(hilos[i], NULL);
        esperar_hilos(i + 1); // Llamada recursiva para esperar al siguiente hilo
    }

    esperar_hilos(0); // Iniciar espera de hilos con recursividad

    // Limpiar recursos
    fclose(archivo);
    sem_destroy(&ensamblando_auto);

    printf("Proceso de ensamblaje completado. Revisa el archivo 'reporte.txt'.\n");

    return 0;
}
