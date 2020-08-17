#include "functions.h"
#include "math.h"

double *GLCM(int **pixel, int size)
{
    int featureSize = 24;
    double *features = double_array_allocation(featureSize);
    int neighborSize = 256;
    int **neighbor = matrix_allocation(neighborSize);
    
    int **aux = matrix_allocation(size);
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