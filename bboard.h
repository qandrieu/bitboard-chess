#ifndef B_BOARD_H
#define B_BOARD_H

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

/* BBoard is an alias for "uint64_t" (unsigned integer exactly equal to 8*8-bit) */
typedef uint64_t BBoard;
/* The files of the board : A B C D E F G H */
enum File {A, B, C, D, E, F, G, H};
/* The ranks of the Board : 1 2 3 4 5 6 7 8 */
enum Rank {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT};
/*
Table of Masks. For example, ranks[FOUR] is a BBoard
with all the bits set on line number 4, and clear elsewhere
*/
typedef struct{

	BBoard ranks[BOARD_SIZE];
	BBoard files[BOARD_SIZE];

} Masks;

void clear_bit(BBoard *, int);
void set_bit(BBoard*, int);
int get_bit(BBoard*, int);
void inverse_bit(BBoard *, int);
int is_power_of_two(BBoard);
int file_of(int);
int file_of(int);
int rank_of(int);

BBoard ls1b(BBoard);
BBoard ms1b(BBoard);

Masks init_masks();
void init_pos_table(BBoard*, int);

#endif // B_BOARD_H