#ifndef LEGALMOVE_H
#define LEGALMOVE_H

#include "attack.h"
#include "pile.h"

enum Color {WHITE, BLACK, ALL};
enum Piece {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE};

typedef struct
{
    /* pieces */
    Bitboard ModelPiece[2][6];
    /* sides */
    Bitboard ModelSide[3];

}Model;
/*
extern Model ChessBoard;
extern pile *MoveList;*/

Model ChessBoard;
pile *MoveList;
Bitboard empty_board;

int SquareAttacked(enum Square, enum Color);
int KingIsChecked(enum Color);
Bitboard HeadAttacks(Model, enum Color, enum Square, Bitboard(*)(Bitboard, enum Square));

int GetPiece(int, int);
int GetSide(int);
void MakeMove(int, int);
void Capture(int, int);
void UpdateModel(Model *);

pile* PseudoLegalMoves(enum Color);
pile* LegalMoves(int);

#endif // LEGALMOVE_H
