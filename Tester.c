#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#define ROWS 6
#define COLS 7
int scores[6][7]; // 6 rows, 7 columns
int choice;
char name1[20], name2[20];                 // names
double time1, time2 = 0;                   // a double has twice the precision of a floating point number in C
int numOfZeros[7] = {5, 5, 5, 5, 5, 5, 5}; // number of zeros in each column(levels 0-5)



int main()
{
    playConnectFour();
}

/*requires: nothing
  effects: Runs as our main function*/
void playConnectFour()
{
    int winner = 0;
    initializeBoard();
    int whoGoesFirst = 1;
    int zeros = 42;
    while (zeros != 0 && winner == 0)
    {
        display();
        if (whoGoesFirst == 1)
        {
            playerMove();
            winner = WinOrNot();
            display();
            if (winner != 0)
            {
                display(); // for displaying the board after the final move
                printf("%s won!", name1);
                break;
            }
            choose();
            winner = WinOrNot();
            if (winner != 0)
            {
                display(); // for displaying the board after the final move
                if (choice == 2)
                {
                    printf("%s won!", name2);
                }
                else
                {
                    printf("Bot won!");
                }
                break;
            }
        }
        else
        {
            choose();
            winner = WinOrNot();
            display();
            if (winner != 0)
            {
                display(); // for displaying the board after the final move
                if (choice == 2)
                {
                    printf("%s won!", name2);
                }
                else
                {
                    printf("Bot won!");
                }
                break;
            }
            playerMove();
            winner = WinOrNot();
            if (winner != 0)
            {
                display(); // for displaying the board after the final move
                printf("%s won!", name1);
                break;
            }
        }
    }

    winner = WinOrNot();

    if (winner == 0)
    {
        if (time1 > time2)
        {
            if (choice == 3)
            {
                strcpy(name2, "easyBot");
            }
            else if (choice == 4)
            {
                strcpy(name2, "mediumBot");
            }
            else if (choice == 5)
            {
                strcpy(name2, "hardBot");
            }
            else
            {
                strcpy(name2, name2);
            }

            printf("%s, you took %f seconds \n", name1, time1);

            printf("%s, you took %f seconds \n", name2, time2);

            printf("Game was a tie. %s was faster, they won!", name2);
        }
        else if (time1 < time2)
        {
            if (choice == 3)
            {
                strcpy(name2, "easyBot");
            }
            else if (choice == 4)
            {
                strcpy(name2, "mediumBot");
            }
            else if (choice == 5)
            {
                strcpy(name2, "hardBot");
            }
            else
            {
                strcpy(name2, name2);
            }
            printf("%s, you took %f seconds \n", name1, time1);
            printf("%s, you took %f seconds \n", name2, time2);

            printf("Game was a tie. %s was faster, they won!", name1);
        }
    }
}


void playerMove()
{
    int columnNumber;//the column number the player chooses
    time_t start, end;

    printf("%s's turn. ", name1);//asks the player to make a move
    start = time(NULL);//start time of the player's move
    do
    {
        printf("Enter the column number(1-7): ");//asks the player to enter a column number
        scanf("%d", &columnNumber);
        printf("\n");
        if (columnNumber <= 0 || columnNumber > 7) //if the player enters a number that is not between 1 and 7
        {
            printf("Invalid column number. Please enter a number between 1 and 7. \n");
            printf("Enter the column number(1-7): ");
            scanf("%d", &columnNumber);
            columnNumber--;                                             //decrements the column number by 1
            scores[numOfZeros[columnNumber]][columnNumber] = 1;         //inserts the player's piece into the bin they choose
            numOfZeros[columnNumber]--;                                 //decrements the number of zeros in the column by 1
            printf("\n");
        }

        // check if column is full
        else if (numOfZeros[columnNumber - 1] == -1)
        {
            printf("Column is full. Please enter a different column number. \n");
            printf("Enter the column number(1-7): ");
            scanf("%d", &columnNumber);
            columnNumber--;
            scores[numOfZeros[columnNumber]][columnNumber] = 1;
            numOfZeros[columnNumber]--;
            printf("\n");
        }
        else
        {
            columnNumber--;
            scores[numOfZeros[columnNumber]][columnNumber] = 1;
            numOfZeros[columnNumber]--;
            printf("\n");
            break;
        }
    } 
    while (scores[0][columnNumber] != 0);//while the column is full
    end = time(NULL);//end time of the player's move
    time1 += ((double)(end - start));//adds the time it took for the player to make a move to the total time
}

/*Requires: the playe to enter a number between 1 and 7
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the bot or the second player to make a move and then inserts their piece into the bin they choose*/
void player2move()
{
    int columnNumber;
    time_t start, end;

    printf("%s, your move...", name2);
    start = time(NULL);
    do
    {                                                 //asks the player to enter a column number
        printf("Enter the column number(1-7): ");
        scanf("%d", &columnNumber);//the column number the player chooses
        printf("\n");
        if (columnNumber <= 0 || columnNumber > 7) //if the player enters a number that is not between 1 and 7
        {                                                 
            printf("Invalid column number. Please enter a number between 1 and 7. \n");
            printf("Enter the column number(1-7): ");
            scanf("%d", &columnNumber);
            columnNumber--;
            scores[numOfZeros[columnNumber]][columnNumber] = 2;//inserts the player's piece into the bin they choose
            numOfZeros[columnNumber]--;
            printf("\n");
        }

        // check if column is full or not
        else if (numOfZeros[columnNumber - 1] == -1)
        {
            printf("Column full!\n");
            printf("Enter a valid column number(1-7): ");
            scanf("%d", &columnNumber);//the column number the player chooses
            columnNumber--;//decrements the column number by 1
            scores[numOfZeros[columnNumber]][columnNumber] = 2;//inserts the player's piece into the bin they choose
            numOfZeros[columnNumber]--;//decrements the number of zeros in the column by 1
            printf("\n");//prints a new line
        }
        else
        {//decrements the column number by 1
            columnNumber--;
            scores[numOfZeros[columnNumber]][columnNumber] = 2;//inserts the player's piece into the bin they choose
            numOfZeros[columnNumber]--;//decrements the number of zeros in the column by 1
            break;
        }
    } while (scores[0][columnNumber] != 0);
    end = time(NULL);

    time2 += ((double)(end - start));//adds the time it took for the player to make a move to the total time
}

/*Requires: nothing
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the player to choose a difficulty level for the bot and then inserts their piece into the bin they choose*/
void choose()
{
    if (choice == 3)
    {
  
    }
    else if (choice == 4)
    {

    }
    else if (choice == 5)
    {
       int colnnum= hardMove(scores[6][7]);
    }
    else
    {
        player2move();
    }
}



/*Requires: nothing
  Modifies: the name of the players and the difficulty level of the bot
  Effects: asks the player to enter which mode they want to play in and then asks the player to enter the names of the players and the difficulty level of the bot*/
void start()
{
    // Ask the player what mode he wants to play
    printf("\t1. Single Player\n");
    choice=5;
    

    // Asking player names
    printf("Enter your name: ");
    scanf("%s", name1);
    printf("\n");

    // If the mode is 2 (not against bot), ask the name of the second player
    if (choice == 2)
    {
        printf("Enter your name: ");
        scanf("%s", name2);
        printf("\n");
    }
}
int WinOrNot()
{
    if (checkHorizontal() != 0)
    {
        return 1;
    }
    else if (checkVertical() != 0)
    {
        return 1;
    }
    else if (checkDiagonalA() != 0)
    {
        return 1;
    }
    else if (checkDiagonalB() != 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
int checkHorizontal()
{
    for (int j = 0; j<=ROWS-3 ; j++ ){//checks the rows
        for (int i = 0; i<COLS; i++){//checks the columns
            if (scores[i][j] == 1 && scores[i][j+1] == 1 && scores[i][j+2] == 1 && scores[i][j+3] == 1){//checks if there are 4 consecutive 1s horizontally
                return 1;
            }    
            else if (scores[i][j] == 2 && scores[i][j+1] == 2 && scores[i][j+2] == 2 && scores[i][j+3] == 2){//checks if there are 4 consecutive 2s horizontally
                return 1;
            }      
        }
    }
    return 0;   
}
int checkDiagonalA()
{
     for (int i=3; i<COLS; i++){
        for (int j=0; j<=ROWS-3; j++){
            if (scores[i][j] == 1 && scores[i-1][j+1] == 1 && scores[i-2][j+2] == 1 && scores[i-3][j+3] == 1){//checks if there are 4 consecutive 1s diagonally
                return 1;}
            else if (scores[i][j] == 2 && scores[i-1][j+1] == 2 && scores[i-2][j+2] == 2 && scores[i-3][j+3] == 2){//checks if there are 4 consecutive 2s diagonally
                return 1;}
            
        }
    }
    return 0;
}
int checkDiagonalB(){
for (int i=3; i<COLS; i++){
        for (int j=3; j<=ROWS; j++){
            if (scores[i][j] == 1 && scores[i-1][j-1] == 1 && scores[i-2][j-2] == 1 && scores[i-3][j-3] == 1){
                return 1;}
            else if (scores[i][j] == 2 && scores[i-1][j-1] == 2 && scores[i-2][j-2] == 2 && scores[i-3][j-3] == 2){
                return 1;}
        }
    }
    return 0;
    }

int checkVertical()
{
    for (int i = 0; i<COLS-3 ; i++ ){
        for (int j = 0; j<=ROWS; j++){
            if (scores[i][j] == 1 && scores[i+1][j] == 1 && scores[i+2][j] == 1 && scores[i+3][j] == 1){
                return 1;
            } 
            else if (scores[i][j] == 2 && scores[i+1][j] == 2 && scores[i+2][j] == 2 && scores[i+3][j] == 2){
                return 1;
            }           
        }
    }
    return 0;
}


void initializeBoard()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            scores[i][j] = 0;
        }
    }
    start();
}

void display()
{
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("|---|---|---|---|---|---|---|\n\n");
    int row, column = 0;

    for (row = 0; row < 6; row++)
    {
        printf("| %d |", scores[row][0]);
        for (column = 1; column < 7; column++)
        {
            printf(" %d |", scores[row][column]);
        }
        printf("\n");
        printf("|---|---|---|---|---|---|---|\n");
    }
}


/*Requires: a side which is either 1 or 2
  Modifies: nothing
  Effects: checks if there is a winner  whether horizontaly, vertically or diagonally and if there is, then it returns 1, else it returns 0*/
int checkWinningSide(int side)
{
    int winningSide = 0;
    // check horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores[i][j] == side && scores[i][j + 1] == side && scores[i][j + 2] == side && scores[i][j + 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check vertical
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (scores[i][j] == side && scores[i + 1][j] == side && scores[i + 2][j] == side && scores[i + 3][j] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores[i][j] == side && scores[i + 1][j + 1] == side && scores[i + 2][j + 2] == side && scores[i + 3][j + 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if (scores[i][j] == side && scores[i + 1][j - 1] == side && scores[i + 2][j - 2] == side && scores[i + 3][j - 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    return winningSide;
}

 /*Requires: nothing
      Effects: returns the score of the favorability of the position*/
int favOfPosition()
{
    // check horizontal
    int score = 0;

    // check horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores[i][j] == 2 && scores[i][j + 1] == 2 && scores[i][j + 2] == 2 && scores[i][j + 3] == 2)
            {
                score += 100;
            }
            else if (scores[i][j] == 2 && scores[i][j + 1] == 2 && scores[i][j + 2] == 2)
            {
                score += 10;
            }
            else if (scores[i][j] == 2 && scores[i][j + 1] == 2)
            {
                score += 2;
            }

            else if (scores[i][j] == 1 && scores[i][j + 1] == 1 && scores[i][j + 2] == 1)
            {
                score -= 100;
            }
        }
    }

    // check vertical
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (scores[i][j] == 2 && scores[i + 1][j] == 2 && scores[i + 2][j] == 2 && scores[i + 3][j] == 2)
            {
                score += 100;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j] == 2 && scores[i + 2][j] == 2)
            {
                score += 10;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j] == 2)
            {
                score += 2;
            }

            else if (scores[i][j] == 1 && scores[i + 1][j] == 1 && scores[i + 2][j] == 1)
            {
                score -= 100;
            }
        }
    }

    // check diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores[i][j] == 2 && scores[i + 1][j + 1] == 2 && scores[i + 2][j + 2] == 2 && scores[i + 3][j + 3] == 2)
            {
                score += 100;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j + 1] == 2 && scores[i + 2][j + 2] == 2)
            {
                score += 10;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j + 1] == 2)
            {
                score += 2;
            }

            else if (scores[i][j] == 1 && scores[i + 1][j + 1] == 1 && scores[i + 2][j + 2] == 1)
            {
                score -= 100;
            }
        }
    }

    // check diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if (scores[i][j] == 2 && scores[i + 1][j - 1] == 2 && scores[i + 2][j - 2] == 2 && scores[i + 3][j - 3] == 2)
            {
                score += 100;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j - 1] == 2 && scores[i + 2][j - 2] == 2)
            {
                score += 10;
            }
            else if (scores[i][j] == 2 && scores[i + 1][j - 1] == 2)
            {
                score += 2;
            }

            else if (scores[i][j] == 1 && scores[i + 1][j - 1] == 1 && scores[i + 2][j - 2] == 1)
            {
                score -= 100;
            }
        }
    }

    return score;
}

/*Requires:four parameters integer which represents the depth of the tree , the alpha value, the beta value, the side which is either 1 or 2
  Modifies: nothing
  Effects: returns the best move for the bot*/
botMove minimax(int depth, int alpha, int beta, int maximizingPlayer)
{
    botMove ret;//the return value
    int check = checkWinningSide(2) - checkWinningSide(1);//checks if there is a winner

    if (depth == 0 || check == 1 || check == -1)
    {//if the depth is 0 or there is a winner, then it returns the score
        if (check == 1 || check == -1)
        {//if there is a winner, then it returns the score
            WinOrNot();//checks if there is a winner
            if (check == 1)
            {//if the bot wins, then it returns a score of 1000
                ret.column = -2;
                ret.score = 1000000;
                return ret;
            }
            else if (check == -1)
            {//if the player wins, then it returns a score of -1000
                ret.column = -2;
                ret.score = -1000000;
                return ret;
            }
            else // game is over, no more valid moves
            {//if there is no winner, then it returns a score of 0
                ret.column = -2;//the column is -2 because it is not a valid move
                ret.score = 0;//game is over, no more valid moves
                return ret;
            }
        }
        else // depth is zero
        {//if the depth is 0, then it returns the score
            ret.column = -2;
            ret.score = favOfPosition();
            return ret;
        }
    }

    if (maximizingPlayer)
    {//if it is the bot's turn
        int bestScore = -1000000;
        int col;

        do//it loops until it finds a valid move
            (col = rand() % 7);//generates a random number between 0 and 6
        while (scores[0][col] != 0);//checks if the column is full

        for (int i = 0; i < 7; i++)
        {//it loops through all the columns
            if (scores[0][i] == 0)
            {//if the column is not full, then it makes a move
                scores[numOfZeros[i]][i] = 2;//makes a move
                numOfZeros[i]--;
                int score = minimax(depth - 1, alpha, beta, 0).score;//calls the minimax function
                scores[numOfZeros[i] + 1][i] = 0;
                numOfZeros[i]++;

                if (score > bestScore)
                {//if the score is greater than the best score, then it updates the best score and the column
                    bestScore = score;
                    col = i;
                }

                if (bestScore > alpha)
                {//if the best score is greater than the alpha value, then it updates the alpha value
                    alpha = bestScore;
                }
                if (beta <= alpha)
                {//if the beta value is less than or equal to the alpha value, then it breaks the loop
                    break;
                }
            }
        }
        ret.column = col;
        ret.score = bestScore;//returns the best score
        return ret;
    }
    else
    {//if it is the player's turn
        int bestScore = 1000000;
        int col;

        do
            (col = rand() % 7);
        while (scores[0][col] != 0);

        for (int i = 0; i < 7; i++)
        {
            if (scores[0][i] == 0)
            {
                scores[numOfZeros[i]][i] = 1;
                numOfZeros[i]--;
                int score = minimax(depth - 1, alpha, beta, 1).score;
                scores[numOfZeros[i] + 1][i] = 0;
                numOfZeros[i]++;

                if (score < bestScore)
                {
                    bestScore = score;
                    col = i;
                }
                if (bestScore < beta)
                {
                    beta = bestScore;
                }

                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        ret.column = col;
        ret.score = bestScore;
        return ret;
    }
}


/*Requires: nothing
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the bot to make a move and then inserts their piece into the bin they choose*/
  //change hard move to take as input the array of scores and the array of numOfZeros
  //and return columnNumber
int hardMove(int scores[6][7])
{
    int columnNumber;
    botMove retur= minimax(12, -1000, 1000, 0);

    printf("You are playing against the Hard Bot...\n\n");
    //start = time(NULL);

    columnNumber = minimax(12, -1000, 1000, 0).column;  //calls the minimax function and stores the column number the bot chooses in the variable columnNumber with a depth of 12

    printf("Column number: %d \n", columnNumber+1);

    scores[numOfZeros[columnNumber]][columnNumber] = 2;
    numOfZeros[columnNumber]--;
    //end = time(NULL);

    //time2 += ((double)(end - start));
    return retur.column;
}