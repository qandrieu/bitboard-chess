#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void push(Stack **p, Shift m)
{
    Stack *element = malloc(sizeof(Stack));
    if(!element) exit(EXIT_FAILURE);
    element->movement = m;
    element->previous = *p;
    *p = element;
}

Shift pop(Stack **p)
{
    Shift m;
    m.from = -1;
    m.to = -1;
    Stack *tmp;
    if(!*p) return m;
    tmp = (*p)->previous;
    m = (*p)->movement;
    free(*p);
    *p = tmp;
    return m;
}

Shift peek(Stack *p)
{
    Shift m;
    m.from = -1;
    m.to = -1;
    Stack *tmp;
    if(!p) return m;
    m = p->movement;
    return m;
}

void clear(Stack **p)
{
    Stack *tmp;
    while(*p) {
        tmp = (*p)->previous;
        free(*p);
        *p = tmp;
    }
}

int length(Stack *p)
{
    int n=0;
    while(p) {
        n++;
        p = p->previous;
    }
    return n;
}

void view(Stack *p)
{
    while(p) {
        printf("%d -> %d\n",p->movement.from, p->movement.to);
        p = p->previous;
    }
}

int contains(Stack *p, Shift m)
{
    int result = 0;
    while(p && !result) {
        if(p->movement.from == m.from && p->movement.to == m.to) result = 1;
        p = p->previous;
    }
    return result;
}

int equals(Shift m, Shift n)
{
    return m.from == n.from && m.to == n.to;
}

Stack *rm(Stack* first, Shift m)
{
    Stack *node, *prev;
    if (first != NULL) {
        if (equals(first->movement,m)) {
            node = first;
            first = first->previous;
            free(node);
        } else {
            prev = first;
            node = first->previous;
            while (node != NULL) {
                if (equals(node->movement,m)) {
                    prev->previous = node->previous;
                    free(node);
                    break;
                }
                prev = node;
                node = node->previous;
            }
        }
    }
    return first;
}