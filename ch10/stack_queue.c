#include <stdio.h>
#include <stdlib.h>

//we'll grow the backing array if necessary by this much
#define PARTITION_SIZE 10

struct stack {
  int size;
  int topIndex;
  int* _data;
};

struct queue {
  int size;
  int* _data;
};

struct stack* Stack(){
  struct stack* ret = calloc(1, sizeof(struct stack));
  ret->size = PARTITION_SIZE;
  ret->_data = calloc(PARTITION_SIZE, sizeof(int));
}

void stack_Push(struct stack *s, int x){
  //if the stack is full, grow the array
  if (s->topIndex+1 > s->size){
    s->size += PARTITION_SIZE;
    int* newPointer = (int *) realloc(s->_data, s->size * sizeof(int));
    if (newPointer){
      s->_data = newPointer;
    }
  }
  s->_data[s->topIndex] = x;
  s->topIndex++;
}

int stack_Pop(struct stack *s){
  if (s->topIndex-1 >= 0){
    s->topIndex--;
    return s->_data[s->topIndex];
  }
  return 0;
}

int stack_Examine(struct stack* s){
  return s->_data[s->topIndex-1];
}

struct queue* Queue(){
  struct queue* ret = calloc(1, sizeof(struct queue));
  ret->size = PARTITION_SIZE;
  ret->_data = calloc(PARTITION_SIZE, sizeof(int));
}

int main(){
  //test creation of the stack
  struct stack* s = Stack();
  //push a few numbers onto the stack
  stack_Push(s, 1);
  stack_Push(s, 4);
  stack_Push(s, 3);
  stack_Push(s, 5);
  stack_Push(s, 5);
  stack_Push(s, 2);
  stack_Push(s, 2);
  stack_Push(s, 2);
  stack_Push(s, 2);
  stack_Push(s, 2);
  stack_Push(s, 3);
  stack_Push(s, 9);
  //examine (should be 2)
  printf("%d\n", stack_Pop(s));
  printf("%d\n", stack_Examine(s));
  printf("%d\n", s->size);
  //test creation of the queue
  struct queue* q = Queue();

  free(s);
  free(q);
}
