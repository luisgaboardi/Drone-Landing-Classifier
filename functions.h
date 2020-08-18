#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int **matrix_allocation(int);
int **free_matrix (int, int **);
int *int_array_allocation(int);
double *double_array_allocation(int);

char *concatenate_image_adress(char *imageAdress, char *imagesFolder, char *imageType, int nImg, int numberLength);

// Each pixel separator in the .txt file
#define SEPARATOR ";"
int get_image_size(char *);
int **read_image(char *, int);

int binToInt(int, int);
void shiftArr1Pos(char *, int);
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








char *concatenate_image_adress(char *imageAdress, char *imagesFolder, char *imageType, int nImg, int numberLength)
{
    // Convert int image number to char array
    char sNum[numberLength];

    strcat(imageAdress, imagesFolder);
    strcat(imageAdress, imageType);
    strcat(imageAdress, "/");
    strcat(imageAdress, imageType);
    strcat(imageAdress, "_");
    // The images below 10 in the dataset used have a 0 before the number
    if(nImg < 10) strcat(imageAdress, "0");
    sprintf(sNum, "%d", nImg);
    strcat(imageAdress, sNum);
    strcat(imageAdress, ".txt");

    return imageAdress;
}











int get_image_size(char *fileLocation)
{
    FILE *image;
    char *counter = NULL;
    int size = 1; // Between 0 and 1, depending if the file has a separator in the last element of the line

    image = fopen(fileLocation, "r");
    fscanf(image, "%ms", &counter);
    fclose(image);

    for(int i = 0; i < strlen(counter); ++i)
    {
        if(counter[i] == SEPARATOR[0]) size++;
    }

    return size;
}










int **read_image(char *imgName, int imgSize)
{
    // Dynamically allocate a matrix to store the pixels values
    int **imgPixelsValues = matrix_allocation(imgSize);
    if(!imgPixelsValues)
    {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }

    // Open image in read mode
    FILE *image = fopen(imgName, "r");
    if (!image)
    {
        perror("Error while opening this file");
        exit(EXIT_FAILURE);
    }

    // Declaring variables to read file
    char *line;
    size_t len = 0;

    // Read each line as string
    for (int l = 0; getline(&line, &len, image) != -1; ++l)
    {
        //Splitting string to separate each pixel value
        char *pixel = strtok(line, SEPARATOR);
        imgPixelsValues[l][0] = atoi(pixel);
        for(int column = 1; column < imgSize; ++column)
        {
            pixel = strtok(NULL, SEPARATOR);
            imgPixelsValues[l][column] = atoi(pixel);
        }
    }

    fclose(image);

    return imgPixelsValues;
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










double *normalize(double *imgFeatures, int arraySize)
{
    double *normalizedArray = double_array_allocation(arraySize);
    // Aux variables
    double min = imgFeatures[0], max = -1.0;

    // Get max and min values
    for(int f = 0; f < arraySize; ++f)
    {
        if (imgFeatures[f] < min) min = imgFeatures[f];
        if (imgFeatures[f] > max) max = imgFeatures[f]; 
    }

    for(int i = 0; i < arraySize; ++i) normalizedArray[i] = (imgFeatures[i] - min)/(max - min);

    return normalizedArray;
}




















#endif