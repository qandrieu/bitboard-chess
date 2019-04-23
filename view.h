#ifndef VIEW_H
#define VIEW_H

#include <ctype.h>
#include "legalmove.h"

char BoardView[SIZE_BOARD];
char PieceView[7];

void init_PieceView(char *);
void BitboardToString(Bitboard, enum Piece, char*, enum Color);
void print_ChessBoard(Model);
void Print_History();

#endif // VIEW_H
