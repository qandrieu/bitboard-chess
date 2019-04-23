#ifndef ATTACK_H
#define ATTACK_H

#include "bboard.h"

/*--------------------------------------------------------------
                        ATTACK.H
----------------------------------------------------------------*/

/* Index of each square on the chessboard. {a1 = 0, b1 = 1, ... h8 = 63} */
enum Square {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};

/*  The compass gives the direction of moves. E : East, W : West, N : North, S : South.
    For example, "SSE_NNW" refers the axis SouthSouthEast-NorthNorthWest */
enum Compass{EAST, NORTHEAST, NORTH, NORTHWEST, WEST, SOUTHWEST, SOUTH, SOUTHEAST};
enum KnightCompass{ESE_WNW = 6, WSW_ENE = 10, SSE_NNW = 15, SSW_NNE = 17};

Bitboard PositionTable[SIZE_BOARD];
Bitboard RayAttacksTable[SIZE_BOARD][8];
Bitboard KingAttacksTable[SIZE_BOARD];
Bitboard KnightAttacksTable[SIZE_BOARD];
MaskTable Mask;

void init_RayAttacksTable(Bitboard [][8], Bitboard*, uint8_t);
void init_KingAttacksTable(MaskTable, Bitboard*, Bitboard *);
void init_KnightAttacksTable(MaskTable, Bitboard*, Bitboard *);

Bitboard PositiveAttacks(Bitboard, enum Compass, enum Square);
Bitboard NegativeAttacks(Bitboard, enum Compass, enum Square);
Bitboard RankAttacks(Bitboard, enum Square);
Bitboard FileAttacks(Bitboard, enum Square);
Bitboard DiagonalAttacks(Bitboard, enum Square);
Bitboard AntiDiagonalAttacks(Bitboard, enum Square);

Bitboard PawnAttack(Bitboard, enum Square);
Bitboard KnightAttack(Bitboard, enum Square);
Bitboard BishopAttack(Bitboard, enum Square);
Bitboard RookAttack(Bitboard, enum Square);
Bitboard QueenAttack(Bitboard, enum Square);
Bitboard KingAttack(Bitboard, enum Square);
Bitboard ErrorAttack(Bitboard, enum Square);
Bitboard WhitePawnsAttack(Bitboard, Bitboard, Bitboard, MaskTable);
Bitboard BlackPawnsAttack(Bitboard, Bitboard, Bitboard, MaskTable);

#endif // ATTACK_H
