#include <stdio.h>
#include <stdlib.h>

struct Heap {
  int size;
  int apparentSize;
  int *data;
};

int parent(int i){
  return i/2;
}

int left(int i){
  return 2*i;
}

int right(int i){
  return (2*i)+1;
}

void maxHeapify(struct Heap *heap, int i){
  int L = left(i);
  int R = right(i);
  int largest;
  if (L < heap->apparentSize && heap->data[L] > heap->data[i]){
    largest = L;
  } else {
    largest = i;
  }
  if (R < heap->apparentSize && heap->data[R] > heap->data[largest]){
    largest = R;
  }
  if (largest != i){
    int tempI = heap->data[i];
    heap->data[i] = heap->data[largest];
    heap->data[largest] = tempI;
    maxHeapify(heap, largest);
  }
}

struct Heap *buildMaxHeap(int *data, int size){
  struct Heap *ret = calloc(1, sizeof(struct Heap));
  ret->size = size;
  ret->apparentSize = size;
  ret->data = data;

  //heapify the data
  int i = ret->size/2;
  for (i; i >= 0; --i){
    maxHeapify(ret, i);
  }
  return ret;
}

void heapsort(struct Heap *h){
  int i = h->size-1;
  for (i; i>=1; --i){
    int tempI = h->data[i];
    h->data[i] = h->data[0];
    h->data[0] = tempI;
    h->apparentSize -= 1;
    maxHeapify(h, 0);
  }
  h->apparentSize = h->size;
}

void printHeap(struct Heap *heap){
  int i = 0;
  for (i; i < heap->size; ++i) printf("%d ", heap->data[i]);
  printf("\n");
}

int main(){
  //test data set
  int data[] = {1,4,5,2,3,7,9,9,100,21,233,9,9,8,6};
  
  int size = sizeof(data)/sizeof(int);
  struct Heap *h = buildMaxHeap(data, size);
  printHeap(h);
  heapsort(h);
  printHeap(h);
}
