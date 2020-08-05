#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getImageSize(char *);

/*
  1) Get size of images - OK
  2) Save them in a dynamic(?) memory variable (matrix)
  3) ILBP - generate vector with ILBP code frequency
  4) GLCM
  5) Classifier with Machine Learning
  --------- ML vs NN ---------
  5) Create neurons
  6) Design feed-foward neural network with arbitrary neurons in the one hidden layer
  7) Train network using linear regression
  8) Test and return accuracy vs ML
*/

void main()
{
    // Change adress value if using another DataSet
    char imgExample[] = "DataSet/grass/grass_01.txt";
    const int IMAGESIZE = getImageSize(imgExample);

    printf("%d\n", IMAGESIZE);
}


// Functions //

int getImageSize(char *fileLocation)
{
    FILE *image;
    char *counter = NULL;
    int size = 1; // Between 0 and 1, depending if the file has a separator in the last element of the line
    const char SEPARATOR = ';';

    image = fopen(fileLocation, "r");
    fscanf(image, "%ms", &counter);

    for(int i = 0; i < strlen(counter); ++i)
    {
        if(counter[i] == SEPARATOR) size++;
    }
    return size;
}