// Nombre del equipo: S.O. AGREVAL
// Fecha: 26/09/2024
// Versión: 1.3.1
// Programa para simular la sincronización de procesos usando memoria compartida y turnos,
// con manejo de señales SIGINT (Ctrl+C) para finalizar de manera segura.
// Este programa utiliza memoria compartida (IPC) para coordinar dos procesos que se alternan
// en una sección crítica. Cada proceso espera su turno antes de entrar en la región crítica
// y, una vez que la ha terminado, cede el turno al otro proceso. Se utiliza una variable
// compartida (`turno`) para controlar qué proceso está en la sección crítica en cada momento.
// Además, se maneja la señal SIGINT (Ctrl+C) para finalizar el programa de manera ordenada,
// liberando la memoria compartida antes de salir.

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> // Incluir para funciones de memoria compartida
#include <signal.h>  // Incluir para manejo de señales
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // Incluir para memset (inicializar estructuras)

// Definición de claves y valores
#define SHMKEY 75 // Clave de la memoria compartida
#define TRUE 1    // Valor lógico TRUE

// Variables globales
int shmid;  // ID del segmento de memoria compartida
int *turno; // Puntero para acceder a la memoria compartida

// Prototipos de funciones
void finalizar(int sig);        // Manejador de señales para SIGINT
int region_critica(int pid);    // Simula región crítica
int region_no_critica(int pid); // Simula región no crítica
int esperando_turno(int pid);   // Muestra mensaje mientras se espera el turno

int main()
{

    int pid;             // Identificador del proceso
    struct sigaction sa; // Estructura para manejar la señal SIGINT

    // Configuración de sigaction para capturar SIGINT
    memset((void *)&sa, 0, sizeof(sa)); // Limpiar la estructura
    sa.sa_handler = finalizar;          // Asignar el manejador de señales
    sigaction(SIGINT, &sa, NULL);       // Establecer el manejador para SIGINT

    // Obtener el ID del proceso actual
    pid = getpid();

    // Crear el segmento de memoria compartida
    shmid = shmget(SHMKEY, sizeof(int), 0777 | IPC_CREAT);
    if (shmid < 0)
    {

        perror("Error al crear la memoria compartida");
        exit(1);
    }

    // Adjuntar el segmento de memoria compartida al espacio de direcciones del proceso
    turno = (int *)shmat(shmid, 0, 0);
    if (turno == (int *)-1)
    {

        perror("Error al adjuntar la memoria compartida");
        exit(1);
    }

    // Inicializar el valor de `turno` para controlar el turno de los procesos
    *turno = 0; // Establecer turno inicial

    // Mostrar mensaje inicial
    printf("\n[I] Variables declaradas y memoria compartida creada.");
    sleep(2);
    printf("\n[I] Inicia proceso de turnos con turno inicial: %d\n", *turno);

    // Bucle principal del proceso
    while (TRUE)
    {

        while (*turno != 0)
        {

            esperando_turno(pid);
        }

        // Entrar en la región crítica
        region_critica(pid);

        // Simular un pequeño retardo antes de ceder el turno
        sleep(1);

        // Cambiar el turno al proceso 1
        *turno = 1;

        // Ejecutar la región no crítica
        region_no_critica(pid);
    }

    return 0;
}

void finalizar(int sig)
{

    printf("\n[S] Señal %d recibida. Finalizando proceso...\n", sig);

    // Desvincular el segmento de memoria compartida
    if (shmdt(turno) == -1)
    {

        perror("Error al desvincular la memoria compartida");
    }
    else
    {

        printf("\n[S] Memoria compartida desvinculada correctamente.\n");
    }

    // Eliminar el segmento de memoria compartida
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {

        perror("Error al eliminar la memoria compartida");
    }
    else
    {

        printf("\n[S] Memoria compartida eliminada correctamente.\n");
    }

    // Salir del programa
    exit(0);
}

int esperando_turno(int pid)
{

    printf("\n[I] Proceso %d está esperando su turno.", pid);
    sleep(2); // Simulación de espera
    return 0;
}

int region_critica(int pid)
{

    printf("\n[O] Proceso %d entrando en la región crítica y realizando trabajo.\n", pid);
    for (int i = 0; i < 5; i++)
    {

        printf("[O] Proceso %d - Iteración %d en la región crítica\n", pid, i + 1);
        sleep(1); // Simulación de trabajo dentro de la región crítica
    }

    return 0;
}

int region_no_critica(int pid)
{

    printf("\n[I] Proceso %d está en la región no crítica.\n", pid);
    sleep(2); // Simulación de trabajo en la región no crítica
    return 0;
}