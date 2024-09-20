// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.2 Corregida por el equipo
// El programa tiene la intención de implementar un mecanismo de comunicación entre un proceso padre
// y su proceso hijo utilizando un pipe. El padre envía datos a través del pipe, y el hijo los lee e
// imprime el contenido en la salida estándar (STDOUT).
// Funcionamiento esperado:
// El proceso padre solicitará al usuario una cadena de hasta 10 caracteres.
// El proceso padre enviará esa cadena al proceso hijo a través del pipe.
// El proceso hijo leerá la cadena, la imprimirá en la salida estándar, y luego ambos procesos terminarán.

// Explicación de las correcciones:
// Manejo de errno corregido :
// Se ha corregido el error con errno, y ahora el mensaje de error en caso de falla de fork() funciona
// correctamente.
// Corrección en imprimeDePipe :
// Ahora el proceso hijo lee correctamente el contenido del pipe carácter por carácter y lo imprime en
// la salida estándar utilizando : write(STDOUT_FILENO, &buf, 1);
// Implementación de enviaAPipe :
// El proceso padre pide al usuario que ingrese una cadena de hasta 10 caracteres, la escribe en el pipe y 
// luego cierra el descriptor de escritura.La función fgets() asegura que no se ingresen más de 10 caracteres.
// Sincronización del padre con el hijo :
// El padre espera a que el proceso hijo termine utilizando wait(NULL) antes de finalizar su propio proceso.

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void imprimeDePipe(int leePipe);   // Funcionalidad para el hijo
void enviarAPipe(int escribePipe); // Funcionalidad para el padre

int main(){
    pid_t procHijo;
    int pipeFileDescriptors[2]; // Descriptores de ambos extremos

    // Crear el pipe
    if (pipe(pipeFileDescriptors) == -1){
        printf("Error al crear pipe\n");
        exit(1);
    }

    procHijo = fork(); // Generar proceso hijo

    if (procHijo < 0){
        // Si hay error en fork
        int errnum = errno; // Preservamos código de error
        printf("Error %d al generar proceso hijo con fork\n", errnum);
        exit(1);
    }

    if (procHijo == 0){
        // Es el hijo, cierra pipe de envío y procede
        close(pipeFileDescriptors[1]);
        imprimeDePipe(pipeFileDescriptors[0]);
    }
    else{
        // Es el padre, cierra pipe de recepción y procede
        close(pipeFileDescriptors[0]);
        enviarAPipe(pipeFileDescriptors[1]);

        // Espera a que el proceso hijo termine
        wait(NULL);
        printf("Proceso padre, finalizando\n");
    }

    return 0;
}

/**
 * Funcionalidad para el hijo. Lee del pipe la cadena enviada,
 * imprime el contenido a STDOUT, cierra su extremo del pipe
 * (lectura) y termina su proceso.
 */
void imprimeDePipe(int leePipe){
    char buf; // Caracter de buffer
    printf("Proceso hijo, esperando cadena...\n");
    while (read(leePipe, &buf, 1) > 0){

        write(STDOUT_FILENO, &buf, 1);
        
    }
    write(STDOUT_FILENO, "\n", 1); // Fin de línea
    close(leePipe);
    printf("Proceso hijo, finalizando\n");
    exit(0);
}

/**
 * Funcionalidad para el padre. Lee una cadena de hasta 10 caracteres,
 * la escribe a su extremo del pipe, cierra su extremo y espera a que
 * el proceso hijo termine antes de terminar su propio proceso.
 */
void enviarAPipe(int escribePipe){
    char buf[10];
    printf("Proceso padre, introduzca una cadena (máx 10 caracteres): ");
    fgets(buf, 10, stdin);                // Leer hasta 10 caracteres desde el teclado
    write(escribePipe, buf, strlen(buf)); // Escribir la cadena en el pipe
    close(escribePipe);
    printf("Proceso padre, cadena enviada\n");
}
