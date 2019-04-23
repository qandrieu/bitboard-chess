#include "attack.h"

/*--------------------------------------------------------------
                        ATTACK.C
----------------------------------------------------------------*/

void init_RayAttacksTable(Bitboard RayAttack[][8], Bitboard *Position, uint8_t size_board)
{

    int square;

    for(square = 0; square < size_board; square++){

        RayAttack[square][EAST]=0;
        RayAttack[square][WEST]=0;
        RayAttack[square][NORTH]=0;
        RayAttack[square][SOUTH]=0;
        RayAttack[square][NORTHEAST]=0;
        RayAttack[square][NORTHWEST]=0;
        RayAttack[square][SOUTHEAST]=0;
        RayAttack[square][SOUTHWEST]=0;

        int i;
        for(i = 1;i < FILE_MAX-FileOf(square);i++){
            RayAttack[square][NORTHEAST] |= (uint64_t)Position[square] << 9*i;
            RayAttack[square][SOUTHEAST] |= (uint64_t)Position[square] >> 7*i;
            RayAttack[square][EAST] |= (uint64_t)Position[square] << i;
        }

        for(i = FileOf(square); i > 0; i--){
            RayAttack[square][NORTHWEST] |= (uint64_t)Position[square] << 7*i;
            RayAttack[square][SOUTHWEST] |= (uint64_t)Position[square] >> 9*i;
            RayAttack[square][WEST] |= (uint64_t)Position[square] >> i;
        }
         for(i = 1; i < 8; i++){
            RayAttack[square][NORTH] |= (uint64_t)Position[square] << 8*i;
            RayAttack[square][SOUTH] |= (uint64_t)Position[square] >> 8*i;
        }
    }
}

Bitboard PositiveAttacks(Bitboard occupied, enum Compass direction, enum Square square)
{
   Bitboard attacks = RayAttacksTable[square][direction];
   Bitboard blocks = attacks & occupied;
   if (blocks)
   {
      square = __builtin_ctzll(blocks);
      attacks ^= RayAttacksTable[square][direction];
   }
   return attacks;
}
Bitboard NegativeAttacks(Bitboard occupied, enum Compass direction, enum Square square)
{
   Bitboard attacks = RayAttacksTable[square][direction];
   Bitboard blocks = attacks & occupied;
   if (blocks)
   {
      square = __builtin_ctzll(MS1B(blocks));
      attacks ^= RayAttacksTable[square][direction];
   }
   return attacks;
}

Bitboard RankAttacks(Bitboard occupied, enum Square square)
{
    return PositiveAttacks(occupied, EAST, square) | NegativeAttacks(occupied, WEST, square);
}

Bitboard FileAttacks(Bitboard occupied, enum Square square)
{
    return PositiveAttacks(occupied, NORTH, square) | NegativeAttacks(occupied, SOUTH, square);
}

Bitboard DiagonalAttacks(Bitboard occupied, enum Square square)
{
    return PositiveAttacks(occupied, NORTHEAST, square) | NegativeAttacks(occupied, SOUTHWEST, square);
}

Bitboard AntiDiagonalAttacks(Bitboard occupied, enum Square square)
{
   return PositiveAttacks(occupied, NORTHWEST, square) | NegativeAttacks(occupied, SOUTHEAST, square);
}

Bitboard RookAttack(Bitboard occupied, enum Square square)
{
    return RankAttacks(occupied, square) | FileAttacks(occupied, square);
}

Bitboard BishopAttack(Bitboard occupied, enum Square square)
{
    return DiagonalAttacks(occupied, square) | AntiDiagonalAttacks(occupied, square);
}

Bitboard QueenAttack(Bitboard occupied, enum Square square)
{
    return RookAttack(occupied, square) | BishopAttack(occupied, square);
}

void init_KingAttacksTable(MaskTable Table, Bitboard* position, Bitboard *KingMove)
{
    Bitboard movable_east, movable_west;
    int i;
    for(i = 0; i < SIZE_BOARD; i++)
    {
        movable_east = position[i] & ~Table.MaskFile[FILE_H];
        movable_west = position[i] & ~Table.MaskFile[FILE_A];

        KingMove[i] = position[i] << 8 | position[i] >> 8
                    | movable_east << 1 | movable_west >> 1
                    | movable_east << 9 | movable_west >> 9
                    | movable_east >> 7 | movable_west << 7;
    }
}

Bitboard KingAttack(Bitboard occupied, enum Square square)
{
    return KingAttacksTable[square];
}

void init_KnightAttacksTable(MaskTable Table, Bitboard* position, Bitboard *KnightMove)
{
    Bitboard movable_east, movable_west, movable_deep_east, movable_deep_west;
    int i;
    for(i = 0; i < SIZE_BOARD; i++)
    {
        movable_east = position[i] & (~Table.MaskFile[FILE_H]);
        movable_west = position[i] & (~Table.MaskFile[FILE_A]);
        movable_deep_east = movable_east & (~Table.MaskFile[FILE_G]);
        movable_deep_west = movable_west & (~Table.MaskFile[FILE_B]);

        KnightMove[i] = movable_east >> SSE_NNW | movable_west << SSE_NNW |
                        movable_east << SSW_NNE | movable_west >> SSW_NNE |
                        movable_deep_east << WSW_ENE | movable_deep_west >> WSW_ENE |
                        movable_deep_west << ESE_WNW | movable_deep_east >> ESE_WNW;
    }
}

Bitboard KnightAttack(Bitboard occupied, enum Square square)
{
    return KnightAttacksTable[square];
}

Bitboard WhitePawnsAttack(Bitboard position, Bitboard all, Bitboard all_black, MaskTable TableBase)
{
    Bitboard simple_move = (position << 8);
    Bitboard double_move = ((simple_move & TableBase.MaskRank[RANK_3]) << 8);
    Bitboard moves = (simple_move | double_move) & ~all;

    Bitboard taking_right = (position & ~TableBase.MaskFile[FILE_H]) << 9;
    Bitboard taking_left = (position & ~TableBase.MaskFile[FILE_A]) << 7;
    Bitboard taking = (taking_left | taking_right) & all_black;

    return moves | taking;
}

Bitboard BlackPawnsAttack(Bitboard position, Bitboard all, Bitboard all_white, MaskTable TableBase)
{
    Bitboard simple_move = (position >> 8);
    Bitboard double_move = ((simple_move & TableBase.MaskRank[RANK_6]) >> 8);
    Bitboard moves = (simple_move | double_move) & ~all;

    Bitboard taking_right = (position & ~TableBase.MaskFile[FILE_H]) >> 7;
    Bitboard taking_left = (position & ~TableBase.MaskFile[FILE_A]) >> 9;
    Bitboard taking = (taking_left | taking_right) & all_white;

    return moves | taking;
}
