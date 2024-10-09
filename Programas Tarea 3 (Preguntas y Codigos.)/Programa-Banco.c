#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Variable global que representa el saldo
int saldo;
pthread_mutex_t candado; // Mutex para proteger la variable saldo

// Función para hacer retiros
void *retirar(void *arg){
    int cantidad = *(int *)arg;
    pthread_mutex_lock(&candado); // Bloquear el mutex
    if (saldo >= cantidad){
        saldo -= cantidad;
        printf("Retiro de %d realizado. Saldo restante: %d\n", cantidad, saldo);
    }
    else{
        printf("No hay suficiente saldo para retirar %d. Saldo actual: %d\n", cantidad, saldo);
    }
    pthread_mutex_unlock(&candado); // Desbloquear el mutex
    return NULL;
}

// Función para hacer depósitos
void *depositar(void *arg){
    int cantidad = *(int *)arg;
    pthread_mutex_lock(&candado); // Bloquear el mutex
    saldo += cantidad;
    printf("Depósito de %d realizado. Saldo actual: %d\n", cantidad, saldo);
    pthread_mutex_unlock(&candado); // Desbloquear el mutex
    return NULL;
}

// Función para mostrar el menú y realizar la operación elegida
void mostrar_menu(){
    int opcion;
    pthread_t hilos[10]; // Array para almacenar los identificadores de los hilos
    int cantidades[10]; // Array para almacenar las cantidades
    int num_hilos = 0; // Contador de hilos creados

    do{
        // Mostrar menú
        printf("\n--- Menú de operaciones bancarias ---\n");
        printf("1. Depositar dinero\n");
        printf("2. Retirar dinero\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion){
        case 1:
            // Depositar
            printf("Ingrese la cantidad a depositar: ");
            scanf("%d", &cantidades[num_hilos]);
            pthread_create(&hilos[num_hilos], NULL, depositar, &cantidades[num_hilos]);
            num_hilos++;
            break;
        
        case 2:
            // Retirar
            printf("Ingrese la cantidad a retirar: ");
            scanf("%d", &cantidades[num_hilos]);
            pthread_create(&hilos[num_hilos], NULL, retirar, &cantidades[num_hilos]);
            num_hilos++;
            break;
        
        case 3:
            printf("Saliendo del programa...\n");
            break;
        
        default:
            printf("Opción no válida, intente de nuevo.\n");
            break;
        }
    } while (opcion != 3);

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }
}

int main(){
    // Solicitar el saldo inicial
    printf("Ingrese el saldo inicial: ");
    scanf("%d", &saldo);

    // Inicializar el mutex
    pthread_mutex_init(&candado, NULL);

    // Mostrar el saldo inicial
    printf("\nSaldo inicial: %d\n", saldo);

    // Mostrar el menú para realizar operaciones
    mostrar_menu();

    // Destruir el mutex
    pthread_mutex_destroy(&candado);

    // Mostrar el saldo final
    printf("Saldo final: %d\n", saldo);

    return 0;
}
