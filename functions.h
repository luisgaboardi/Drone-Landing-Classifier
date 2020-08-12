#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int **matrix_allocation(int);
int **free_matrix (int, int **);

int *array_allocation(int);

int binToInt(char [], int);
int getMinValue(char []);





int **matrix_allocation(int size)
{
    int **m;

    if (size < 1) {
        printf ("** Error: Invalid parameter **\n");
        return (NULL);
    }

    m = (int **) calloc (size, sizeof(int *));
    if (m == NULL) {
        printf ("** Error: Insuficient memory **");
        return (NULL);
    }

    for (int i = 0; i < size; i++ ) {
        m[i] = (int*) calloc (size, sizeof(int));
        if (m[i] == NULL) {
            printf ("** Error: Insuficient memory **");
            return (NULL);
        }
    }
    return (m);
}










int **free_matrix (int size, int **m)
{
  if (m == NULL) return (NULL);
  if (size < 1) {
     printf ("** Error: Invalid parameter **\n");
     return (m);
     }
  for (int i = 0; i < size; i++) free (m[i]);
  free (m);
  return (NULL);
}










int *array_allocation(int size)
{
    int *a;

    if (size < 1) {
        printf ("** Error: Invalid parameter **\n");
        return (NULL);
    }

    a = (int *) calloc (size, sizeof(int));
    if (a == NULL) {
        printf ("** Error: Insuficient memory **");
        return (NULL);
    }

    return (a);
}











int binToInt(char num[], int lenght) // 001000110
{
    int decimal = 0;
    for (int i = 0; i <= lenght; ++i)
    {
        decimal += ((int) num[i] - '0') * pow(2.0, lenght-i);
    }

    return decimal;
}









int getMinValue(char bin[])
{
    int numericValue = 252;
    int lenght = 8;
    int min = numericValue;
    char aux;

    for(int i = 0; i < lenght; ++i)
    {
        aux = bin[lenght];
        for (int i = lenght; i > 0; --i)
        { 
            bin[i] = bin[i-1];
        }
        bin[0] = aux;
        
        numericValue = binToInt(bin, lenght);
        
        if(numericValue < min) min = numericValue;
    }

    return min;
}



#endif