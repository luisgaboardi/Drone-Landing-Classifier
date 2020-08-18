#include "functions.h"

int *ILBP(int **pixel, int size)
{    
    // Allocating matrix aux to store neighbors
    int **aux = matrix_allocation(3);

    // int array with 0 and 1 of the 9 neighbor pixels
    char neighborArray[9];

    // Result Array of ILBP
    int *ILBPArray = int_array_allocation(512);

    // First Step ILBP: Generating aux matrix with 0 and 1 comparing pixel value with the average of the 9 neighbor pixels including itself
    double average;

    int arrayInd, min;
    
    for (int line = 1; line < size-1; ++line)
    {
        for (int col = 1; col < size-1; ++col)
        {
            // Calculate average and create neighbor matrix
            average = 0;
            for (int i = line, x = 0; i <= line+2; ++i, x++)
            {
                for (int j = col, y = 0; j <= col+2; ++j, y++)
                {
                    aux[x][y] = pixel[i-1][j-1];
                    average += aux[x][y];
                }
            }

            average /= 9.0;
            
            // Define neighbor binary word(array) // I may change the path
            arrayInd = 0;
            for (int x = 0; x <= 2; x++)
            {
                for (int y = 0; y <= 2; y++)
                {
                    if (aux[x][y] <= average) aux[x][y] = 0;
                    else aux[x][y] = 1;
                    neighborArray[arrayInd] = aux[x][y] + '0';
                    arrayInd++;
                }
            }

            // Get minimal decimal value from the binary word
            min = getMinValue(neighborArray);

            // Add 1 to the position min in the ILBPArray
            ILBPArray[min]++;
        }
    }

    aux = free_matrix(3, aux);

    return ILBPArray;

}