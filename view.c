#include "view.h"

void init_PieceView(char *view_piece)
{
    char view[7] = {'P', 'N', 'B', 'R', 'Q', 'K','.'};
    int i;
    for(i=0; i < 7; i++)
    {
        view_piece[i] = view[i];
    }
}

void BitboardToString(Bitboard board, enum Piece piece,char *stringBoard, enum Color side)
{
        Bitboard temp = board;
        int first ;
        while(temp)
        {
            first = __builtin_ctzll(temp);
            if (side) stringBoard[first] = tolower(PieceView[piece]);
            else  stringBoard[first] = toupper(PieceView[piece]);
            ClearBit(&temp,__builtin_ctzll(temp));
        }
}

void print_ChessBoard(Model board)
{
    int i, j;
    for(i = 0; i < 6; i++)
    {
        for(j = 1; j >=0; j--)
        {
            BitboardToString(board.ModelPiece[j][i],i,BoardView,j);
        }
    }
    BitboardToString(~board.ModelSide[ALL],NONE,BoardView,ALL);
    printf("\t    a b c d e f g h\n");
    printf("\t   _________________\n");
    printf("\t  |                 |\n");
    int octet = SIZE_BOARD-8;
    int bit = 0;
    while(octet>=0)
    {
        printf("\t%d | ",(int)octet/8+1);
        for(bit = octet; bit < octet+8; bit++)
        {
            printf("%c ",BoardView[bit]);
        }
        printf("| %d\n",(int)octet/8+1);
        octet-=8;
    }
    printf("\t  |_________________|\n");
    printf("\t    a b c d e f g h\n");
}

void Print_History()
{
    int i = 0;
    int j = 0;
    puts("----------------------------------\n");
    puts("       Historique des coups : \n");
    puts("----------------------------------\n");
    char *hit;
    while(i < 10)
    {
       // if(strcmp(History[i],"list"))
//        printf("[%s]-",History[i]);
        i++;
        /*puts("[");
        while(j < 4)
        {
            printf("%c\n",hit[j]);
            //hit[j] = history[i][j];
            printf("[%c",hit[j]);
        }*/
//        puts("]-");
    }

    puts("\n----------------------------------");
}
