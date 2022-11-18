
typedef struct botMove_foolsmate botMove_foolsmate;
botMove_foolsmate minimax_foolsmate(); 

struct botMove_foolsmate// This struct is used to return the best move and the score of the best move from the minimax_foolsmate function
{
    int column;
    int score;
};

int make_move_foolsmate();
int favOfPosition_foolsmate();
int checkWinningSide_foolsmate();