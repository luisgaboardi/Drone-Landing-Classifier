#include <stdio.h>

int *ILBP(int **pixel)
{ 
    //** Find way to get the image size here without passing as parameter) **//
    
    // Allocating matrix with same size as "pixel"
    int **aux = (int **) calloc (1025, sizeof(int *));
    if (aux == NULL) {
        printf ("** Error: Insuficient memory **");
        return (NULL);
    }
    
    for (int i = 0; i < 1025; i++ ) {
        aux[i] = (int*) calloc (1025, sizeof(int));
        if (aux[i] == NULL) {
            printf ("** Error: Insuficient memory **");
            return (NULL);
        }
    }

    // First Step ILBP: Generating matrix with 0 and 1 comparing pixel value with the average of the 9 neighbor pixels including itself
    float average;
    
    for (int l = 1; l < 1024; ++l)
    {
        for (int c = 1; c < 1024; ++c)
        {
            // Get average
            average = 0;
            average += pixel[l-1][c-1] + pixel[l-1][c] + pixel[l-1][c+1];
            average += pixel[l][c-1] + pixel[l][c] + pixel[l][c+1];
            average += pixel[l+1][c-1] + pixel[l+1][c] + pixel[l+1][c+1];
            average /= 9.0; 

            for (int i = l; i < l+2; ++i)
            {
                for (int j = c; j < c+2; ++j)
                {
                    // Compare each neighbor with the average
                    if(pixel[i-1][j-1] < average) aux[i-1][j-1] = 0;
                    else aux[i-1][j-1] = 1;
                }
            }
        }
    }

}