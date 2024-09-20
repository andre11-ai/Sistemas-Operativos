// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.1 de Ejemplo 1 Dada por el profesor
// EL programa tiene como objetivo crear un proceso hijo utilizando la función fork(),
// la cual es parte del sistema operativo Unix/Linux
// Funcionamiento esperado :
// Padre : El proceso principal(padre) creará un proceso hijo.
// Hijo : El proceso hijo imprimirá su PID y el PID del padre, dormirá 20 segundos, y luego terminará
// Padre : El proceso padre imprimirá su PID y el del hijo, dormirá 30 segundos(10 más que el hijo), y
// luego terminará. Ambos procesos, después de dormir, imprimirán el mensaje "Final de ejecución de <PID>".
// El programa simula la ejecución concurrente de procesos, donde el padre se suspende por más tiempo que el hijo.

// Pero el codigo tiene pequeños errores como:
// Error ortográfico: En el mensaje printf("NO he podido crear eñ proceso hijo \n");,
// hay un error tipográfico con la letra "ñ", que debería ser una "l". Debería decir "el proceso hijo".
// SI desea ver mas informacion acerca del funcionamiento en el txt de la carpeta "Ejemplos-Corregidos ->
// Ejemplo-1-Correcion", encontrara mas informacion de este codigo.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    pid_t rf;
    rf = fork();

    switch (rf){

    case -1:
        printf("NO he podido crear eñ proceso hijo \n");
        break;

    case 0:
        printf("Soy el hijo, mi PID es %d y mi PPID es %d\n", getpid(), getppid());
        sleep(20); // suspende el proceso 20 segundos
        break;
    default:
        printf("Soy el padre, mi PID es %d y el PID de mi hijo es %d\n", getpid(), rf);
        sleep(30); // suspende el proceso 3o segundos. Acaba antes el hijo.
    }

    printf("Final de ejecucuión de %d\n", getpid());
    exit(0);
    
}
