#include "functions.h"

int *ILBP(int **pixel)
{ 
    //** Find way to get the image size here without passing as parameter) **//
    
    // Allocating matrix aux to store neighbors
    int **aux = matrix_allocation(3);

    // int array with 0 and 1 of the 9 neighbor pixels
    char *neighborArray = (char *) malloc(9*sizeof(char));
    if (neighborArray == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }

    // Result Array of ILBP
    int *ILBPArray = array_allocation(256);

    // First Step ILBP: Generating aux matrix with 0 and 1 comparing pixel value with the average of the 9 neighbor pixels including itself
    float average;

    int arrayInd;
    
    for (int l = 1; l < 1024; ++l)
    {
        for (int c = 1; c < 1024; ++c)
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

    int counter = 0;

    for (int i = 0; i < 256; ++i)
    {
        //printf("[%d]= %d\n", i, ILBPArray[i]);
        counter += ILBPArray[i];
    }

    aux = free_matrix(3, aux);
    free(neighborArray);

    return ILBPArray;

}