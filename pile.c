#include "pile.h"
#include <stdlib.h>
#include <stdio.h>

void Push(pile **p, Shift m)
{
        pile *element = malloc(sizeof(pile));
        if(!element) exit(EXIT_FAILURE);
        element->movement = m;
        element->previous = *p;
        *p = element;
}

Shift Pop(pile **p)
{
        Shift m;
        m.from = -1;
        m.to = -1;
        pile *tmp;
        if(!*p) return m;
        tmp = (*p)->previous;
        m = (*p)->movement;
        free(*p);
        *p = tmp;
        return m;
}

Shift Peek(pile *p)
{
        Shift m;
        m.from = -1;
        m.to = -1;
        pile *tmp;
        if(!p) return m;
        m = p->movement;
        return m;
}

void Clear(pile **p)
{
        pile *tmp;
        while(*p)
          {
             tmp = (*p)->previous;
             free(*p);
             *p = tmp;
          }
}

int Length(pile *p)
{
        int n=0;
        while(p)
          {
              n++;
              p = p->previous;
          }
        return n;
}

void View(pile *p)
{
        while(p)
          {
             printf("%d -> %d\n",p->movement.from, p->movement.to);
             p = p->previous;
          }
}

int InList(pile *p, Shift m)
{
    int result = 0;
    while(p && !result)
    {
        if(p->movement.from == m.from && p->movement.to == m.to) result = 1;
        p = p->previous;
    }
    return result;
}

int EqualMoves(Shift m, Shift n)
{
 return m.from == n.from && m.to == n.to;
}

pile *Remove(pile* first, Shift m)
{
    pile *node, *prev;
    if (first != NULL)
    {
        if (EqualMoves(first->movement,m))
        {
            node = first;
            first = first->previous;
            free(node);
        }
        else
        {
            prev = first;
            node = first->previous;
            while (node != NULL)
            {
                if (EqualMoves(node->movement,m))
                    {
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
