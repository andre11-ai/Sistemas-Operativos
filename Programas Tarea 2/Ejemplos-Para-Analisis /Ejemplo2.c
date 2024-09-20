// S.O.AGREVAl
// Fecha : 20 / 09 / 2024
// Version : 1.1 de Ejemplo 1 Dada por el profesor
// El programa tiene como objetivo utilizar la función execv() para ejecutar otro programa llamado execprog2.
// Funcionamiento esperado:
// El programa se ejecuta e imprime sus argumentos.Espera 10 segundos(sleep(10)).Intenta reemplazarse a 
// sí mismo con el programa execprog2 usando execv().Si execprog2 no se puede ejecutar, se imprimirá un 
// mensaje de error.

// Pero el codigo tiene pequeños errores como:
// Doble bucle for: El código contiene dos bucles for anidados innecesariamente
// for (i = 0; i < argc; i++)
//   for (i = 0; i < argc; i++)
// Esto es incorrecto, ya que el segundo for está reescribiendo el valor de i. Esto causaría que el
// código no funcione correctamente.
// Modificación de argv[0] con strcpy(): Aunque se intenta cambiar argv[0], esto puede causar un
// comportamiento inesperado, ya que modificar argv[0] directamente puede no estar permitido en
// algunos sistemas si los argumentos fueron almacenados en memoria de solo lectura.
// SI desea ver mas informacion acerca del funcionamiento en el txt de la carpeta "Ejemplos-Corregidos ->
// Ejemplo-2-Correcion", encontrara mas informacion de este codigo.

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
