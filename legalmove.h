#ifndef LEGALMOVE_H
#define LEGALMOVE_H

#include "attack.h"
#include "stack.h"

enum Color {WHITE, BLACK, ALL};
enum Piece {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE};

typedef struct
{
    /* pieces */
    BBoard ModelPiece[2][6];
    /* sides */
    BBoard ModelSide[3];

}Model;
/*
extern Model ChessBoard;
extern Stack *MoveList;*/

Model ChessBoard;
Stack *MoveList;
BBoard empty_board;

int SquareAttacked(enum Square, enum Color);
int KingIsChecked(enum Color);
BBoard HeadAttacks(Model, enum Color, enum Square, BBoard(*)(BBoard, enum Square));

int GetPiece(int, int);
int GetSide(int);
void MakeMove(int, int);
void Capture(int, int);
void UpdateModel(Model *);

Stack* PseudoLegalMoves(enum Color);
Stack* LegalMoves(int);

#endif // LEGALMOVE_H
