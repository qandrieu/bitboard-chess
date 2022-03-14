#include "attack.h"

/*--------------------------------------------------------------
                        ATTACK.C
----------------------------------------------------------------*/

void init_RayAttacksTable(BBoard RayAttack[][8], BBoard *Position, uint8_t size_board)
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
        for(i = 1;i < BOARD_SIZE - file_of(square);i++){
            RayAttack[square][NORTHEAST] |= (uint64_t)Position[square] << 9*i;
            RayAttack[square][SOUTHEAST] |= (uint64_t)Position[square] >> 7*i;
            RayAttack[square][EAST] |= (uint64_t)Position[square] << i;
        }

        for(i = file_of(square); i > 0; i--){
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

BBoard PositiveAttacks(BBoard occupied, enum Compass direction, enum Square square)
{
   BBoard attacks = RayAttacksTable[square][direction];
   BBoard blocks = attacks & occupied;
   if (blocks)
   {
      square = __builtin_ctzll(blocks);
      attacks ^= RayAttacksTable[square][direction];
   }
   return attacks;
}
BBoard NegativeAttacks(BBoard occupied, enum Compass direction, enum Square square)
{
   BBoard attacks = RayAttacksTable[square][direction];
   BBoard blocks = attacks & occupied;
   if (blocks)
   {
      square = __builtin_ctzll(ms1b(blocks));
      attacks ^= RayAttacksTable[square][direction];
   }
   return attacks;
}

BBoard RankAttacks(BBoard occupied, enum Square square)
{
    return PositiveAttacks(occupied, EAST, square) | NegativeAttacks(occupied, WEST, square);
}

BBoard FileAttacks(BBoard occupied, enum Square square)
{
    return PositiveAttacks(occupied, NORTH, square) | NegativeAttacks(occupied, SOUTH, square);
}

BBoard DiagonalAttacks(BBoard occupied, enum Square square)
{
    return PositiveAttacks(occupied, NORTHEAST, square) | NegativeAttacks(occupied, SOUTHWEST, square);
}

BBoard AntiDiagonalAttacks(BBoard occupied, enum Square square)
{
   return PositiveAttacks(occupied, NORTHWEST, square) | NegativeAttacks(occupied, SOUTHEAST, square);
}

BBoard RookAttack(BBoard occupied, enum Square square)
{
    return RankAttacks(occupied, square) | FileAttacks(occupied, square);
}

BBoard BishopAttack(BBoard occupied, enum Square square)
{
    return DiagonalAttacks(occupied, square) | AntiDiagonalAttacks(occupied, square);
}

BBoard QueenAttack(BBoard occupied, enum Square square)
{
    return RookAttack(occupied, square) | BishopAttack(occupied, square);
}

void init_KingAttacksTable(Masks Table, BBoard* position, BBoard *KingMove)
{
    BBoard movable_east, movable_west;
    int i;
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        movable_east = position[i] & ~Table.files[H];
        movable_west = position[i] & ~Table.files[A];

        KingMove[i] = position[i] << 8 | position[i] >> 8
                    | movable_east << 1 | movable_west >> 1
                    | movable_east << 9 | movable_west >> 9
                    | movable_east >> 7 | movable_west << 7;
    }
}

BBoard KingAttack(BBoard occupied, enum Square square)
{
    return KingAttacksTable[square];
}

void init_KnightAttacksTable(Masks Table, BBoard* position, BBoard *KnightMove)
{
    BBoard movable_east, movable_west, movable_deep_east, movable_deep_west;
    int i;
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        movable_east = position[i] & (~Table.files[H]);
        movable_west = position[i] & (~Table.files[A]);
        movable_deep_east = movable_east & (~Table.files[G]);
        movable_deep_west = movable_west & (~Table.files[B]);

        KnightMove[i] = movable_east >> SSE_NNW | movable_west << SSE_NNW |
                        movable_east << SSW_NNE | movable_west >> SSW_NNE |
                        movable_deep_east << WSW_ENE | movable_deep_west >> WSW_ENE |
                        movable_deep_west << ESE_WNW | movable_deep_east >> ESE_WNW;
    }
}

BBoard KnightAttack(BBoard occupied, enum Square square)
{
    return KnightAttacksTable[square];
}

BBoard WhitePawnsAttack(BBoard position, BBoard all, BBoard all_black, Masks TableBase)
{
    BBoard simple_move = (position << 8);
    BBoard double_move = ((simple_move & TableBase.ranks[THREE]) << 8);
    BBoard moves = (simple_move | double_move) & ~all;

    BBoard taking_right = (position & ~TableBase.files[H]) << 9;
    BBoard taking_left = (position & ~TableBase.files[A]) << 7;
    BBoard taking = (taking_left | taking_right) & all_black;

    return moves | taking;
}

BBoard BlackPawnsAttack(BBoard position, BBoard all, BBoard all_white, Masks TableBase)
{
    BBoard simple_move = (position >> 8);
    BBoard double_move = ((simple_move & TableBase.ranks[SIX]) >> 8);
    BBoard moves = (simple_move | double_move) & ~all;

    BBoard taking_right = (position & ~TableBase.files[H]) >> 7;
    BBoard taking_left = (position & ~TableBase.files[A]) >> 9;
    BBoard taking = (taking_left | taking_right) & all_white;

    return moves | taking;
}
