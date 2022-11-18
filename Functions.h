void initializeBoard();
void display();
int tossAcoin();
void playerMove();
void choose(); 
void player2move();
int favOfPosition();
int WinOrNot();
void start();
int checkVertical();
int checkHorizontal();
int checkDiagonalA();
int checkDiagonalB();
void playConnectFour();
typedef struct botMove botMove;
botMove minimax(); 
struct botMove
// This struct is used to return the best move and the score of the best move from the minimax function
{
    int column;
    int score;
};

int hardMove();