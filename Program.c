#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each pixel separator in the .txt file
#define SEPARATOR ';'

int get_image_size(char *);
int **read_image(int, char *);

int **matrix_allocation(int);
int **free_matrix (int, int **);


/*
  1) Get size of images - OK
  2) Save them in a dynamic memory variable (matrix) - OK
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
    //DataSet adresses
    char imagesFolder[] = "DataSet/";
    char imageType1[] = "grass";
    char imageType2[] = "asphalt";

    // 50 grass and 50 asphalt
    const float dataSetSize = 100.0;

    // Percentage of how many images will be used for training
    const float trainingProp = 50.0/100.0; 

    // Percentage of how many images will be used for testing
    const float testingProp = (100.0 - trainingProp) / 100.0;
    
    // Get example to determine how many pixels the images have
    char imgEx[] = "DataSet/grass/grass_01.txt";
    int IMAGESIZE = get_image_size(imgEx);

    // Get the max number of digits an image name can have 
    int numberLength = 1;
    int auxDataSize = dataSetSize;
    while (auxDataSize/10 > 0)
    {
        numberLength++;
        auxDataSize /= 10;
    }

    // Image address string
    char *imageAdress;
    // Image number string
    char sNum[numberLength];

    // Select images to read
    for(float j = 1, i = 1; j <= dataSetSize*trainingProp/2;)
    {
        // Allocate enough space to store image adress string
        imageAdress = (char *) malloc(100*sizeof(char));

        // Concatenating substrings to form image adress
        strcat(imageAdress, imagesFolder);

        // Read all grass images
        if(i <= dataSetSize*trainingProp/2)
        {
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "_");
            if(i < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%.0f", i);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("[%.0f] = %s\n", i, imageAdress);
            i++;
        }
        // Read all asphalt images
        else
        {
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "_");
            if(j < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%.0f", j);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("[%.0f] = %s\n", j, imageAdress);
            j++;
        }
        
        // ILBP (read_image(IMAGESIZE, imageAdress));
        read_image(IMAGESIZE, imageAdress);

        free(imageAdress);
        imageAdress = NULL;
        
    }
    
}







//////// Functions ////////







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
        if(counter[i] == SEPARATOR) size++;
    }

    return size;
}










int **read_image(int imgSize, char *imgName)
{
    // Dynamically allocate a matrix to store the pixels values
    int **imgPixelsValues = matrix_allocation(imgSize);

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
        char *pixel = strtok(line, ";");
        imgPixelsValues[0][0] = atoi(pixel);
        for(int column = 1; column < imgSize; ++column)
        {
            pixel = strtok(NULL, ";");
            imgPixelsValues[0][column] = atoi(pixel);
            //printf("[%d] - %d\n", column, imgPixelsValues[0][column]);
        }
    }

    fclose(image);

    return imgPixelsValues;
}










int **matrix_allocation(int size)
{
    int **m;  /* ponteiro para a matriz */

    if (size < 1) { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    /* aloca as linhas da matriz */
    m = (int **) calloc (size, sizeof(int *));	// Um vetor de size ponteiros para int */
    if (m == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for (int i = 0; i < size; i++ ) {
        m[i] = (int*) calloc (size, sizeof(int));	/* size vetores de size ints */
        if (m[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (m); /* retorna o ponteiro para a matriz */
}










int **free_matrix (int size, int **m)
{
  if (m == NULL) return (NULL);
  if (size < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (m);
     }
  for (int i = 0; i < size; i++) free (m[i]); /* libera as linhas da matriz */
  free (m);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}