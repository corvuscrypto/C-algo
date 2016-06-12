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
  int topIndex;
  int nextIndex;
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
  ret->nextIndex = -1;
  ret->_data = calloc(PARTITION_SIZE, sizeof(int));
}

void queue_Enqueue(struct queue *q, int x){
  //circular queue implementation with limit
  if (q->topIndex == q->nextIndex) return;
  if (q->nextIndex < 0) q->nextIndex = 0;
  q->_data[q->topIndex] = x;
  q->topIndex++;

  if (q->topIndex > q->size){
    q->topIndex = 0;
  }
}

int queue_Dequeue(struct queue *q){
  int ret = q->_data[q->nextIndex++];
  if (q->nextIndex > q->size){
    q->nextIndex = 0;
  }
  return ret;
}

int main(){
  printf("--Stack--\n");
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
  printf("%d\n", stack_Pop(s));
  printf("%d\n", stack_Examine(s));

  printf("\n--Queue--\n");
  //test creation of the queue
  struct queue* q = Queue();
  //put some stuff in that queue
  queue_Enqueue(q, 1);
  queue_Enqueue(q, 1);
  queue_Enqueue(q, 2);
  queue_Enqueue(q, 4);
  queue_Enqueue(q, 5);
  queue_Enqueue(q, 7);
  queue_Enqueue(q, 8);
  queue_Enqueue(q, 8);
  queue_Enqueue(q, 8);
  queue_Enqueue(q, 9);
  queue_Enqueue(q, 10);
  queue_Enqueue(q, 10);//should fail
  printf("%d\n", queue_Dequeue(q));//1
  queue_Enqueue(q, 11);//should work
  printf("%d\n", queue_Dequeue(q));//1
  printf("%d\n", queue_Dequeue(q));//2


  free(s);
  free(q);
}
