#include "functions.h"

int *GLCM(int **pixel, int size)
{
    int featureSize = 24;
    int *features = array_allocation(featureSize);
    
    int **aux = matrix_allocation(size);

    // Down-neighbor
    for (int l = 0; l < size; ++l)
    {
        for (int c = 0; c < size; ++c)
        {
            
        }
    }

    return features;
}