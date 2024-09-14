// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.2 Corregida por el equipo 
// Dependiendo del proceso (padre o hijo), se ejecutan diferentes bloques de código.
// El proceso padre espera a que el proceso hijo termine utilizando wait(),
// lo que asegura que el proceso hijo finalice antes de que el padre continúe.
// Ambos procesos imprimen mensajes indicando su estado y luego el programa termina.

// Explicación de las correccionesque se realizaron para este codigo:
// Inclusión de librerías : Se añadieron #include<unistd.h> para fork() y 
// #include<sys / wait.h> para wait().
// Gestión de errores : Se usa la función perror() para dar un mensaje de error más detallado.
// Uso de getpid() : En lugar de mostrar pid directamente, se utiliza getpid() para imprimir el PID del
// proceso actual, ya que es más adecuado en este contexto.
// Con estas correciones ya compila adecuadamente el codigo.

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
