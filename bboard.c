#include "bboard.h"

/*----------------------------------------
            bboard.c
----------------------------------------*/

void ClearBit(Bitboard *value, int _rank)
{
    *value &= ~((Bitboard) 1 << _rank);
}

void SetBit(Bitboard *value, int _rank)
{
    *value |= ((Bitboard) 1 << _rank);
}

int GetBit(Bitboard value, int _rank)
{
    if(value & ((Bitboard) 1 << _rank)){
        return 1;
    }
    else {
      return 0;
    }
}

void InverseBit(Bitboard *value, int _rank)
{
    *value ^=((Bitboard) 1 << _rank);
}

int IsPow2(Bitboard x)
{
    if(x != 0 && (x&(x-1)) == 0) return 1;
    else return 0;
}

/*------------------------------------------------*/

int FileOf(int square){return square & 7;}
int RankOf(int square){return square >> 3;}
Bitboard LS1B(Bitboard b){return b & -b;}
Bitboard MS1B(Bitboard b)
{
    b |= b >> 32;
    b |= b >> 16;
    b |= b >>  8;
    b |= b >>  4;
    b |= b >>  2;
    b |= b >>  1;
    return  (b >> 1) + 1;
}

int Population(Bitboard b)
{
    int rank;
    int count = 0;

    while(b)
    {
        rank = __builtin_ctzll(b);
        ClearBit(&b,rank);
        count++;
    }
    return count;
}

MaskTable init_Table()
{
    MaskTable Table;
    Table.MaskFile[FILE_A] = 0x101010101010101;
    Table.MaskRank[RANK_1] = 0xFF;
    int i;
    for(i = 1; i < FILE_MAX; i++){
            Table.MaskFile[FILE_A+i] = Table.MaskFile[FILE_A] << i;
            Table.MaskRank[RANK_1+i] = Table.MaskRank[RANK_1] << i*8;
        }
    return Table;
}

void init_PositionTable(Bitboard* table, int size_Position){

    int i;
    for(i=0;i<size_Position;i++)table[i] = (Bitboard)1 << i;
}

void print_Bitboard(Bitboard board)
{
        printf("\n/*--AFFICHAGE BITBOARD--*/\n\n");
        printf("      a b c d e f g h\n");
        printf("     _________________\n");
        printf("    |                 |\n");
        int octet = SIZE_BOARD-8;
        int bit = 0;
        while(octet>=0){
            printf("  %d | ",(int)octet/8+1);
            for(bit = octet; bit < octet+8; bit++){

                if(!GetBit(board, bit)) printf(". ");
                else printf("1 ");
            }
            printf("| %d\n",(int)octet/8+1);
            octet-=8;
        }
        printf("    |_________________|\n");
        printf("                       \n");
	printf("      a b c d e f g h\n");
}
