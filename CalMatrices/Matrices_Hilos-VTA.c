// S.O. AGREVAL
// Fecha: 17/09/2024
// Version: 1.2.2 -> Esta version corre preferentemente en tabletas(ANDROID) 
// Este programa esta basado en nuestra implementacion en batch, pero utilizando el lenguaje C y la 
// posibilidad de utilizar la libreria <pthread.h> para el manejo de hilos. En este csao particular se 
// usara la logica de Multiples procesos por un hilo por proceso, con el fin de resolver un problema de
// la vida real, con la logica de los Hilos y procesos.

#include <stdio.h>
#include <pthread.h>  // Biblioteca para el manejo de hilos

#define N 4

typedef struct
{
    int mat1[N][N];
    int mat2[N][N];
    int mat3[N][N];
} MATRIX;

// Estructura para pasar múltiples parámetros a los hilos
typedef struct {
    int i, j, k, pin, num; 
    MATRIX *m;
} thread_args;

// Declaración de funciones
int menu(int, MATRIX *);
void selection(int, MATRIX *);
void writeMatrix(MATRIX *, int, int, int, int);
void printMatrix(MATRIX *, int, int, int, int);
void *thread_product(void *args);
void *thread_add(void *args);
void *thread_scalar(void *args);
void *thread_det(void *args);
void *thread_tras(void *args);

int det(int, int, int, MATRIX *);
void tras(int, int, int, MATRIX *);

// Punto de entrada que se llama a si mismo para inicializar las Matrices en 0's
int main()
{
    int opc = 7;
    MATRIX m = {.mat1 = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},.mat2 = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, .mat3 = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};

    if (menu(opc, &m))
    {
        system("clear");
        main();
    }
    else
    {
        system("clear");
        printf("Saliendo!\nSi necesita volver a usar, Reinicie...");
    }
}

// Menu el cual nos va a dirigir a las operaciones necesarias
int menu(int opc, MATRIX * m)
{
    int s;
    if (opc == 6)
    {
        return 0;
    }
    else if ((opc > 6) || (opc < 1))
    {
        printf("*****************************************\n");
        printf("*S E L E C C I O N A  U N A  O P C I O N*\n");
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
        system("clear");
        return (menu(s, m));
    }
    else
    {
        selection(opc, m);
    }
    return (1);
}

// Se selecciona la modalidad y creacion de los hilos.
void selection(int opc, MATRIX * m)
{
    int tam, num = 1;
    printf("*****************************************\n");
    printf("*S E L E C C I O N A  U N A  O P C I O N*\n");
    printf("*****************************************\n");
    printf("** Matriz 2 x 2.....................(1)**\n");
    printf("** Matriz 3 x 3.....................(2)**\n");
    printf("** Cancelar..........(Cualquier numero)**\n");
    printf("*****************************************\n");
    printf("\nOpcion: ");
    scanf("%d", &tam);
    if ((tam < 1) || (tam > 2))
    {
        system("clear");
        printf("Volviendo al Inicio...\n");
        system("pause");
        system("clear");
        return;
    }
    if (opc == 1)
    {
        system("clear");
        printf("*** Suma de Matrices %d x %d***:\n", tam + 1, tam + 1);
        writeMatrix(m, 0, 0, tam + 1, 1);
        system("clear");
        printf("*** Suma de Matrices %d x %d***:\n", tam + 1, tam + 1);
        printf("Tus Matrices:\n");
        printMatrix(m, 0, 0, tam + 1, 1);
        printMatrix(m, 0, 0, tam + 1, 2);
        // Creación del hilo para la suma
        pthread_t thread;
        thread_args args = {0, 0, 0, tam + 1, 0, m};
        pthread_create(&thread, NULL, thread_add, (void *)&args);
        pthread_join(thread, NULL);  // Espera a que el hilo termine

        system("pause");
        system("clear");
    }
    else if (opc == 2)
    {
        system("clear");
        printf("*** Multiplicación de Matrices %d x %d***:\n", tam + 1, tam + 1);
        writeMatrix(m, 0, 0, tam + 1, 1);
        system("clear");
        printf("*** Multiplicación de Matrices %d x %d***:\n", tam + 1, tam + 1);
        printf("Tus Matrices:\n");
        printMatrix(m, 0, 0, tam + 1, 1);
        printMatrix(m, 0, 0, tam + 1, 2);
        // Creación del hilo para la multiplicación
        pthread_t thread;
        thread_args args = {0, 0, 0, tam + 1, 0, m};
        pthread_create(&thread, NULL, thread_product, (void *)&args);
        pthread_join(thread, NULL);

        system("pause");
        system("clear");
    }
    else if (opc == 3)
    {
        printf("Ingresa el escalar: ");
        scanf("%d", &num);
        system("clear");
        printf("*** Multiplicación por escalar %d en matriz %d x %d***:\n", num, tam + 1, tam + 1);
        writeMatrix(m, 0, 0, tam + 1, 2);
        system("clear");
        printf("Tu Matriz:\n");
        printMatrix(m, 0, 0, tam + 1, 2);
        // Creación del hilo para la multiplicación por escalar
        pthread_t thread;
        thread_args args = {0, 0, 0, tam + 1, num, m};
        pthread_create(&thread, NULL, thread_scalar, (void *)&args);
        pthread_join(thread, NULL);

        system("pause");
        system("clear");
    }
    else if (opc == 4)
    {
        system("clear");
        printf("*** Determinante de Matriz %d x %d***:\n", tam + 1, tam + 1);
        writeMatrix(m, 0, 0, tam + 1, 2);
        system("clear");
        printf("Tu Matriz:\n");
        printMatrix(m, 0, 0, tam + 1, 2);
        // Creación del hilo para el determinante
        pthread_t thread;
        thread_args args = {0, 0, 0, tam + 1, 0, m};
        pthread_create(&thread, NULL, thread_det, (void *)&args);
        pthread_join(thread, NULL);

        system("pause");
        system("clear");
    }
    else if (opc == 5)
    {
        system("clear");
        printf("*** Traspuesta de Matriz %d x %d***:\n", tam + 1, tam + 1);
        writeMatrix(m, 0, 0, tam + 1, 2);
        system("clear");
        printf("Tu Matriz:\n");
        printMatrix(m, 0, 0, tam + 1, 2);
        // Creación del hilo para la traspuesta
        pthread_t thread;
        thread_args args = {0, 0, 0, tam + 1, 0, m};
        pthread_create(&thread, NULL, thread_tras, (void *)&args);
        pthread_join(thread, NULL);

        system("pause");
        system("clear");
    }
}

// Función para escribir las matrices
void writeMatrix(MATRIX * m, int i, int j, int pin, int mat)
{
    if (mat == 2)
    {
        if (i == pin)
            return;
        else if (j == pin)
            writeMatrix(m, i + 1, 0, pin, mat);
        else
        {
            printf("Matriz %d número de la posición [%d][%d]: ", mat, i, j);
            scanf("%d", &m->mat2[i][j]);
            writeMatrix(m, i, j + 1, pin, mat);
        }
    }
    else
    {
        if (i == pin)
            writeMatrix(m, 0, 0, pin, mat + 1);
        else if (j == pin)
            writeMatrix(m, i + 1, 0, pin, mat);
        else
        {
            printf("Matriz %d número de la posición [%d][%d]: ", mat, i, j);
            scanf("%d", &m->mat1[i][j]);
            writeMatrix(m, i, j + 1, pin, mat);
        }
    }
}

// Operación de suma ejecutada en un hilo
void *thread_add(void *args)
{
    thread_args *arg = (thread_args *)args;
    int i = arg->i, j = arg->j, pin = arg->pin;
    MATRIX *m = arg->m;

    if (i == pin)
    {
        printf("Resultado:\n");
        printMatrix(m, 0, 0, pin, 3);
        return (NULL);
    }
    else if (j == pin)
        thread_add(&(thread_args){i + 1, 0, 0, pin, 0, m});
    else
    {
        m->mat3[i][j] = m->mat2[i][j] + m->mat1[i][j];
        thread_add(&(thread_args){i, j + 1, 0, pin, 0, m});
    }
    return (NULL);
}

// Operación de multiplicación ejecutada en un hilo
void *thread_product(void *args)
{
    thread_args *arg = (thread_args *)args;
    int i = arg->i, j = arg->j, k = arg->k, pin = arg->pin;
    MATRIX *m = arg->m;

    if (i == pin)
    {
        printf("Resultado:\n");
        printMatrix(m, 0, 0, pin, 3);
        return (NULL);
    }
    else if (j == pin)
        thread_product(&(thread_args){i + 1, 0, 0, pin, 0, m});
    else if (k == pin)
    {
        thread_product(&(thread_args){i, j + 1, 0, pin, 0, m});
    }
    else
    {
        m->mat3[i][j] += m->mat1[i][k] * m->mat2[k][j];
        thread_product(&(thread_args){i, j, k + 1, pin, 0, m});
    }
    return (NULL);
}

// Operación de multiplicación por escalar ejecutada en un hilo
void *thread_scalar(void *args)
{
    thread_args *arg = (thread_args *)args;
    int i = arg->i, j = arg->j, pin = arg->pin, num = arg->num;
    MATRIX *m = arg->m;

    if (i == pin)
    {
        printf("Resultado:\n");
        printMatrix(m, 0, 0, pin, 3);
        return (NULL);
    }
    else if (j == pin)
        thread_scalar(&(thread_args){i + 1, 0, 0, pin, num, m});
    else
    {
        m->mat3[i][j] = m->mat2[i][j] * num;
        thread_scalar(&(thread_args){i, j + 1, 0, pin, num, m});
    }
    return (NULL);
}

// Operación de determinante ejecutada en un hilo
void *thread_det(void *args)
{
    thread_args *arg = (thread_args *)args;
    int i = arg->i, pin = arg->pin;
    MATRIX *m = arg->m;

    printf("Determinante = |%d|\n", det(i, i, pin, m));
    return (NULL);
}

// Operación de traspuesta ejecutada en un hilo
void *thread_tras(void *args)
{
    thread_args *arg = (thread_args *)args;
    int i = arg->i, j = arg->j, pin = arg->pin;
    MATRIX *m = arg->m;

    if (i == pin)
    {
        printf("Resultado:\n");
        printMatrix(m, 0, 0, pin, 3);
        return NULL;
    }
    else if (j == pin)
        thread_tras(&(thread_args){i + 1, 0, 0, pin, 0, m});
    else
    {
        m->mat3[j][i] = m->mat2[i][j];
        thread_tras(&(thread_args){i, j + 1, 0, pin, 0, m});
    }
    return (NULL);
}

// Función para imprimir matrices
void printMatrix(MATRIX * m, int i, int j, int pin, int mat)
{
    if (i == pin)
	{
		putchar('\n');
        return;
	}
    else if (j == pin)
    {
        printf("\n");
        printMatrix(m, i + 1, 0, pin, mat);
    }
    else
    {
        if (mat == 1)
            printf("[%d] ", m->mat1[i][j]);
        else if (mat == 2)
            printf("[%d] ", m->mat2[i][j]);
        else
            printf("[%d] ", m->mat3[i][j]);
        printMatrix(m, i, j + 1, pin, mat);
    }
}

// Función para calcular el determinante
int det(int i, int j, int pin, MATRIX *m)
{
    if (pin == 2)  // Matriz 2x2
        return (m->mat2[0][0] * m->mat2[1][1] - m->mat2[0][1] * m->mat2[1][0]);
    else //Matriz 3x3
    	return((m->mat2[0][0] * m->mat2[1][1] * m->mat2[2][2]) + (m->mat2[0][1] * m->mat2[1][2] * m->mat2[2][0]) + (m->mat2[0][2] * m->mat2[1][0] * m->mat2[2][1]) - (m->mat2[2][0] * m->mat2[1][1] * m->mat2[0][2]) - (m->mat2[2][1] * m->mat2[1][2] * m->mat2[0][0]) - (m->mat2[0][1] * m->mat2[1][0] * m->mat2[2][2]));
}
