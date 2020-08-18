#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int **matrix_allocation(int);
int **free_matrix (int, int **);

int *array_allocation(int);

int binToInt(int, int);
int getMinValue(char []);

double *normalize(double *, int);



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










int *int_array_allocation(int size)
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











double *double_array_allocation(int size)
{
    double *a;

    if (size < 1) {
        printf ("** Error: Invalid parameter **\n");
        return (NULL);
    }

    a = (double *) calloc (size, sizeof(double));
    if (a == NULL) {
        printf ("** Error: Insuficient memory **");
        return (NULL);
    }

    return (a);
}











int binToInt(int num, int lenght)
{
    int decimal_val = 0, base = 1, rem;

    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }

    return decimal_val;
}





void shiftArr1Pos(char *arr1, int arrSize) 
{
    int i, temp;
    temp = arr1[0];
    for(i = 0; i < arrSize-1; i++) 
	{
        arr1[i] = arr1[i+1];
    }
    arr1[i] = temp;
}










int getMinValue(char bin[])
{
    int numericValue;
    int lenght = 8;
    int min = 511;

    for(int i = 0; i < lenght; ++i)
    {
        shiftArr1Pos(bin, lenght);

        numericValue = binToInt(atoi(bin), lenght);
        if (numericValue <= min) min = numericValue;
    }

    return min;
}










// double *normalize(double *imgFeatures, int arraySize)
// {
//     double *normalizedArray = double_array_allocation(arraySize);


//     return normalizedArray;
// }




















#endif