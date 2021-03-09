//
// Created by rugewit on 06.03.2021.
//

#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H


struct Matrix_ {
    int** array;
    int n;
};

typedef struct Matrix_ Matrix;

void init(Matrix* matrix, int n);
void checkBorders(Matrix* matrix,int i,int j);
int getElement(Matrix* matrix,int i,int j);
void setElement(Matrix* matrix,int i,int j,int el);
void fillRandomNumbers(Matrix* matrix,int maxInt);
void print(Matrix* matrix);
void destroy(Matrix* matrix);
void copy(Matrix* src, Matrix* dest);


void init(Matrix* matrix, int n) {
    matrix->n = n;
    matrix->array = (int**) calloc(sizeof (int*),n);
    for(int i = 0;i < n;i++){
        matrix->array[i] = (int*) calloc(sizeof (int),n);
    }
}

void checkBorders(Matrix* matrix,int i,int j){
    bool cond1 = i < 0 || i > (matrix->n - 1);
    bool cond2 = j < 0 || j > (matrix->n - 1);
    if (cond1 || cond2){
        perror("out of range");
    }
}

int getElement(Matrix* matrix,int i,int j) {
    checkBorders(matrix,i,j);
    return matrix->array[i][j];
}

void setElement(Matrix* matrix,int i,int j,int el) {
    checkBorders(matrix,i,j);
    matrix->array[i][j] = el;
}

void fillRandomNumbers(Matrix* matrix,int maxInt){
    for(int i = 0;i < matrix->n; i++){
        for(int j = 0;j < matrix->n; j++){
            setElement(matrix,i,j,rand() % (maxInt + 1));
        }
    }
}

void print(Matrix* matrix){
    for(int i = 0; i < matrix->n; i++){
        for(int j = 0;j < matrix->n; j++){
            printf("%d ",getElement(matrix,i,j));
        }
        putchar('\n');
    }
}

void destroy(Matrix* matrix){
    for(int i = 0; i < matrix->n; i++){
        free(matrix->array[i]);
    }
    free(matrix->array);
}

void copy(Matrix* src, Matrix* dest){
    for(int i = 0;i < src->n; i++){
        for(int j = 0;j < src->n; j++){
            dest->array[i][j] = src->array[i][j];
        }
    }
}

#endif //LAB3_MATRIX_H
