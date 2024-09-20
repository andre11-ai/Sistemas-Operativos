// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.2 Corregida por el equipo
// El programa tiene como objetivo utilizar la función execv() para ejecutar otro programa llamado execprog2.
// Funcionamiento esperado:
// El programa se ejecuta e imprime sus argumentos.Espera 10 segundos(sleep(10)).Intenta reemplazarse a
// sí mismo con el programa execprog2 usando execv().Si execprog2 no se puede ejecutar, se imprimirá un
// mensaje de error.Recuerda que para que este programa funcione correctamente, debes tener un programa
// llamado execprog2 en el mismo directorio.

// Explicación de las correcciones:
// Bucle para imprimir argumentos: Ahora solo hay un bucle que imprime correctamente todos los argumentos 
// pasados al programa.
// Uso de execv() : El programa hace una pausa de 10 segundos usando sleep(10) antes de intentar ejecutar 
// execprog2 con los mismos argumentos.Si execv() falla(por ejemplo, si execprog2 no existe), imprime un 
// mensaje de error y termina con un código de error(exit(1)).
// Eliminación de la modificación de argv[0] : Para evitar problemas con la modificación de argv[0], se 
// ha eliminado esa línea.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int i;

    printf("Ejecutando el programa invocador (execprog1). Sus argumentos son:\n");

    // Imprimir los argumentos pasados al programa
    for (i = 0; i < argc; i++){

        
    printf("argv[%d]: %s\n", i, argv[i]);
    
    }

    sleep(10); // Pausa de 10 segundos

    // Llamada a execv para reemplazar este programa por execprog2
    if (execv("./execprog2", argv) < 0){
        // Si execv falla, imprime un mensaje de error
        printf("Error en la invocación a execprog2\n");
        exit(1);

    }

    // Nunca se ejecutará si execv es exitoso
    exit(0);
    
}
