#include <cstdio>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <cstring>
#include <cmath>
#include <mutex>

#include "matrix.h"

#define MATRIX_SIZE 11
#define THREAD_SIZE 8
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




Matrix globalMatrix;

std::mutex mutex;
long long taskResult = 0;


void threadFunc(int length,int* row,int* col){
    for(int i = 0;i < length; i++){
        Matrix* minor = getMinor(&globalMatrix,row[i],col[i]);
        long long calc = globalMatrix.array[row[i]][0] * calcDeterminant(minor);
        destroy(minor);
        free(minor);
        if (row[i] % 2 == 1){
            calc *= -1;
        }
        mutex.lock();
        taskResult += calc;
        mutex.unlock();
    }
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
    Matrix matrix;
    init(&matrix,MATRIX_SIZE);
    init(&globalMatrix,MATRIX_SIZE);
    //fillRandomNumbers(&matrix,MAX_MATRIX_VALUE);
    readData(&matrix);
    copy(&matrix,&globalMatrix);

    std::thread threads[THREAD_SIZE];

    int* linesPerThread = splitLinesForThreading(MATRIX_SIZE,THREAD_SIZE);

    clock_t timeBegin = clock();
    int curLine = 0;

    for(int i = 0;i < THREAD_SIZE; i++){
        int linesCount = linesPerThread[i];

        int* row = new int[linesCount];
        int* col = new int[linesCount];

        for(int j = 0;j < linesCount; j++){
            row[j] = curLine;
            col[j] = 0;
            curLine++;
        }

        threads[i] = std::thread(threadFunc,linesCount,row,col);
    }

    free(linesPerThread);

    for(auto & thread : threads){
        thread.join();
    }

    printf("Parallel %lld\n",taskResult);

    clock_t timeEnd = clock();
    double timeSpent = (double)(timeEnd - timeBegin) / CLOCKS_PER_SEC;

    printf("time is %lf\n",timeSpent);

    destroy(&matrix);
    destroy(&globalMatrix);
    return 0;
}
