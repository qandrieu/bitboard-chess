#include "legalmove.h"

int SquareAttacked(enum Square square, enum Color side_attacked) {

    int side_attack = !side_attacked;

    Bitboard OtherBishopsQueens = ChessBoard.ModelPiece[side_attack][QUEEN] |
                                  ChessBoard.ModelPiece[side_attack][BISHOP];
    if (BishopAttack(ChessBoard.ModelSide[side_attacked], square) & OtherBishopsQueens) return 1;

    Bitboard OtherRooksQueens = ChessBoard.ModelPiece[side_attack][QUEEN] |
                                ChessBoard.ModelPiece[side_attack][ROOK];
    if (RookAttack(ChessBoard.ModelSide[side_attacked], square) & OtherRooksQueens) return 1;

    Bitboard OtherKnights = ChessBoard.ModelPiece[side_attack][KNIGHT];
    if (KnightAttack(empty_board,square) & OtherKnights) return 1;

    Bitboard OtherKing = ChessBoard.ModelPiece[side_attack][KING];
    if (KingAttack(empty_board,square) & OtherKing) return 1;

    Bitboard OtherPawn = ChessBoard.ModelPiece[side_attack][PAWN];
    if (side_attacked == WHITE)
    {
        if(WhitePawnsAttack(PositionTable[square],ChessBoard.ModelSide[ALL],ChessBoard.ModelSide[BLACK],Mask) &  OtherPawn) return 1;
    }
    else
    {
        if(BlackPawnsAttack(PositionTable[square],ChessBoard.ModelSide[ALL],ChessBoard.ModelSide[WHITE],Mask) & OtherPawn) return 1;
    }
    return 0;
}

int KingIsChecked(enum Color side_attacked)
{
    return SquareAttacked(__builtin_ctzll(ChessBoard.ModelPiece[side_attacked][KING]),side_attacked);
}

Bitboard HeadAttacks(Model Board, enum Color side, enum Square square, Bitboard(*Attacks)(Bitboard, enum Square))
{
    return ((*Attacks)(Board.ModelSide[ALL],square)) & ~Board.ModelSide[side];
}

pile* PseudoLegalMoves(enum Color side)
{
    int type_piece, from, to;
    Bitboard piece, attacks;
    Shift moves;
    /*
	/Warning
	*/	

    Bitboard (*ListAttacks[5])(Bitboard,enum Square)= {KnightAttack,BishopAttack,RookAttack,QueenAttack,KingAttack};
    pile* move_list = NULL;

    for (type_piece = 0; type_piece < 6; type_piece++)
    {
        piece = ChessBoard.ModelPiece[side][type_piece];
        while(piece)
        {
            from = __builtin_ctzll(piece);
            moves.from = from;
            ClearBit(&piece,from);
            if (type_piece == 0)
            {
                if (side == WHITE)
                {
                    attacks = WhitePawnsAttack(PositionTable[from],ChessBoard.ModelSide[ALL], ChessBoard.ModelSide[BLACK],Mask);
                }
                else
                {
                    attacks = BlackPawnsAttack(PositionTable[from],ChessBoard.ModelSide[ALL],ChessBoard.ModelSide[WHITE],Mask);
                }
            }
            else
            {
                attacks = HeadAttacks(ChessBoard,side,from,ListAttacks[type_piece-1]);
            }
            while(attacks)
            {
                to = __builtin_ctzll(attacks);
                moves.to = to;
                Push(&move_list,moves);
                ClearBit(&attacks,to);
            }
        }
    }
    return move_list;
}
pile* LegalMoves(int trait)
{
    Model UndoBoard = ChessBoard;
    Clear(&MoveList);
    MoveList = PseudoLegalMoves(trait);
    pile *next = MoveList;
    Shift next_move;
    while(next)
    {
        next_move = Peek(next);
        MakeMove(next_move.from,next_move.to);
        if(KingIsChecked(trait))
        {
            MoveList = Remove(MoveList,next_move);
            ChessBoard = UndoBoard;
        }
        next = next->previous;
        ChessBoard = UndoBoard;
    }
    if(!KingIsChecked(trait) && !MoveList)
        {
            puts("MATCH NUL");
	    getchar();
            exit(EXIT_SUCCESS);
        }
    if(!MoveList && KingIsChecked(trait))
    {
        puts("ECHEC ET MAT !");
	getchar();
        exit(EXIT_SUCCESS);
    }
  return MoveList;
}

int GetPiece(int from, int side)
{
    int type_piece = 0;
    while((ChessBoard.ModelPiece[side][type_piece] & PositionTable[from])== 0)
    {
        type_piece++;
    }
    return type_piece;
}

int GetSide(int from)
{
    if (ChessBoard.ModelSide[WHITE] & PositionTable[from])return WHITE;
    else return BLACK;
}

void MakeMove(int from, int to)
{
    int side, piece;
    side = GetSide(from);
    piece = GetPiece(from, side);
    ChessBoard.ModelPiece[side][piece] ^= PositionTable[from];
    ChessBoard.ModelPiece[side][piece] |= PositionTable[to];
    if(PositionTable[to] & ChessBoard.ModelSide[!side]) Capture(to,!side);
    UpdateModel(&ChessBoard);
}

void Capture(int square, int side_attacked)
{
    int i = 0;
    /*
    Bitboard target = PositionTable[square] & ChessBoard.ModelSide[side_attacked];
    if (target)
    {
        target = PositionTable[square] & ChessBoard.ModelPiece[side_attacked][i];
        while(!target)
        {
            i++;
        }
        ClearBit(&ChessBoard.ModelPiece[side_attacked][i],square);
    }
    UpdateModel(&ChessBoard);*/
    for(i = 0; i < 6; i++)
    {
        ClearBit(&ChessBoard.ModelPiece[side_attacked][i],square);
    }

    UpdateModel(&ChessBoard);
}

void UpdateModel(Model *Board)
{
    int i, j;
    Board->ModelSide[ALL] = empty_board;

    for(j = 0; j < 2; j++)
    {
        Board->ModelSide[j] = empty_board;
        for(i = 0; i < 6; i++)
        {
            Board->ModelSide[j] |= Board->ModelPiece[j][i];
        }
    }
    Board->ModelSide[ALL] = Board->ModelSide[WHITE] | Board->ModelSide[BLACK];
}
