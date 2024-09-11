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