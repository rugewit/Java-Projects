#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"

#define MATRIX_SIZE 11
#define THREAD_SIZE 10
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


typedef struct {
    int length;
    double calcTime;
    int* row;
    int* col;
    long long* res;
} pthrData;


Matrix globalMatrix;

void* threadFunc(void* thread_data){
    pthrData* data = (pthrData*) thread_data;

    clock_t timeBegin = clock();

    for(int i = 0;i < data->length; i++){
        Matrix* minor = getMinor(&globalMatrix,data->row[i],data->col[i]);
        long long calc = globalMatrix.array[data->row[i]][0] * calcDeterminant(minor);
        destroy(minor);
        free(minor);
        if (data->row[i] % 2 == 1){
            calc *= -1;
        }
        data->res[i] = calc;
    }

    clock_t timeEnd = clock();

    data->calcTime = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;

    return NULL;
}


int* splitLinesForThreading(int matrixSize, int threadSize) {
    if (threadSize > matrixSize){
        perror("ERROR threadSize > matrixSize\n");
    }
    int* linesInThread = (int*) calloc(sizeof(int), threadSize);
    int maxLinesPerThread = (int) ceil( (double) matrixSize / threadSize);
    int difference = maxLinesPerThread * threadSize - matrixSize;
    for(int i = 0;i < threadSize; i++){
        linesInThread[i] = maxLinesPerThread;
    }

    if (difference > threadSize){
        perror("ERROR difference > threadSize\n");
    }

    if (difference == threadSize){
        perror("ERROR difference == threadSize\n");
    }

    if (difference > 0){
        for(int i = threadSize - 1; difference > 0; i--){
            linesInThread[i]--;
            difference--;
        }
    }
    return linesInThread;
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
    pthread_t* threads = (pthread_t*) calloc(sizeof(pthread_t),THREAD_SIZE);
    pthrData* threadsData = (pthrData*) calloc(sizeof(pthrData),THREAD_SIZE);
    Matrix matrix;
    init(&matrix,MATRIX_SIZE);
    init(&globalMatrix,MATRIX_SIZE);
    //fillRandomNumbers(&matrix,MAX_MATRIX_VALUE);
    readData(&matrix);
    copy(&matrix,&globalMatrix);

    int* linesPerThread = splitLinesForThreading(MATRIX_SIZE,THREAD_SIZE);

    clock_t timeBegin = clock();
    int curLine = 0;

    for(int i = 0;i < THREAD_SIZE; i++){
        int linesCount = linesPerThread[i];

        threadsData[i].length = linesCount;
        threadsData[i].calcTime = 0;
        threadsData[i].row = (int*) calloc(sizeof(int),linesCount);
        threadsData[i].col = (int*) calloc(sizeof(int),linesCount);
        threadsData[i].res = (long long*) calloc(sizeof(long long),linesCount);

        for(int j = 0;j < linesCount; j++){
            threadsData[i].row[j] = curLine;
            threadsData[i].col[j] = 0;
            threadsData[i].res[j] = 0;
            curLine++;
        }
        pthread_create(&(threads[i]), NULL, threadFunc, &(threadsData[i]));
    }

    free(linesPerThread);

    for(int i = 0; i < THREAD_SIZE; i++){
        pthread_join(threads[i], NULL);
    }

    long long res = 0;
    double calcTimeWithoutSync = 0;

    for(int i = 0; i < THREAD_SIZE; i++){
        for(int j = 0;j < threadsData[i].length; j++){
            res += threadsData[i].res[j];
        }
        //calcTimeWithoutSync += threadsData[i].calcTime;
    }

    printf("Parallel %lld\n",res);

    clock_t timeEnd = clock();
    double timeSpent = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;

    printf("time is %lf\n",timeSpent);
   // printf("calcTime is %lf\n",calcTimeWithoutSync / 2.0f);

    for(int i = 0;i < THREAD_SIZE; i++){
        free(threadsData[i].row);
        free(threadsData[i].col);
        free(threadsData[i].res);
    }

    destroy(&matrix);
    destroy(&globalMatrix);
    free(threads);
    free(threadsData);

    return 0;
}
