#include "functions.h"

int *ILBP(int **pixel, int size)
{    
    // Allocating matrix aux to store neighbors
    int **aux = matrix_allocation(3);

    // int array with 0 and 1 of the 9 neighbor pixels
    char *neighborArray = (char *) malloc(9*sizeof(char));
    if (neighborArray == NULL) {
        printf ("** Error: Insuficient memory **");
        return (NULL);
    }

    // Result Array of ILBP
    int *ILBPArray = array_allocation(512);

    // First Step ILBP: Generating aux matrix with 0 and 1 comparing pixel value with the average of the 9 neighbor pixels including itself
    float average;

    int arrayInd;
    
    for (int l = 1; l < size-1; ++l)
    {
        for (int c = 1; c < size-1; ++c)
        {
            // Calculate average
            average = 0;
            for (int i = l, x = 0; i <= l+2; ++i, x++)
            {
                for (int j = c, y = 0; j <= c+2; ++j, y++)
                {
                    average += pixel[i-1][j-1];
                }
            }
            average /= 9.0;
            
            // Define neighbor binary array
            arrayInd = 0;
            for (int i = l, x = 0; i <= l+2; ++i, x++)
            {
                for (int j = c, y = 0; j <= c+2; ++j, y++)
                {
                    if (pixel[i-1][j-1] < average) aux[x][y] = 0;
                    else aux[x][y] = 1;
                    neighborArray[arrayInd] = aux[x][y] + '0';
                    arrayInd++;
                }
            }

            ILBPArray[getMinValue(neighborArray)]++;
        }
    }

    aux = free_matrix(3, aux);
    free(neighborArray);

    return ILBPArray;

}