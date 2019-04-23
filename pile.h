#ifndef PILE_H
#define PILE_H

typedef struct
{
    int from;
    int to;
}Shift;

typedef struct pile
{
    Shift movement;
    struct pile *previous;
} pile;

void Push(pile **, Shift);
Shift Pop(pile **);
Shift Peek(pile *);
void Clear(pile **);
int Length(pile *);
void View(pile *);
int InList(pile *, Shift);
int EqualMoves(Shift,Shift);
pile *Remove(pile*,Shift);

#endif // PILE_H



