#include "ILBP.h"
#include "GLCM.h"

// Each pixel separator in the .txt file
#define SEPARATOR ";"

int get_image_size(char *);
int **read_image(char *, int);


/*
  1) Get size of images - OK
  2) Save them in a dynamic memory variable (matrix) - OK
  3) ILBP - generate array with ILBP code frequency for each image - OK
  4) GLCM - generate array with the 24 image features (3 for each of the 8 matrixes) - OK
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
    char imageType1[] = "asphalt";
    char imageType2[] = "grass";

    // 50 grass and 50 asphalt
    const int dataSetSize = 100;

    // how many images will be used for training
    const int trainingImages = 50;

    // how many images will be used for testing
    const int testingImages = 100 - trainingImages;
    
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

    // Image address string (arbitrary size)
    char imageAdress[100];

    // Image number string (needed to select image and concatenate with the imageAdress)
    char sNum[numberLength];

    // Store the matrix of the read image
    int **imageRead = matrix_allocation(IMAGESIZE);

    // ILBP return array
    int ILBPSize = 256;
    int *ILBPArray = int_array_allocation(ILBPSize);

    // GLCM return array
    int GLCMSize = 24;
    double *GLCMArray = double_array_allocation(GLCMSize);

    // Image features (final result of each image)
    int imageFeatureArraySize = 280;
    double *imgFeatures = double_array_allocation(imageFeatureArraySize);

    // Average image features (average result)
    double *averageFeatures = double_array_allocation(imageFeatureArraySize);

    // Classification array (average feature data after training) for each type
    double *type1Classification = double_array_allocation(imageFeatureArraySize);
    double *type2Classification = double_array_allocation(imageFeatureArraySize);

    // Initializes random number generator
    time_t t;
    srand((unsigned) time(&t));

    // Array to store the random image order, half for training and half for testing
    int randomImageOrder[dataSetSize+1];
    randomImageOrder[0] = 0;

    // Generate sequential array from 1 to 50
    for (int img = 1; img <= trainingImages; ++img) randomImageOrder[img] = img;

    // Shuffle the array to form a random array
    for (int img = 1; img <= trainingImages; ++img) 
    {
        int temp = randomImageOrder[img];
        int randomIndex = (rand() % trainingImages) + 1;
        randomImageOrder[img]         = randomImageOrder[randomIndex];
        randomImageOrder[randomIndex] = temp;
    }

    // Select images to read
    for(int type1 = 1, type2 = 1; type2 <= trainingImages/2;)
    {
        // Erase previous image name to store the next one
        imageAdress[0] = '\0';

        // Concatenating substrings to form image adress
        strcat(imageAdress, imagesFolder);

        // Read 'trainingImages/2' asphalt images
        if(type1 <= trainingImages/2)
        {
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType1);
            strcat(imageAdress, "_");
            // The images below 10 in the dataset used have a 0 before the number
            if(randomImageOrder[type1] < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%d", randomImageOrder[type1]);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("\n\n**** [Image %d] = %s ****\n", type1, imageAdress);
            type1++;
        }

        // Read 'trainingImages/2' training grass images
        else
        {
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "/");
            strcat(imageAdress, imageType2);
            strcat(imageAdress, "_");
            // The images below 10 in the dataset used have a 0 before the number
            if(randomImageOrder[type2] < 10) strcat(imageAdress, "0");
            sprintf(sNum, "%d", randomImageOrder[type2]);
            strcat(imageAdress, sNum);
            strcat(imageAdress, ".txt");
            printf("\n\n**** [Image %d] = %s ****\n", type2, imageAdress);
            type2++;
        }
        
        // Read image's pixels values and store in 'imageRead' matrix
        imageRead = read_image(imageAdress, IMAGESIZE);

        // Run ILBP algorithm on the just read image and store result array in 'ILBPArray'
        ILBPArray = ILBP(imageRead, IMAGESIZE);
        //printf("ILBP Done.\n");

        // Run GLCM algorithm on the just read image and store result array in 'ILBPArray'
        GLCMArray = GLCM(imageRead, IMAGESIZE);
        //printf("GLCM Done.\n");

        // Store ILBP result in the 'imgFeatures' array
        for(int f = 0; f < ILBPSize; ++f) imgFeatures[f] = ILBPArray[f];

        // Store GLCM result in the 'imgFeatures' array after the ILBP results
        for(int f = ILBPSize; f < imageFeatureArraySize; ++f) imgFeatures[f] = GLCMArray[f-ILBPSize];

        // Normalize
        //imgFeatures = normalize(imgFeatures, imageFeatureArraySize);

        // Calculate the sum of the imageFeatures
        for(int s = 0; s < imageFeatureArraySize; ++s) averageFeatures[s] += imgFeatures[s];

        // After reading the first 'trainingImages/2' images of the 'type1'
        if(type1 == trainingImages/2 + 1)
        {
            type1++;
            // Divide the sum of the imgFeatures by the number of images os this type trained to get the average features values
            for(int feature = 0; feature < imageFeatureArraySize; ++feature)
            {
                averageFeatures[feature] /= (trainingImages/2);
                // Store data
                type1Classification[feature] = averageFeatures[feature];
            }

            printf("*Type1 parameters array done!!*\n");




            // TESTING



            // Finally, clear 'averageFeatures' array to now be used for the 'type2' images
            for(int feature = 0; feature < imageFeatureArraySize; ++feature) averageFeatures[feature] = 0;

        }
        // After reading the last 'trainingImages/2' images of the 'type2'
        else if(type2 == trainingImages/2 + 1)
        {
            type2++;
            // Divide the sum of the imgFeatures by the number of images os this type trained to get the average features values
            for(int feature = 0; feature < imageFeatureArraySize; ++feature)
            {
                averageFeatures[feature] /= (trainingImages/2);
                // Store data
                type2Classification[feature] = averageFeatures[feature];
            } 

            printf("*Type2 parameters array done!!*\n");
            free(imgFeatures);
            free(ILBPArray);
            free(GLCMArray);
            free(averageFeatures);



            // TESTING



            
        }

    }

    free(type2Classification);
    free(type1Classification);
    
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