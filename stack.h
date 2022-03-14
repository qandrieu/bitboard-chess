#ifndef Stack_H
#define Stack_H

typedef struct
{
    int from;
    int to;
} Shift;

typedef struct Stack
{
    Shift movement;
    struct Stack *previous;
} Stack;

void push(Stack **, Shift);
Shift pop(Stack **);
Shift peek(Stack *);
void clear(Stack **);
int length(Stack *);
void view(Stack *);
int contains(Stack *, Shift);
int equals(Shift, Shift);
Stack *rm(Stack*, Shift);

#endif // Stack_H
