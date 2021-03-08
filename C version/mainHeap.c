#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>

#include "matrix.h"

#define MATRIX_SIZE 11
#define MAX_MATRIX_VALUE 10


Matrix* getMinor(Matrix* matrix,int row,int col){
    checkBorders(matrix,row,col);
    Matrix* resMatrix = (Matrix*) calloc(sizeof(Matrix),1);
    init(resMatrix,matrix->n - 1);
    int curI = 0, curJ = 0;
    for(int i = 0;i < matrix->n; i++){
        curJ = 0;
        if (i == row){
            continue;
        }
        for(int j = 0;j < matrix->n;j++){
            if (j != col){
                setElement(resMatrix,curI,curJ,matrix->array[i][j]);
                curJ++;
            }
        }
        curI++;
    }
    return resMatrix;
}


long long calcDeterminant(Matrix* matrix){
    if (!matrix){
        perror("matrix is empty!");
    }

    if (matrix->n == 0) {
        return 0;
    }
    else if (matrix->n == 1) {
        return matrix->array[0][0];
    }
    else if (matrix->n == 2) {
        return matrix->array[0][0] * matrix->array[1][1]
               - matrix->array[0][1] * matrix->array[1][0];
    }
    else {
        long long res = 0;
        for(int i = 0; i < matrix->n; i++){
            Matrix* minor = getMinor(matrix,i,0);
            long long calc = matrix->array[i][0] * calcDeterminant(minor);
            destroy(minor);
            free(minor);
            if (i % 2 == 1){
                calc *= -1;
            }
            res += calc;
        }
        return res;
    }
}

void readData(Matrix* matrix){
    //const char* filePath = "/home/rugewit/Programming/Cpp/OS/Lab3/data.txt";
    const char* filePath = "C:\\Users\\rugiv\\IdeaProjects\\untitled1\\src\\input.txt";
    FILE* filePtr = fopen(filePath,"r");
    if (!filePtr){
        printf("can't open file \n");
    }

    for(int i = 0;i < MATRIX_SIZE; i++){
        for(int j = 0;j < MATRIX_SIZE; j++){
            fscanf(filePtr,"%d",&matrix->array[i][j]);
        }
    }

    fclose(filePtr);
}

int main() {
    srand(time(NULL));
    Matrix matrix;
    init(&matrix,MATRIX_SIZE);

    //fillRandomNumbers(&matrix,MAX_MATRIX_VALUE);
    readData(&matrix);

    clock_t timeBegin = clock();

    printf("Default is %lld\n",calcDeterminant(&matrix));

    clock_t timeEnd = clock();
    double timeSpent = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;

    printf("time is %f\n",timeSpent);

    destroy(&matrix);

    return 0;
}
