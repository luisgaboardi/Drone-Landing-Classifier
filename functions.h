#include <stdio.h>
#include <stdlib.h>


int **matrix_allocation(int);
int **free_matrix (int, int **);

int *array_allocation(int);

int binToInt(int);
int getMinValue(char []);





int **matrix_allocation(int size)
{
    int **m;  /* ponteiro para a matriz */

    if (size < 1) { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    /* aloca as linhas da matriz */
    m = (int **) calloc (size, sizeof(int *));	// Um vetor de size ponteiros para int */
    if (m == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for (int i = 0; i < size; i++ ) {
        m[i] = (int*) calloc (size, sizeof(int));	/* size vetores de size ints */
        if (m[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (m); /* retorna o ponteiro para a matriz */
}










int **free_matrix (int size, int **m)
{
  if (m == NULL) return (NULL);
  if (size < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (m);
     }
  for (int i = 0; i < size; i++) free (m[i]); /* libera as linhas da matriz */
  free (m);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}










int *array_allocation(int size)
{
    int *a;

    if (size < 1) {
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }

    a = (int *) calloc (size, sizeof(int));
    if (a == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }

    return (a);
}











int binToInt(int num)
{
    int binary_val, decimal_val = 0, base = 1, rem;
 
    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
    return decimal_val;
}









int getMinValue(char bin[])
{
    int numericValue = binToInt(atoi(bin));
    int min = numericValue;
    char aux;

    for(int i = 0; i < 8; ++i)
    {
        aux = bin[8];
        for (int i = 8; i > 0; --i)
        { 
            bin[i] = bin[i-1];
        }
        bin[0] = aux;
        numericValue = binToInt(atoi(bin));
        
        if(numericValue < min) min = numericValue;
    }

    return min;
}