#include "bboard.h"

void clear_bit(BBoard *value, int _rank)
{
    *value &= ~((BBoard) 1 << _rank);
}

void set_bit(BBoard *value, int _rank)
{
    *value |= ((BBoard) 1 << _rank);
}

int get_bit(BBoard *value, int _rank)
{
    return *value & ((BBoard) 1 << _rank) ? 1 : 0;
}

void inverse_bit(BBoard *value, int _rank)
{
    *value ^=((BBoard) 1 << _rank);
}

int is_power_of_two(BBoard x)
{
    return x != 0 && (x&(x-1)) == 0 ? 1 : 0;
}

int file_of(int square)
{
    return square & 7;
}

int rank_of(int square)
{
    return square >> 3;
}

BBoard ls1b(BBoard b)
{
    return b & -b;
}

BBoard ms1b(BBoard b)
{
    b |= b >> 32;
    b |= b >> 16;
    b |= b >>  8;
    b |= b >>  4;
    b |= b >>  2;
    b |= b >>  1;
    return  (b >> 1) + 1;
}

Masks init_masks()
{
    Masks masks;
    masks.files[A] = 0x101010101010101;
    masks.ranks[ONE] = 0xFF;
    for(int i = 1; i < BOARD_SIZE; i++) {
        masks.files[A+i] = masks.files[A] << i;
        masks.ranks[ONE+i] = masks.ranks[ONE] << i*8;
    }
    return masks;
}

void init_pos_table(BBoard* b, int size)
{
    for(int i=0; i<size; i++)
        b[i] = (BBoard)1 << i;
}
