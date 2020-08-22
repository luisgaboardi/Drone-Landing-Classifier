#include "functions.h"

/*
  1) Get size of images - OK
  2) Save them in a dynamic memory variable (matrix) - OK
  3) ILBP - generate array with ILBP code frequency for each image - OK
  4) GLCM - generate array with the 24 image features (3 for each of the 8 matrixes) - OK
  5) Classifier measured by euclidian distance - OK
  --------- ML vs NN ---------
  5) Create neurons
  6) Design feed-foward neural network with arbitrary neurons in the one hidden layer
  7) Train network using linear regression
  8) Test and return accuracy vs ML
*/

void main()
{


    //////////// Initial values and array allocation //////////// 



    //DataSet adresses
    char imagesFolder[] = "DataSet/";
    char imageType1[] = "asphalt";
    char imageType2[] = "grass";

    // 50 grass and 50 asphalt
    const int dataSetSize = 100;

    // how many images will be used for training
    const int trainingImages = 50;

    // how many images will be used for testing
    const int testingImages = dataSetSize - trainingImages;
    
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

    // Average image features (average result)
    int imageFeatureArraySize = 280;
    double *imgFeatures = double_array_allocation(imageFeatureArraySize);
    double *averageFeatures = double_array_allocation(imageFeatureArraySize);

    // Each image type classification array (average feature data after training)
    double *type1Classification = double_array_allocation(imageFeatureArraySize);
    double *type2Classification = double_array_allocation(imageFeatureArraySize);






    //////////// Generate random order image array to process ////////////



    // Initializes random number generator
    time_t t;
    srand((unsigned) time(&t));

    // Array to store the random image order, half for training and half for testing
    // The images file start with 1, so we'll skip 0
    int randomImageOrder[dataSetSize+1];
    randomImageOrder[0] = 0;

    // Generate sequential array from 1 to 'dataSetSize/2'
    for (int img = 1; img <= dataSetSize/2; ++img) randomImageOrder[img] = img;

    // Shuffle the array to form a random array
    for (int img = 1; img <= dataSetSize/2; ++img) 
    {
        int temp = randomImageOrder[img];
        int randomIndex = (rand() % dataSetSize/2) + 1;
        randomImageOrder[img]         = randomImageOrder[randomIndex];
        randomImageOrder[randomIndex] = temp;
    }






    //////////// Training images in the above mentioned order ////////////



    printf("\n##### TRAINING #####\n\n");
    printf("\n##### Training to type1 images #####\n\n");

    // Go through every training image and do:
    for(int type1 = 1, type2 = 1; type2 <= trainingImages/2;)
    {
        // Erase previous image name to store the next one
        imageAdress[0] = '\0';

        // Read 'trainingImages/2' type1 images
        if(type1 <= trainingImages/2)
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType1, randomImageOrder[type1], numberLength));
            printf(" [%d] = %s\n", type1, imageAdress);
            type1++;
        }

        // Read 'trainingImages/2' training type2 images
        else
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType2, randomImageOrder[type2], numberLength));
            printf(" [%d] = %s\n", type2, imageAdress);
            type2++;
        }

        imgFeatures = image_process(imageAdress, IMAGESIZE);
        
        //////////// One image done ////////////



        //////////// Machine Learning solution ////////////



        // Calculate the sum of the imageFeatures
        for(int s = 0; s < imageFeatureArraySize; ++s) averageFeatures[s] += imgFeatures[s];

        // After reading the first 'trainingImages/2' images of the 'type1'
        if(type1 == trainingImages/2 + 1)
        {
            type1++;
            // Divide the sum of the imgFeatures by the number of images of this type trained to get the average features values
            for(int feature = 0; feature < imageFeatureArraySize; ++feature)
            {
                averageFeatures[feature] /= (trainingImages/2);
                type1Classification[feature] = averageFeatures[feature];
            }

            printf("\n##### Type1 parameters array done! #####\n\n");
            printf("\n##### Training to type2 images #####\n\n");

            // Finally, clear 'averageFeatures' array to now be used for the 'type2' images
            for(int feature = 0; feature < imageFeatureArraySize; ++feature) averageFeatures[feature] = 0;

        }
        // After reading the last 'trainingImages/2' images of the 'type2'
        else if(type2 == trainingImages/2 + 1)
        {
            type2++;
            // Divide the sum of the imgFeatures by the number of images of this type trained to get the average features values
            for(int feature = 0; feature < imageFeatureArraySize; ++feature)
            {
                averageFeatures[feature] /= (trainingImages/2);
                type2Classification[feature] = averageFeatures[feature];
            } 

            printf("\n##### Type2 images parameters array done! #####\n");
            free(averageFeatures);
            
        }

    }




    //////////// Going though the testing image ////////////



    double euclidianDist1, euclidianDist2;
    double correct = 0, falseAceptance = 0, falseRejection = 0;

    printf("\n##### TESTING #####\n");

    // Go through every testing image and do:
    for(int type1 = 1, type2 = 1; type2 <= testingImages/2;)
    {
        // Erase previous image name to store the next one
        imageAdress[0] = '\0';

        // Read 'testingImages/2' type1 images
        if(type1 <= testingImages/2)
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType1, randomImageOrder[type1+trainingImages/2], numberLength));
            type1++;
        }

        // Read 'testingImages/2' type2 images
        else
        {
            strcpy(imageAdress, concatenate_image_adress(imageAdress, imagesFolder, imageType2, randomImageOrder[type2+trainingImages/2], numberLength));
            type2++;
        }

        imgFeatures = image_process(imageAdress, IMAGESIZE);



        //////////// Classifing using minimal euclidian distance ////////////




        for(int i = 0; i < imageFeatureArraySize; ++i)
        {
            euclidianDist1 += pow((imgFeatures[i] - type1Classification[i]), 2);
            euclidianDist2 += pow((imgFeatures[i] - type2Classification[i]), 2);
        }
        euclidianDist1 = sqrt(euclidianDist1);
        euclidianDist2 = sqrt(euclidianDist2);

        if      (euclidianDist1 < euclidianDist2 && type2 == 1) correct++;
        else if (euclidianDist1 < euclidianDist2 && type2  > 1) falseRejection++;
        else if (euclidianDist2 < euclidianDist1 && type2  > 1) correct++;
        else if (euclidianDist2 < euclidianDist1 && type2 == 1) falseAceptance++;      
    
    }




    //////////// Printing results ////////////




    char porc = '%';
    printf("\n##### MACHINE LEARNING RESULTS #####\n");
    printf("Correct:         %.0lf%c\n", 100 * correct/(double)testingImages, porc);
    printf("False Rejection: %.0lf%c\n", 100 * falseRejection/(double)testingImages, porc);
    printf("False Aceptance: %.0lf%c\n\n", 100 * falseAceptance/(double)testingImages, porc);


    free(imgFeatures);
    free(type2Classification);
    free(type1Classification);
    
}