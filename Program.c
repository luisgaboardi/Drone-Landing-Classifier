#include "ILBP.h"
#include "GLCM.h"

// Each pixel separator in the .txt file
#define SEPARATOR ";"

int get_image_size(char *);
int **read_image(int, char *);


/*
  1) Get size of images - OK
  2) Save them in a dynamic memory variable (matrix) - OK
  3) ILBP - generate array with ILBP code frequency for each image - OK
  4) GLCM - generate array with the 24 image features (3 for each of the 8 matrixes)
  5) Classifier measured by euclidian distance
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
    char imageAdress[100];

    // Store the matrix of the read image
    int **imageRead = matrix_allocation(IMAGESIZE);

    // Image number string
    char sNum[numberLength];

    // ILBP return array
    int *ILBPArray = int_array_allocation(256);

    // GLCM return array
    double *GLCMArray = double_array_allocation(24);

    // Image features (final result of each image)
    double *imgFeatures = double_array_allocation(280);

    // Average ILBP
    double *averageFeatures = double_array_allocation(280);

    // Initializes random number generator
    time_t t;
    srand((unsigned) time(&t));
    int random[(int)(dataSetSize*trainingProp+1)];
    random[0] = 0;

    // Generate random number array between 1 - 50
    for (int i = 1; i <= dataSetSize*trainingProp; ++i)
    {
        random[i] = i;
    }

    for (int i = 1; i <= dataSetSize*trainingProp; i++) // Shuffle
    {
        int temp = random[i];
        int randomIndex = rand() % (int) dataSetSize*trainingProp + 1;
        random[i]           = random[randomIndex];
        random[randomIndex] = temp;
    }

    // Select images to read
    for(int j = 1, i = 1; j <= dataSetSize*trainingProp/2;)
    {
        imageAdress[0] = '\0';
        // Concatenating substrings to form image adress
        strcat(imageAdress, imagesFolder);

        // Read all grass images
        if(i <= dataSetSize*trainingProp/2)
        {
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "_");
            if(random[i] < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%d", random[i]);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("\n\n**** [Image %d] = %s ****\n", i, imageAdress);
            i++;
        }
        // Read all asphalt images
        else
        {
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "_");
            if(random[j] < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%d", random[j]);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("\n\n**** [Image %d] = %s ****\n", j, imageAdress);
            j++;
        }
        
        imageRead = read_image(IMAGESIZE, imageAdress);

        ILBPArray = ILBP(imageRead, IMAGESIZE);
        printf("ILBP Done.\n");

        GLCMArray = GLCM(imageRead, IMAGESIZE);
        printf("GLCM Done.\n");

        for(int i = 0; i < 256; ++i)
        {
            // printf("[%d] = %d\t", i, ILBPArray[i]);
            imgFeatures[i] = ILBPArray[i];
        }

        for(int i = 256; i < 280; ++i)
        {
            // printf("\n{%d} = %.4lf", i, GLCMArray[i-256]);
            imgFeatures[i] = GLCMArray[i-256];
        }

        printf("*Image features array created!*\n");

        free(ILBPArray);

        free(GLCMArray);

    }

    free(imgFeatures);
    
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
        if(counter[i] == SEPARATOR[0]) size++;
    }

    return size;
}










int **read_image(int imgSize, char *imgName)
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