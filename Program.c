#include "ILBP.h"
#include "GLCM.h"


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
    //char sNum[numberLength];

    // Main matrix and arrays allocations
    // Store the matrix of the image read
    int **imageRead = matrix_allocation(IMAGESIZE);

    // ILBP return array
    int ILBPSize = 256;
    double *ILBPArray = double_array_allocation(ILBPSize);

    // GLCM return array
    int GLCMSize = 24;
    double *GLCMArray = double_array_allocation(GLCMSize);

    // Image features (final result of each image)
    int imageFeatureArraySize = ILBPSize + GLCMSize; // 280
    double *imgFeatures = double_array_allocation(imageFeatureArraySize);

    // Average image features (average result)
    double *averageFeatures = double_array_allocation(imageFeatureArraySize);

    // Each image type classification array (average feature data after training)
    double *type1Classification = double_array_allocation(imageFeatureArraySize);
    double *type2Classification = double_array_allocation(imageFeatureArraySize);

    // Initializes random number generator
    time_t t;
    srand((unsigned) time(&t));

    // Array to store the random image order, half for training and half for testing
    // The images file start with 1, so we'll skip 0
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

    // Go through every training image and do:
    for(int type1 = 1, type2 = 1; type2 <= trainingImages/2;)
    {
        // Erase previous image name to store the next one
        imageAdress[0] = '\0';

        // Read 'trainingImages/2' asphalt images
        if(type1 <= trainingImages/2)
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType1, randomImageOrder[type1], numberLength));
            printf("\n\n**** [Image %d] = %s ****\n", type1, imageAdress);
            type1++;
        }

        // Read 'trainingImages/2' training grass images
        else
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType1, randomImageOrder[type1], numberLength));
            printf("\n\n**** [Image %d] = %s ****\n", type2, imageAdress);
            type2++;
        }
        
        // Read above chosen image's pixels values and store in 'imageRead' matrix
        imageRead = read_image(imageAdress, IMAGESIZE);

        // Run ILBP algorithm on the just read image and store result array in 'ILBPArray'
        ILBPArray = ILBP(imageRead, IMAGESIZE);
        // Normalize
        ILBPArray = normalize(ILBPArray, ILBPSize);
        printf("ILBP Done.\n");

        // Run GLCM algorithm on the just read image and store result array in 'GLCMArray'
        GLCMArray = GLCM(imageRead, IMAGESIZE);
        GLCMArray = normalize(GLCMArray, GLCMSize);
        printf("GLCM Done.");

        // Store ILBP result in the 'imgFeatures' array
        for(int f = 0; f < ILBPSize; ++f) imgFeatures[f] = ILBPArray[f];

        // Store GLCM result in the 'imgFeatures' array after the ILBP results
        for(int f = ILBPSize; f < imageFeatureArraySize; ++f) imgFeatures[f] = GLCMArray[f-ILBPSize];

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

            printf("\n***Type1 parameters array done!!***\n");

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
            
        }

    }

    // TESTING //






    free(type2Classification);
    free(type1Classification);
    
}