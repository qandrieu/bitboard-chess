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

BBoard PositionTable[BOARD_SIZE * BOARD_SIZE];
BBoard RayAttacksTable[BOARD_SIZE * BOARD_SIZE][8];
BBoard KingAttacksTable[BOARD_SIZE * BOARD_SIZE];
BBoard KnightAttacksTable[BOARD_SIZE * BOARD_SIZE];
Masks Mask;

void init_RayAttacksTable(BBoard [][8], BBoard*, uint8_t);
void init_KingAttacksTable(Masks, BBoard*, BBoard *);
void init_KnightAttacksTable(Masks, BBoard*, BBoard *);

BBoard PositiveAttacks(BBoard, enum Compass, enum Square);
BBoard NegativeAttacks(BBoard, enum Compass, enum Square);
BBoard RankAttacks(BBoard, enum Square);
BBoard FileAttacks(BBoard, enum Square);
BBoard DiagonalAttacks(BBoard, enum Square);
BBoard AntiDiagonalAttacks(BBoard, enum Square);

BBoard PawnAttack(BBoard, enum Square);
BBoard KnightAttack(BBoard, enum Square);
BBoard BishopAttack(BBoard, enum Square);
BBoard RookAttack(BBoard, enum Square);
BBoard QueenAttack(BBoard, enum Square);
BBoard KingAttack(BBoard, enum Square);
BBoard ErrorAttack(BBoard, enum Square);
BBoard WhitePawnsAttack(BBoard, BBoard, BBoard, Masks);
BBoard BlackPawnsAttack(BBoard, BBoard, BBoard, Masks);

#endif // ATTACK_H
