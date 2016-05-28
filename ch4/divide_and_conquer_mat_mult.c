#include <stdlib.h>
#include <stdio.h>

struct Matrix {
  int rows;
  int cols;
  int *data;
};

/**
 * makes a new square matrix and returns it
 */
struct Matrix *newSquareMatrix(int size, int *data){
  struct Matrix *m = calloc(1, sizeof(struct Matrix));
  m->rows = size;
  m->cols = size;
  m->data = data;
  return m;
}

/**
 * only multiply 2x2 matrices for now
 */
struct Matrix *recursiveMatMult(struct Matrix *m1, struct Matrix *m2){
  int size = m1->rows;
  //make a new matrix for the result
  struct Matrix *ret = newSquareMatrix(size, calloc(size*size, sizeof(int)));
  //if it's only 1x1 then just multiply and return
  if (size==1){
    ret->data[0] = m1->data[0]*m2->data[0];
    return ret;
  }
  //otherwise unroll a simple loop for 1x1 matrices
  int *d1 = m1->data;
  int *d2 = m2->data;
  ret->data[0] = recursiveMatMult(newSquareMatrix(size-1, d1), newSquareMatrix(size-1, d2))->data[0];
  ret->data[0] += recursiveMatMult(newSquareMatrix(size-1, d1+1), newSquareMatrix(size-1, d2+2))->data[0];

  ret->data[1] = recursiveMatMult(newSquareMatrix(size-1, d1), newSquareMatrix(size-1, d2+1))->data[0];
  ret->data[1] += recursiveMatMult(newSquareMatrix(size-1, d1+1), newSquareMatrix(size-1, d2+3))->data[0];

  ret->data[2] = recursiveMatMult(newSquareMatrix(size-1, d1+2), newSquareMatrix(size-1, d2))->data[0];
  ret->data[2] += recursiveMatMult(newSquareMatrix(size-1, d1+3), newSquareMatrix(size-1, d2+2))->data[0];

  ret->data[3] = recursiveMatMult(newSquareMatrix(size-1, d1+2), newSquareMatrix(size-1, d2+1))->data[0];
  ret->data[3] += recursiveMatMult(newSquareMatrix(size-1, d1+3), newSquareMatrix(size-1, d2+3))->data[0];
  return ret;
}

/**
 * pretty prints a matrix
 */
void printMatrix(struct Matrix *m){
  int rows = m->rows;
  int columns = m->cols;
  int i, j;
  for (i=0; i < (m->rows); ++i){
    printf("[ ");
    for (j=0; j < (m->cols); ++j){
      printf("%d ", m->data[(i*rows)+j]);
    }
    printf("]\n");
  }
  printf("\n");
}

int main(){
  int d1[] = {1,3,4,2};
  int d2[] = {0,3,2,2};
  struct Matrix *m1 = newSquareMatrix(2, d1);
  struct Matrix *m2 = newSquareMatrix(2, d2);
  printMatrix(recursiveMatMult(m1, m2));
}
