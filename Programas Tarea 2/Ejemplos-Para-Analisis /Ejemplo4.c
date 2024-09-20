// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.1 de Ejemplo 1 Dada por el profesor
// El programa tiene la intención de implementar un mecanismo de comunicación entre un proceso padre
// y su proceso hijo utilizando un pipe. El padre envía datos a través del pipe, y el hijo los lee e
// imprime el contenido en la salida estándar (STDOUT).
// Funcionamiento esperado:
// El proceso padre solicitará al usuario una cadena de hasta 10 caracteres.
// El proceso padre enviará esa cadena al proceso hijo a través del pipe.
// El proceso hijo leerá la cadena, la imprimirá en la salida estándar, y luego ambos procesos terminarán.

// Pero el codigo tiene pequeños errores como:
// Error en el manejo de errno :
// La variable interrnum y errum están mal definidas.En lugar de interrnum, debe ser simplemente errno,
// y errum no está declarada. Además, la variable errno no necesita ser preservada de esa manera, ya que
// el sistema la maneja automáticamente.
// Error en la escritura de la función imprimeDePipe :
// La llamada a write() dentro del bucle es incorrecta :código write(read(STDOUT_FILENO, &buf, 1));
// Esto no tiene sentido, ya que read() devuelve el número de bytes leídos, y el resultado está siendo
// pasado incorrectamente a write().En lugar de eso, deberías usar write(STDOUT_FILENO, &buf, 1).
// La función enviaAPipe() está incompleta :
// No hay implementación en la función enviaAPipe(). Debería pedir una cadena al usuario,escribirla en
// el pipe y luego cerrarlo.
// SI desea ver mas informacion acerca del funcionamiento en el txt de la carpeta "Ejemplos-Corregidos ->
// Ejemplo-4-Correcion", encontrara mas informacion de este codigo.

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void imprimeDePipe(int leePipe);   // Funcionalidad para el hijo                                                                                                                                                                                 imprimeDePipe(int leePipe); // Funcionalidad para el hijo
void enviarAPipe(int escribePipe); // Funcionalidad para el padre

int main(){

    pid_t procHijo;
    int pipeFileDescriptors[2]; // Descriptores de ambos extremos
    if (pipe(pipeFileDescriptors) == -1){ // Genera pipe

        printf("Error al crear pipe\n");
        exit(1);

    }

    procHijo = fork(); // Genera proceso hijo

    if (procHijo < 0){

        interrnum = errno; // Preservamos código de error
        printf("Error %d al generar proceso hijo con fork\n", errum);
        exit(1);

    }

    if (procHijo == 0){

        // Es el hijo, cierra pipe de envio y procede
        close(pipeFileDescriptors[1]);
        imprimeDePipe(pipeFileDescriptors[0]);

    }

    if (procHijo > 0){

        // Es el padre, cierra pide de recepción y procede
        close(pipeFileDescriptors[0]);
        enviarAPipe(pipeFileDescriptors[1]);

    }

    return 0;

}

/**
 *  Funcionalidad para el hijo, lee del pipe la cadena enviada, imprime
 * el contenido de esta a STDOUT, cierra su extremo del pipe (lectura)
 * y termina su proceso.
 * */

void imprimeDePipe(int leePipe){

    char buf; // Caracter de buffer
    printf("Proceso hijo, esperando cadena...\n");
    while (read(leePipe, &buf, 1) > 0)
        write(read(STDOUT_FILENO, &buf, 1));
    write(STDOUT_FILENO, "\n", 1); // Fin de linea
    close(leePipe);
    printf("Proceso hijo, finalizando\n");
    exit(0);

}

/**
 * Funcionalidad para el padre, lee una cadena de hasta 10 caracteres,
 * la escribe a su extremo del pipe, cierra su extremo y espera a que
 * un proceso hijo termina antes de terminar su propio proceso.
 **/

void enviaAPipe(int escibePipe){

    char buf[10];

}