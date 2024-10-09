// S.O. AGREVAL
// Fecha: 09/10/2024
// Version: 1.2.2
// Este codigo utiliza procesos y tuberías para leer un archivo de entrada, procesar sus líneas y
// aplicar filtros y ordenamientos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Función para leer líneas alternas y escribir en dos tuberías
void alternar_lineas(FILE *file, int fd1[2], int fd2[2])
{
    char buffer[BUFFER_SIZE];
    int linea = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        if (linea % 2 == 0)
        { // Línea par
            write(fd1[1], buffer, strlen(buffer) + 1);
        }
        else
        { // Línea impar
            write(fd2[1], buffer, strlen(buffer) + 1);
        }
        linea++;
    }

    close(fd1[1]); // Cerramos escritura en ambas tuberías
    close(fd2[1]);
}

// Función para aplicar grep y escribir el resultado en una tercera tubería
void aplicar_grep(int fd_in[2], int fd_out[2], char *palabra)
{
    char buffer[BUFFER_SIZE];
    close(fd_in[1]);  // Cerramos el extremo de escritura de la tubería de entrada
    close(fd_out[0]); // Cerramos el extremo de lectura de la tubería de salida

    while (read(fd_in[0], buffer, BUFFER_SIZE) > 0)
    {
        if (strstr(buffer, palabra) != NULL)
        { // Si la palabra está en la línea
            write(fd_out[1], buffer, strlen(buffer) + 1);
        }
    }

    close(fd_in[0]);  // Cerramos lectura de la tubería de entrada
    close(fd_out[1]); // Cerramos escritura de la tubería de salida
}

// Función para ordenar las líneas usando sort
void ordenar_tuberia(int fd_in[2])
{
    char buffer[BUFFER_SIZE];
    FILE *temp_file = tmpfile();

    close(fd_in[1]); // Cerramos el extremo de escritura de la tubería

    // Leer todas las líneas de la tubería y escribirlas en un archivo temporal
    while (read(fd_in[0], buffer, BUFFER_SIZE) > 0)
    {
        fprintf(temp_file, "%s", buffer);
    }

    // Reposicionar el puntero del archivo temporal al inicio
    rewind(temp_file);

    // Usar el comando sort en el archivo temporal
    int temp_fd = fileno(temp_file);
    dup2(temp_fd, STDIN_FILENO);
    execlp("sort", "sort", NULL);

    fclose(temp_file);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Uso: %s <archivo_entrada> <palabra1> <palabra2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Crear tuberías
    int fd1[2], fd2[2], fd3[2];
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);

    // Abrir archivo de entrada
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Crear el primer proceso para alternar las líneas
    if (fork() == 0)
    {
        close(fd1[0]); // Cerramos lectura de las tuberías
        close(fd2[0]);
        alternar_lineas(file, fd1, fd2);
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    // Crear el segundo proceso para aplicar grep en líneas pares
    if (fork() == 0)
    {
        close(fd1[1]); // Cerramos escritura de la tubería
        aplicar_grep(fd1, fd3, argv[2]);
        exit(EXIT_SUCCESS);
    }

    // Crear el tercer proceso para aplicar grep en líneas impares
    if (fork() == 0)
    {
        close(fd2[1]); // Cerramos escritura de la tubería
        aplicar_grep(fd2, fd3, argv[3]);
        exit(EXIT_SUCCESS);
    }

    // Crear el cuarto proceso para ordenar las líneas
    if (fork() == 0)
    {
        close(fd3[1]); // Cerramos escritura de la tubería
        ordenar_tuberia(fd3);
        exit(EXIT_SUCCESS);
    }

    // Cerrar extremos no usados en el proceso principal
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    close(fd3[0]);
    close(fd3[1]);

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }

    return 0;
}
