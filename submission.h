
typedef struct botMove botMove;
botMove minimax(); 

struct botMove// This struct is used to return the best move and the score of the best move from the minimax function
{
    int column;
    int score;
};

int hardMove();
int favOfPosition();
int checkWinningSide();