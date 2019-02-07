typedef struct stack * Stack;

Stack init_stack();
int stack_empty(Stack s);
void push(Stack s, void * elem);
void * pop(Stack s);
void * top(Stack s);
int size(Stack s);