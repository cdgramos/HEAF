#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"


#define minValues 16 //mininum records to compute Hurst Exponent by Autocorrelation Function ! Impirical Value


int main(){

    FILE *fp; // general purpose file pointer

    int N = 0; // number of data records
    int i = 0; // general purpose


    double *sequence; // input data


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




    printf("Program ended...\n");

    fclose(fp);
    free(sequence);


    return 0;
}
