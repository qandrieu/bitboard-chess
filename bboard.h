#ifndef BBOARD_H
#define BBOARD_H

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define RANK_MAX 8
#define FILE_MAX 8
#define SIZE_BOARD 64

/* BitBoard is an alias for "uint64_t" (unsigned integer exactly equal to 8*8-bit) */
typedef uint64_t Bitboard;
/* The files of the board : {A, B, C, D E F G H} */
enum File {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
/* The ranks of the Board : 1 2 3 4 5 6 7 8 */
enum Rank {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};
/*
Table of Masks. For example, MaskRank[Rank_4] is a bitboard
with all the bits set on line number 4, and clear elsewhere
*/
typedef struct{

	/* Masks Ranks (or files) */
	Bitboard MaskRank[RANK_MAX];
	Bitboard MaskFile[FILE_MAX];

}MaskTable;

void ClearBit(Bitboard *, int);
void SetBit(Bitboard* , int);
void InverseBit(Bitboard * , int);
int TestBit(Bitboard, int);
int IsPow2(Bitboard);
int FileOf(int);
int RankOf(int);

Bitboard LS1B(Bitboard);
Bitboard MS1B(Bitboard);
int Population(Bitboard);

MaskTable init_Table();
void init_PositionTable(Bitboard*, int);
void print_Bitboard(Bitboard);

#endif // BBOARD_H
