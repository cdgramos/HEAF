#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"


#define minValues 16 //mininum records to compute Hurst Exponent by Autocorrelation Function ! Impirical Value


int main(){

    FILE *fp; // general purpose file pointer

    int N = 0; // number of data records
    int i = 0; // general purpose
    int k = 0; // general purpose


    double *sequence; // input data

    double mu = 0.0; // meanW
    double gamma_0 = 0.0;
    double gamma_1 = 0.0;
    double H = 0.0;


    printf("Opening the raw data file...\n");
    fp = fopen("075.txt","r");

    printf("Counting number of records...\n");
    N = countRecordsInFile(fp);
    rewind(fp);

    printf( "\tNumber of records: %d\n",N);
    if(N <= minValues){
    	printf( "\t\tError: insufficient data\n");
    	exit(1);
    }

    printf("Allocating memory...\n");
    sequence = (double *) calloc((N)+1, sizeof(double));

    if(sequence == NULL){
        printf( "\t\tError: allocating memory\n");
        exit(1);
    }

    printf("Reading raw data and closing the raw data file...\n");
    i = 0;
    while(i < N){
        fscanf(fp,"%lf\n",&sequence[i]);
        i++;
    }

    printf("Computing the mean...\n");
    mu = mean(sequence,N);
    printf("\tMean value is: %lf\n",mu);


    printf("Computing gamma zero and gamma 1...\n");
    k=0;
    for(i=0;i<(N-k);i++){
        gamma_0 += (sequence[i]-mu)*(sequence[i+k]-mu);
    }
    gamma_0 = gamma_0/N;

    k=1;
    for(i=0;i<(N-k);i++){
        gamma_1 += (sequence[i]-mu)*(sequence[i+k]-mu);
    }
    gamma_1 = gamma_1/N;

    printf("\tGamma 0 = %lf\n\tGamma 1 = %lf\n",gamma_0,gamma_1);


    printf("Computing Hurst...\n");

    H = 0.5+ (1 / (2*log(2)) ) * log(1 + (gamma_1/gamma_0));

    printf("\tH = %lf...\n",H);

    printf("Program ended...\n");

    fclose(fp);
    free(sequence);


    return 0;
}
