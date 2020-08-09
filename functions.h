#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>


int **matrix_allocation(int);
int **free_matrix (int, int **);

int *array_allocation(int);

int binToInt(int);
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



#endif