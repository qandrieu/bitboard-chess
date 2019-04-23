#include "game.h"
#include "view.h"
#include <time.h>

void init_Board(Model *, int *);
void Command();
Model Play(int *, char *);
void init_ModelHistory(Model *, Model *, Model);
void UpdateModelHistory(Model *, Model *, Model);
void RecoverModel(Model);
Model Run(int*);

int main()
{
/*  uint64_t const n = UINT64_MAX;
    printf("%" PRIu64 "\n", n);
*/
    srand(time(NULL));
    int trait = WHITE;
    int new_game = 0;
    char s[255];
    char *NamePlayer[2] = {"Blancs","Noirs"};
    Model ModelHistory[] ={ChessBoard,ChessBoard};
    MoveList = NULL;

    printf("MOTEUR DE JEU D'ECHEC\n");
    printf("- 06/2017 -\n");
    printf("(Tapez \"cmd\" pour afficher la liste des commandes)\n");
    for(;;)
    {
        printf(">");
        scanf("%s",s);

        if (!strcmp(s,"cmd")){Command(s);continue;}
        if (!strcmp(s,"save")){}
        if (!strcmp(s,"open")){}
        if (!strcmp(s,"exit")){break;}
        if (!strcmp(s,"new"))
        {
            init_Board(&ChessBoard,&new_game);
            init_ModelHistory(&ModelHistory[0],&ModelHistory[1],ChessBoard);
            LegalMoves(trait);
            continue;
        }
        if (!strcmp(s,"undo"))
        {
	            if(new_game)
            {
                RecoverModel(ModelHistory[0]);
                trait = !trait;
                printf("Les %s jouent : \n",NamePlayer[trait]);
                continue;
            }
        }
        if (!strcmp(s,"run")){
            if(new_game)
            {
                LegalMoves(trait);
                UpdateModelHistory(&ModelHistory[0],&ModelHistory[1],Run(&trait));
                continue;
            }
        }
        if (strcmp(s,""))
        {
            if(new_game)
            {
                LegalMoves(trait);
                UpdateModelHistory(&ModelHistory[0],&ModelHistory[1],Play(&trait,s));
                continue;
            }
        }
    }
    Clear(&MoveList);
    return (EXIT_SUCCESS);
}

void Command(){
    printf("-----------------------------------------------------\n");
    printf("                      COMMANDES                      \n");
    printf("-----------------------------------------------------\n");
    printf("cmd : Liste des commandes \n");
    printf("new : Nouvelle partie\n");
//    printf("save : Sauvegarder la partie \n");
  //  printf("open : Charger une partie\n");
//    printf("-----------------------------------------------------\n");
    printf("Pour jouer une piece, taper les deux cases a la suite\n");
    printf("Ex : b1a3\n");
    printf("run : L'ordinateur joue un coup\n");
    printf("undo : Annuler le dernier coup\n");
    printf("exit : Quitter\n");
    printf("-----------------------------------------------------\n");
}

void init_Board(Model *Board, int* n_game)
{
    *n_game = 1;
    printf(" -- NOUVELLE PARTIE --\n");
    init_PositionTable(PositionTable,SIZE_BOARD);
    Mask = init_Table();
    init_RayAttacksTable(RayAttacksTable, PositionTable, SIZE_BOARD);
    init_KingAttacksTable(Mask,PositionTable,KingAttacksTable);
    init_KnightAttacksTable(Mask,PositionTable,KnightAttacksTable);

    Board->ModelPiece[WHITE][PAWN] = 0xFF00;
    Board->ModelPiece[WHITE][ROOK] = PositionTable[a1] | PositionTable[h1];
    Board->ModelPiece[WHITE][KNIGHT] = PositionTable[b1] | PositionTable[g1];
    Board->ModelPiece[WHITE][BISHOP] = PositionTable[c1] | PositionTable[f1];
    Board->ModelPiece[WHITE][QUEEN] = PositionTable[d1];
    Board->ModelPiece[WHITE][KING] = PositionTable[e1];

    Board->ModelPiece[BLACK][PAWN] = 0xFF000000000000;
    Board->ModelPiece[BLACK][ROOK] = PositionTable[a8] | PositionTable[h8];
    Board->ModelPiece[BLACK][KNIGHT] = PositionTable[b8] | PositionTable[g8];
    Board->ModelPiece[BLACK][BISHOP] = PositionTable[c8] | PositionTable[f8];
    Board->ModelPiece[BLACK][QUEEN] = PositionTable[d8];
    Board->ModelPiece[BLACK][KING] = PositionTable[e8];

    UpdateModel(Board);
    init_PieceView(PieceView);
    print_ChessBoard(*Board);
    printf("Les Blancs jouent : \n");
}

Model Play(int *trait, char *hit)
{
    Shift player_move;
    init_player(&player_move,hit);
    char *NamePlayer[2] = {"Blancs","Noirs"};

    if(!InList(MoveList, player_move))
    {
        puts("Mouvement interdit");
    }
    else
    {
        MakeMove(player_move.from,player_move.to);
        print_ChessBoard(ChessBoard);
        *trait = !*trait;
        LegalMoves(*trait);
        if(KingIsChecked(*trait))puts("ECHEC AU ROI");
        printf("Les %s jouent : \n",NamePlayer[*trait]);
    }
    return ChessBoard;
}

Model Run(int *trait)
{
    char *NamePlayer[2] = {"Blancs","Noirs"};
    pile *next = MoveList;
    int n =rand()%Length(MoveList);
    Shift run_move;
    int i = 0;

    while(i < n)
    {
        next = next->previous;
        i++;
    }
    run_move = next->movement;

    if(!InList(MoveList, run_move))
    {
        puts("Mouvement interdit");
    }
    else
    {
        MakeMove(run_move.from,run_move.to);
        print_ChessBoard(ChessBoard);
        *trait = !*trait;
        LegalMoves(*trait);
        if(KingIsChecked(*trait))puts("ECHEC AU ROI");
        printf("Les %s jouent : \n",NamePlayer[*trait]);
    }
    return ChessBoard;
}

void init_ModelHistory(Model *Previous, Model *Present, Model Next)
{
    *Present = Next;
    *Previous = *Present;
}

void RecoverModel(Model Previsous)
{
    ChessBoard = Previsous;
    print_ChessBoard(ChessBoard);
}

void UpdateModelHistory(Model *Previous, Model *Present, Model Next)
{
    *Previous = *Present;
    *Present = Next;
}