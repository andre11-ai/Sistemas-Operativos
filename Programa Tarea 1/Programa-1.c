// S.O.AGREVAl
// Fecha : 13 / 09 / 2024
// Version : 1.1 Dada por el profesor
// Dependiendo del proceso (padre o hijo), se ejecutan diferentes bloques de código.
// El proceso padre espera a que el proceso hijo termine utilizando wait(),
// lo que asegura que el proceso hijo finalice antes de que el padre continúe.
// Ambos procesos imprimen mensajes indicando su estado y luego el programa termina.

// Pero el codigo tiene pequeños errores de formateo, como la falta de indentación en 
// algunas líneas y a falta de un tipo de retorno en la función main().
// En C, la función main() debe retornar un valor entero(int).Declaración de variables.
// Las variables pid y status están correctamente declaradas como enteros,
// pero es importante verificar que el valor de fork() esté siendo almacenado correctamente.

// SI desea ver mas informacion acerca del funcionamiento en el txt "Programa-1-Correcion.txt",
// encontrara mas informacion de este codigo. 

#include<fcntl.h>
#include<stdio.h>

    main(){

    int pid, status;
    switch (pid=fork()){
    case -1: /*Gestion del error*/
        exit(1);
        break;
    case 0: /*Proceso hijo*/
        printf("\n Proceso hijo. PID=%d\n" ,pid);
        break;
    
    default: /*Proceso Padre*/
        printf("\n Proceso Padre. PID =%d\n" ,pid);
        wait(&status); /*Espera el final del proceso hijo*/
        break;
    }/*fin del switch*/

    printf("\n Fin de la ejecucion\n");
    return 0;

}/*Fin de la funcion main*/