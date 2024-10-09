// S.O. AGREVAL
// Fecha: 09/10/2024
// Version: 1.2.2
// Este codigo simula el cruce de vehículos en un puente utilizando hilos y semáforos para controlar el
// acceso y la sincronización. El programa define un total de 100 vehículos, divididos equitativamente en
// dos sentidos (50 en cada sentido).

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define TOTAL_VEHICULOS 100
#define VEHICULOS_SENTIDO_1 50
#define VEHICULOS_SENTIDO_2 50

sem_t puente;                         // Semáforo para controlar el acceso al puente
sem_t mutex;                          // Semáforo para controlar la sección crítica
int en_puente = 0;                    // Número de vehículos en el puente
int esperando_1 = 0, esperando_2 = 0; // Vehículos esperando en cada sentido

void *vehiculo(void *arg)
{
    int *datos = (int *)arg;
    int sentido = datos[0];
    int numero = datos[1];
    int espera_random = rand() % 20; // Tiempo aleatorio de espera antes de intentar acceder al puente

    sleep(espera_random); // Simula el tiempo que tarda en llegar al puente

    if (sentido == 1)
    {
        sem_wait(&mutex); // Sección crítica
        esperando_1++;
        printf("Vehículo %d en sentido 1 esperando.\n", numero);
        sem_post(&mutex);
    }
    else
    {
        sem_wait(&mutex); // Sección crítica
        esperando_2++;
        printf("Vehículo %d en sentido 2 esperando.\n", numero);
        sem_post(&mutex);
    }

    sem_wait(&puente); // Espera para acceder al puente

    sem_wait(&mutex); // Sección crítica
    en_puente++;
    if (sentido == 1)
    {
        esperando_1--;
        printf("Vehículo %d en sentido 1 cruzando el puente.\n", numero);
    }
    else
    {
        esperando_2--;
        printf("Vehículo %d en sentido 2 cruzando el puente.\n", numero);
    }
    sem_post(&mutex);

    sleep(1); // Simula el tiempo que tarda en cruzar el puente

    sem_wait(&mutex); // Sección crítica
    en_puente--;
    if (en_puente == 0)
    {
        sem_post(&puente); // Libera el puente si no hay más vehículos
    }
    sem_post(&mutex);

    free(datos); // Liberar la memoria asignada para los datos del vehículo

    return NULL;
}

int main()
{
    pthread_t vehiculos[TOTAL_VEHICULOS];

    sem_init(&puente, 0, 1); // Inicializa el semáforo del puente
    sem_init(&mutex, 0, 1);  // Inicializa el semáforo del mutex

    for (int i = 0; i < VEHICULOS_SENTIDO_1; i++)
    {
        int *datos = malloc(2 * sizeof(int));
        datos[0] = 1;
        datos[1] = i + 1;
        pthread_create(&vehiculos[i], NULL, vehiculo, datos);
    }

    for (int i = VEHICULOS_SENTIDO_1; i < TOTAL_VEHICULOS; i++)
    {
        int *datos = malloc(2 * sizeof(int));
        datos[0] = 2;
        datos[1] = i - VEHICULOS_SENTIDO_1 + 1;
        pthread_create(&vehiculos[i], NULL, vehiculo, datos);
    }

    for (int i = 0; i < TOTAL_VEHICULOS; i++)
    {
        pthread_join(vehiculos[i], NULL);
    }

    sem_destroy(&puente);
    sem_destroy(&mutex);

    return 0;
}