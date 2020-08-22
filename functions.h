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

double *image_process(char *, int);

double *ILBP(int **, int);
double *GLCM(int **, int);



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
    int lenght = 9;
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









double *image_process(char *imageAdress, int IMAGESIZE)
{
    int **imageRead = matrix_allocation(IMAGESIZE);

    // ILBP return array
    int ILBPSize = 256;
    double *ILBPArray = double_array_allocation(ILBPSize);

    // GLCM return array
    int GLCMSize = 24;
    double *GLCMArray = double_array_allocation(GLCMSize);

    // Image features (final result of each image)
    int imageFeatureArraySize = ILBPSize + GLCMSize;
    double *imgFeatures = double_array_allocation(imageFeatureArraySize);


    // Read above chosen image's pixels values and store in 'imageRead' matrix
    imageRead = read_image(imageAdress, IMAGESIZE);

    // Run ILBP algorithm on the just read image and store normalized result array in 'ILBPArray'
    ILBPArray = ILBP(imageRead, IMAGESIZE);
    ILBPArray = normalize(ILBPArray, ILBPSize);

    // Run GLCM algorithm on the just read image and store result array in 'GLCMArray'
    GLCMArray = GLCM(imageRead, IMAGESIZE);
    GLCMArray = normalize(GLCMArray, GLCMSize);

    // Store ILBP result in the 'imgFeatures' array
    for(int f = 0; f < ILBPSize; ++f) imgFeatures[f] = ILBPArray[f];

    // Store GLCM result in the 'imgFeatures' array after the ILBP results
    for(int f = ILBPSize; f < imageFeatureArraySize; ++f) imgFeatures[f] = GLCMArray[f-ILBPSize];

    return imgFeatures;
}













double *ILBP(int **pixel, int size)
{    
    // Allocating matrix aux to store neighbors
    int **aux = matrix_allocation(3);

    // int array with 0 and 1 of the 9 neighbor pixels
    char neighborArray[9];

    // Result Array of ILBP
    int ILBPSize = 256;
    double *ILBPArray = double_array_allocation(ILBPSize);

    // First Step ILBP: Generating aux matrix with 0 and 1 comparing pixel value with the average of the 9 neighbor including
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

            average /= 8.0;
            
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
            ILBPArray[min] += 1.0;
        }
    }

    aux = free_matrix(3, aux);

    return ILBPArray;

}

















double *GLCM(int **pixel, int size)
{
    int featureSize = 24;
    double *features = double_array_allocation(featureSize);
    int neighborSize = 256;
    int **neighbor = matrix_allocation(neighborSize);
    
    double contrast = 0.0, energy = 0.0, homogeneity = 0.0;
    int counter = 0;



    // South-neighbor
    for (int l = 0; l < size-1; ++l)
    {
        for (int c = 0; c < size; ++c)
        {
            neighbor[pixel[l][c]][pixel[l+1][c]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }


    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // SouthEast-neighbor
    for (int l = 0; l < size-1; ++l)
    {
        for (int c = 1; c < size; ++c)
        {
            neighbor[pixel[l][c]][pixel[l+1][c-1]]++;
        }
    }


    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // East-neighbor
    for (int l = 0; l < size; ++l)
    {
        for (int c = 1; c < size; ++c)
        {
            neighbor[pixel[l][c]][pixel[l][c-1]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // NorthEast-neighbor
    for (int l = 1; l < size; ++l)
    {
        for (int c = 1; c < size-1; ++c)
        {
            neighbor[pixel[l][c]][pixel[l-1][c-1]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // North-neighbor
    for (int l = 1; l < size; ++l)
    {
        for (int c = 0; c < size; ++c)
        {
            neighbor[pixel[l][c]][pixel[l-1][c]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // NorthWest-neighbor
    for (int l = 1; l < size; ++l)
    {
        for (int c = 0; c < size-1; ++c)
        {
            neighbor[pixel[l][c]][pixel[l-1][c+1]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // West-neighbor
    for (int l = 0; l < size; ++l)
    {
        for (int c = 0; c < size-1; ++c)
        {
            neighbor[pixel[l][c]][pixel[l][c+1]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;
    counter++;

    // Zeroing values
    contrast = 0;
    energy = 0;
    homogeneity = 0;

    // SouthWest-neighbor
    for (int l = 0; l < size-1; ++l)
    {
        for (int c = 0; c < size-1; ++c)
        {
            neighbor[pixel[l][c]][pixel[l+1][c+1]]++;
        }
    }

    // Measure features
    for (int l = 0; l < neighborSize; ++l)
    {
        for (int c = 0; c < neighborSize; ++c)
        {
            contrast += fabs(pow(l-c,2)) * neighbor[l][c];
            energy += pow(neighbor[l][c], 2.0);
            homogeneity += neighbor[l][c] / (1.0 + fabs(l-c));
        }
    }

    //contrat /= neighborSize;
    features[counter] = contrast;
    counter++;
    features[counter] = energy;
    counter++;
    features[counter] = homogeneity;

    return features;
}


















#endif