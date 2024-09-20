// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.2 Corregida por el equipo
// EL programa tiene como objetivo crear un proceso hijo utilizando la función fork(),
// la cual es parte del sistema operativo Unix/Linux
// Funcionamiento esperado :
// Padre : El proceso principal(padre) creará un proceso hijo.
// Hijo : El proceso hijo imprimirá su PID y el PID del padre, dormirá 20 segundos, y luego terminará
// Padre : El proceso padre imprimirá su PID y el del hijo, dormirá 30 segundos(10 más que el hijo), y
// luego terminará. Ambos procesos, después de dormir, imprimirán el mensaje "Final de ejecución de <PID>".
// El programa simula la ejecución concurrente de procesos, donde el padre se suspende por más tiempo que el hijo.

// Explicación de las correcciones:
// Corrección ortográfica : Corregimos el mensaje de error que se muestra cuando no se puede crear el
// proceso hijo.
// Revisión de las llamadas a sleep() : Aunque no hubo un error específico, es importante mantenerlas
// en mente, ya que su correcto funcionamiento depende del sistema operativo.
// Revisión general del código : Aseguramos que las funciones y estructuras se comportan de acuerdo
// con lo esperado para un programa que crea procesos con fork().

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    pid_t rf;
    rf = fork(); // Crea un proceso hijo

    switch (rf){

    case -1:
        // Error al crear el proceso hijo
        printf("NO he podido crear el proceso hijo \n");
        break;

    case 0:
        // Proceso hijo
        printf("Soy el hijo, mi PID es %d y mi PPID es %d\n", getpid(), getppid());
        sleep(20); // Suspende el proceso 20 segundos
        break;

    default:
        // Proceso padre
        printf("Soy el padre, mi PID es %d y el PID de mi hijo es %d\n", getpid(), rf);
        sleep(30); // Suspende el proceso 30 segundos
    }

    // Ambos procesos ejecutarán esta línea antes de terminar
    printf("Final de ejecución de %d\n", getpid());
    exit(0);
    
}
