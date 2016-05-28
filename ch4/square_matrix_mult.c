#include <stdlib.h>
#include <stdio.h>

struct Matrix {
  int rows;
  int columns;
  int *data;
};

/**
 * makes a new square matrix and returns it
 */
struct Matrix *newSquareMatrix(int size, int *data){
  struct Matrix *m = calloc(1, sizeof(struct Matrix));
  m->rows = size;
  m->columns = size;
  m->data = data;
  return m;
}

/**
 * multiply two square matrices together
 */
struct Matrix *squareMatMult(struct Matrix *m1, struct Matrix *m2){
  int size = m1-> rows;
  //make a new square matrix of same size with 0 data
  struct Matrix *ret = newSquareMatrix(size, calloc(size*size, sizeof(int)));

  int i, j, k;
  for (i=0; i<size; ++i){
    for (j=0; j<size; ++j){
      for (k=0; k<size; ++k){
        int retIndex = ((i*size)+j);
        int m1Index = ((i*size)+k);
        int m2Index = ((k*size)+j);
        ret->data[retIndex] += m1->data[m1Index]*m2->data[m2Index];
      }
    }
  }
  return ret;
}

/**
 * pretty prints a matrix
 */
void printMatrix(struct Matrix *m){
  int rows = m->rows;
  int columns = m->columns;
  int i, j;
  for (i=0; i < (m->rows); ++i){
    printf("[ ");
    for (j=0; j < (m->columns); ++j){
      printf("%d ", m->data[(i*rows)+j]);
    }
    printf("]\n");
  }
  printf("\n");
}

int main(){
  //declare data
  int d1[] = {0,1,2,3};
  int d2[] = {2,2,3,3};
  //declare matrices we will be multiplying
  struct Matrix *m1 = newSquareMatrix(2, d1);
  struct Matrix *m2 = newSquareMatrix(2, d2);
  struct Matrix *m3 = squareMatMult(m2, m1);
  printMatrix(m3);
}
