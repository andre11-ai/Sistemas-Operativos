// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.2 Corregida por el equipo
// El programa tiene como objetivo crear un proceso hijo utilizando la función fork()
// Funcionamiento esperado:
// Proceso padre :
// Se ejecutará primero y creará un proceso hijo usando fork().Luego, imprimirá su propio PID
// y el PID del proceso hijo.Después de que el proceso hijo haya terminado de dormir(10 segundos),
// ambos procesos finalizarán, mostrando el mensaje de fin de ejecución con sus respectivos PIDs.
// Proceso hijo : El proceso hijo se ejecutará en paralelo con el proceso padre.Imprimirá su propio
// PID y el PID de su padre.Luego, dormirá por 10 segundos usando sleep(10).Finalmente, imprimirá el
// mensaje de fin de ejecución y terminará.

// Este programa compila y corre correctamente no necesita correciones.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    pid_t rf;
    rf = fork();

    switch (rf){

    case -1:
        printf("\nNo he podido crear el proceso hijo");
        break;

    case 0:
        printf("\nSoy el hijo, mi PID es %d  y mi PPID es %d", getpid(), getppid());
        sleep(10);
        break;
    default:
        printf("\nSoy el padre, mi PID es %d y el PID de mi hijo es %d", getpid(), rf);
    }

    printf("\nFinal de ejecucuión de %d\n", getpid());
    exit(0);

}