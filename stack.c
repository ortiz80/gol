#include <stdlib.h>
#include "stack.h"

typedef struct node
{
  void * info;
  struct node *next;
} Node;

typedef Node * List; 

struct stack
{
  List contents;
  int size;
};


Stack init_stack()
{
  Stack s;
  s = malloc(sizeof(struct stack));
  s->contents = NULL;
  s->size = 0;
  return s;
}

int stack_empty(Stack s)
{
  return s->contents == NULL;
}

void push(Stack s, void * elem)
{
  List temp;
  
  temp = malloc(sizeof(Node));
  temp->info = elem;
  temp->next = s->contents;
  s->contents = temp;
  (s->size)++;
}

void * pop(Stack s)
{
  void * ris;
  List temp;

  temp = (s->contents);
  s->contents = temp->next;
  ris = temp->info;
  free(temp);
  (s->size)--;
  return ris;
}

void * top(Stack s)
{
  return s->contents->info;
}

int size(Stack s){
  return s->size;
}