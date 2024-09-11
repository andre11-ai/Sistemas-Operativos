#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>   // Para la función fork()
#include <sys/wait.h> // Para la función wait()

int main(){

    int pid, status;
    switch (pid = fork()){
    case -1: // Gestión del error
        perror("Error al crear el proceso");
        exit(1);
        break;
    case 0: // Proceso hijo
        printf("\nProceso hijo. PID = %d\n", getpid());
        break;

    default: // Proceso padre
        printf("\nProceso padre. PID = %d\n", getpid());
        wait(&status); // Espera al final del proceso hijo
        break;
    } // Fin del switch

    printf("\nFin de la ejecución\n");
    return 0;
} // Fin de la función main
