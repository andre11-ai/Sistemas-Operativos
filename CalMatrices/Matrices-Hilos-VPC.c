// S.O. AGREVAL
// Fecha: 17/09/2024
// Version: 1.2 -> Esta version corre en las computadoras preferentemente
// Este programa esta basado en nuestra implementacion en batch, pero utilizando el lenguaje C y
// la posibilidad de utilizar la libreria <pthread.h>  para el manejo de hilos. En este caso particular
// se usara la logica de Multiples procesos por un hilo por proceso, con el fin de resolver un problema
// de la vida real, con la logica de los Hilos y procesos.

// ESTA VERSION EN ALGUNOS CASOS PUEDE SOBREPASAR EL MAXIMO DE MATRICES 

#include <stdio.h>
#include <pthread.h> // Para usar hilos
#include <stdlib.h>  // Para malloc, free y system

#define N 4 // Máximo tamaño de las matrices

// Estructura para pasar múltiples parámetros a los hilos
typedef struct
{
    int mat1[N][N];
    int mat2[N][N];
    int mat3[N][N];
} MATRIX;

// Estructura para pasar los parámetros a los hilos
typedef struct
{
    int pin, num;
    MATRIX *m;
} thread_args;

// Prototipos de funciones
int menu(void);
void selection(int, MATRIX *);
void writeMatrix(MATRIX *, int, int);
void printMatrix(MATRIX *, int, int);
void *thread_product(void *args);
void *thread_add(void *args);
void *thread_scalar(void *args);
void *thread_det(void *args);
void *thread_tras(void *args);
int det(int pin, MATRIX *m);
void tras(int pin, MATRIX *m);
void clear_screen(void);

// Punto de entrada que se llama a si mismo para inicializar las Matrices en 0's
int main()
{
    int opc = 0;
    MATRIX m = {
        .mat1 = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        .mat2 = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        .mat3 = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

    while (1)
    {
        clear_screen(); // Limpiar antes de mostrar el menú
        opc = menu();
        if (opc == 6)
        {
            printf("Saliendo...\n");
            break;
        }
        selection(opc, &m);
    }
    return 0;
}

// Menu el cual nos va a dirigir a las operaciones necesarias
int menu(void)
{
    int s;
    printf("*****************************************\n");
    printf("* SELECCIONA UNA OPCION                 *\n");
    printf("*****************************************\n");
    printf("** Suma de Matrices.................(1)**\n");
    printf("** Multiplicación de Matrices.......(2)**\n");
    printf("** Multiplicación por un escalar....(3)**\n");
    printf("** Determinante de una Matriz.......(4)**\n");
    printf("** Traspuesta de una Matriz.........(5)**\n");
    printf("** Salir del Programa...............(6)**\n");
    printf("*****************************************\n");
    printf("\nOpcion: ");
    scanf("%d", &s);
    return s;
}

// Se selecciona la modalidad y creacion de los hilos.
void selection(int opc, MATRIX *m)
{
    int tam, num;
    pthread_t thread;
    thread_args *args = malloc(sizeof(thread_args));

    clear_screen();

    printf("Selecciona el tamaño de la matriz:\n");
    printf("** 2 x 2.....................(1)**\n");
    printf("** 3 x 3.....................(2)**\n");
    printf("** 4 x 4.....................(3)**\n");
    printf("Opcion: ");
    scanf("%d", &tam);

    args->pin = tam + 1;
    args->m = m;

    clear_screen();

    if (opc == 1)
    {
        // Suma de matrices
        writeMatrix(m, args->pin, 1);
        writeMatrix(m, args->pin, 2);
        pthread_create(&thread, NULL, thread_add, (void *)args);
        pthread_join(thread, NULL);
        printMatrix(m, args->pin, 3);
    }
    else if (opc == 2)
    {
        // Multiplicación de matrices
        writeMatrix(m, args->pin, 1);
        writeMatrix(m, args->pin, 2);
        pthread_create(&thread, NULL, thread_product, (void *)args);
        pthread_join(thread, NULL);
        printMatrix(m, args->pin, 3);
    }
    else if (opc == 3)
    {
        // Multiplicación por un escalar
        printf("Escribe el número escalar: ");
        scanf("%d", &num);
        args->num = num;
        writeMatrix(m, args->pin, 1);
        pthread_create(&thread, NULL, thread_scalar, (void *)args);
        pthread_join(thread, NULL);
        printMatrix(m, args->pin, 1);
    }
    else if (opc == 4)
    {
        // Determinante de la matriz
        writeMatrix(m, args->pin, 1);
        pthread_create(&thread, NULL, thread_det, (void *)args);
        pthread_join(thread, NULL);
    }
    else if (opc == 5)
    {
        // Traspuesta de la matriz
        writeMatrix(m, args->pin, 1);
        pthread_create(&thread, NULL, thread_tras, (void *)args);
        pthread_join(thread, NULL);
        printMatrix(m, args->pin, 3);
    }

    free(args);

    printf("\nPresiona Enter para continuar...");
    getchar(); // Esperar que el usuario presione Enter antes de limpiar la pantalla
    getchar();
}

// Función para escribir las matrices
void writeMatrix(MATRIX *m, int pin, int mat)
{
    int i, j;
    printf("Ingresa los valores de la matriz %d (%dx%d):\n", mat, pin, pin);
    for (i = 0; i < pin; i++)
    {
        for (j = 0; j < pin; j++)
        {
            printf("Valor en [%d][%d]: ", i, j);
            if (mat == 1)
                scanf("%d", &m->mat1[i][j]);
            else
                scanf("%d", &m->mat2[i][j]);
        }
    }
}

// Función para imprimir matrices
void printMatrix(MATRIX *m, int pin, int mat)
{
    int i, j;
    printf("Matriz %d:\n", mat);
    for (i = 0; i < pin; i++)
    {
        for (j = 0; j < pin; j++)
        {
            if (mat == 1)
                printf("[%d] ", m->mat1[i][j]);
            else if (mat == 2)
                printf("[%d] ", m->mat2[i][j]);
            else
                printf("[%d] ", m->mat3[i][j]);
        }
        printf("\n");
    }
}

// Operación de suma ejecutada en un hilo
void *thread_add(void *args)
{
    thread_args *arg = (thread_args *)args;
    MATRIX *m = arg->m;
    int i, j;

    for (i = 0; i < arg->pin; i++)
    {
        for (j = 0; j < arg->pin; j++)
        {
            m->mat3[i][j] = m->mat1[i][j] + m->mat2[i][j];
        }
    }

    return NULL;
}

// Operación de multiplicación ejecutada en un hilo
void *thread_product(void *args)
{
    thread_args *arg = (thread_args *)args;
    MATRIX *m = arg->m;
    int i, j, k;

    for (i = 0; i < arg->pin; i++)
    {
        for (j = 0; j < arg->pin; j++)
        {
            m->mat3[i][j] = 0;
            for (k = 0; k < arg->pin; k++)
            {
                m->mat3[i][j] += m->mat1[i][k] * m->mat2[k][j];
            }
        }
    }

    return NULL;
}

// Operación de multiplicación por escalar ejecutada en un hilo
void *thread_scalar(void *args)
{
    thread_args *arg = (thread_args *)args;
    MATRIX *m = arg->m;
    int i, j;

    for (i = 0; i < arg->pin; i++)
    {
        for (j = 0; j < arg->pin; j++)
        {
            m->mat1[i][j] *= arg->num;
        }
    }

    return NULL;
}

// Operación de determinante ejecutada en un hilo
void *thread_det(void *args)
{
    thread_args *arg = (thread_args *)args;
    MATRIX *m = arg->m;

    int result = det(arg->pin, m);
    printf("Determinante de la matriz: %d\n", result);

    return NULL;
}

// Función para calcular el determinante
int det(int pin, MATRIX *m)
{
    if (pin == 2)
    {
        return m->mat1[0][0] * m->mat1[1][1] - m->mat1[0][1] * m->mat1[1][0];
    }
    else if (pin == 3)
    {
        return m->mat1[0][0] * (m->mat1[1][1] * m->mat1[2][2] - m->mat1[1][2] * m->mat1[2][1]) -
               m->mat1[0][1] * (m->mat1[1][0] * m->mat1[2][2] - m->mat1[1][2] * m->mat1[2][0]) +
               m->mat1[0][2] * (m->mat1[1][0] * m->mat1[2][1] - m->mat1[1][1] * m->mat1[2][0]);
    }
    return 0;
}

// Operación de traspuesta ejecutada en un hilo
void *thread_tras(void *args)
{
    thread_args *arg = (thread_args *)args;
    MATRIX *m = arg->m;
    int i, j;

    for (i = 0; i < arg->pin; i++)
    {
        for (j = 0; j < arg->pin; j++)
        {
            m->mat3[j][i] = m->mat1[i][j];
        }
    }

    return NULL;
}

// Función para limpiar la pantalla (solo para sistemas Linux)
void clear_screen(void)
{
#ifdef __linux__
    system("clear");
#endif
}
