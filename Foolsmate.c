//foolsmate team
// Ryan Atallah, Perla Daghfal, Nadine Saimua, Bucker Yahfoufi

//cmps 270-Software Construction

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


/*The following c code represents the connect 4 game in two modes Player vs. Player and PLayer vs. Bot 
Each player has to input in a column an integer from 1 to 7 (1-2-3-4-5-6-7)
which will fill the table with a token ( represented by 1 and 2 ) in the corresponding place.
The objective of the game is to be the first to form a horizontal,
vertical, or diagonal line of four of one's own tokens. 
If a player wins the game, the program will print the winner.
If the bot wins the game, the program will print that the bot won.*/


//TEST CASES:

/*Multiplayer mode:
The code runs for all the cases:
1) If the player wins or loses:
-Who wins:
    First player wins
    Second player wins
-How does the player win:
    Vertical:Insert the following integers: 1-2-1-2-1-2-1
    Horizontal:Insert the following integers: 1-1-2-1-3-1-4
    Upper diagonal:Insert the following integers: 1-2-3-4-2-3-4-5-3-4-4
    Lower diagonal: Insert the following integers: 7-6-5-4-6-5-4-3-6-5-5                                  
    
2) If the game is a draw:
    The winner is based on the speed of the input of the letters: the faster player wins.
    Insert the following integers: 1 3 2 4 5 6 7 7 6 3 5 4 5 6 1 3 2 1 3 2 4 3 7 4 1 5 2 7 6 7 4 6 7 5 7 5 4 5 1 1 2 2 3 3
    
3) If the player inputs a wrong input:
   example If the input inserts 8 the program will print an error message and will ask the player to insert a new input.

4)The Column is full: 
    Try inserting: 1-1-1-1-1-1-1 //The program will print that the column is full and ask for another letter
*/

/*Bot mode:
There are 3 Difficulty levels:
1)Easy: The bot will look at depth 3
2)Medium: The bot will look at depth 5
3)Hard: The bot will look at depth 12

The code runs for all the cases:
1) If the player wins or loses:
-Who wins:
    First player wins
    Bot wins
-How does the player win:
    Vertical
    Horizontal
    Upper diagonal
    Lower diagonal
2) If the game is a draw:
    The winner is based on the speed of the input of the letters: the faster player wins.

3) If the player inputs a wrong input:
    example If the input inserts 8 the program will print an error message and will ask the player to insert a new input.

4)The Column is full:
    The program will print that the column is full and ask for another letter

Testing Bot Win/Lose:
1) Easy, Bot starts: Specific case, of where the bot starts
2) Easy, Player starts: player moves: 1-2-2-3-4-4-5-5-5 - player wins
    2*) Cannot check for bot winnings

3) Medium, Bot starts: Specific case, of where the bot starts
4) Medium, PLayer starts: Bot plays according to depth 5
    4*) Cannot check for bot winnings

5) Hard, Bot starts: Specific case, of where the bot starts
6) Hard, PLayer starts: Bot plays according to depth 12
    6*) Cannot check for bot winnings

*/


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
    int whoGoesFirst = tossAcoin();
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


/*Requires: the user to enter a number between 1 and 7
  Modifies: the board by inserting the first player's piece into the bin they choose
  Effects: asks the first player to make a move and then inserts their piece into the bin they choose*/
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
  Effects: asks the bot to make a move and then inserts their piece into the bin they choose*/
void easyMove()
{
    int columnNumber;//the column number the bot chooses
    time_t start, end;

    printf("You are playing against the Easy Bot...\n\n");
    start = time(NULL);

    columnNumber = minimax(3, -1000, 1000, 0).column;//calls the minimax function and stores the column number the bot chooses in the variable columnNumber with a depth of 3

    printf("Column number: %d \n", columnNumber+1);

    scores[numOfZeros[columnNumber]][columnNumber] = 2; //inserts the bot's piece into the bin they choose
    numOfZeros[columnNumber]--;                         //decrements the number of zeros in the column by 1

    end = time(NULL); //end time of the bot's move

    time2 += ((double)(end - start)); //adds the time it took for the bot to make a move to the total time
}


/*Requires: nothing
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the bot to make a move and then inserts their piece into the bin they choose*/
void mediumMove()
{
    int columnNumber;
    time_t start, end;

    printf("You are playing against the Medium Bot...\n\n");
    start = time(NULL);

    columnNumber = minimax(5, -1000, 1000, 0).column; //calls the minimax function and stores the column number the bot chooses in the variable columnNumber with a depth of 5

    printf("Column number: %d \n", columnNumber+1);

    scores[numOfZeros[columnNumber]][columnNumber] = 2; //inserts the bot's piece into the bin they choose
    numOfZeros[columnNumber]--;                         //decrements the number of zeros in the column by 1

    end = time(NULL); //end time of the bot's move

    time2 += ((double)(end - start)); //adds the time it took for the bot to make a move to the total time
}

/*Requires: nothing
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the bot to make a move and then inserts their piece into the bin they choose*/
void hardMove()

{
    int columnNumber;
    time_t start, end;

    printf("You are playing against the Hard Bot...\n\n");
    start = time(NULL);

    columnNumber = minimax(12, -1000, 1000, 0).column;//calls the minimax function and stores the column number the bot chooses in the variable columnNumber with a depth of 12

    printf("Column number: %d \n", columnNumber+1);

    scores[numOfZeros[columnNumber]][columnNumber] = 2;
    numOfZeros[columnNumber]--;
    end = time(NULL);

    time2 += ((double)(end - start));
}

/*Requires: nothing
  Modifies: the board by inserting the bot's piece into the bin they choose
  Effects: asks the player to choose a difficulty level for the bot and then inserts their piece into the bin they choose*/
void choose()
{
    if (choice == 3)
    {
        easyMove();
    }
    else if (choice == 4)
    {
        mediumMove();
    }
    else if (choice == 5)
    {
        hardMove();
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
    printf("Choose a mode: \n");
    /* printf("1. Easy\n");
     printf("2. Medium\n");
     printf("3. Hard\n");*/
    printf("\t1. Single Player\n");
    printf("\t2. Multiplayer\n");
    printf("Choose 1 or 2 : ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Choose a difficulty: \n");
        printf("\t3. Easy\n");
        printf("\t4. Medium\n");
        printf("\t5. Hard\n");
        printf("Choose 3, 4 or 5 : ");
        scanf("%d", &choice);
        if (choice == 3)
        {
            printf("You chose Easy Bot.\n");
        }
        else if (choice == 4)
        {
            printf("You chose Medium Bot.\n");
        }
        else if (choice == 5)
        {
            printf("You chose Hard Bot.\n");
        }
        else
        {
            printf("Invalid choice. Please choose 3, 4 or 5.\n");
            scanf("%d", &choice);
        }
    }

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


/*Requires: nothing
  Modifies: nothing
  Effects: checks if there is a winner and if it returns 1, then there is a winner and the game ends
            else if it returns 0, then there is no winner and the game continues*/
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



/*Requires: nothing
  Modifies: nothing
  Effects: checks if there is a winner horizontally and if it returns 1, then there is a winner and the game ends
            else if it returns 0, then there is no winner and the game continues*/
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

/*Requires: nothing
  Modifies: nothing
  Effects: checks if there is a winner in the first and if it returns 1, then there is a winner and the game ends
            else if it returns 0, then there is no winner and the game continues*/
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

/*Requires: nothing
  Modifies: nothing
  Effects: checks if there is a winner in the second diagonal and if it returns 1, then there is a winner and the game ends
            else if it returns 0, then there is no winner and the game continues*/
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

/*Requires: nothing
    Modifies: nothing
    Effects: checks if there is a winner vertically and if it returns 1, then there is a winner and the game ends
                else if it returns 0, then there is no winner and the game continues*/
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


/*Requires: nothing
  Modifies: creates a 2D array which is the board
  Effects: creates a 2D array which is the board*/
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

// Displaying the board
/*Requires: nothing
Modifies: nothing
 Effects: displays the board*/
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


/*Requires: nothing
   Effects: tosses a coin to decide who starts the game. If the result is 1, then player 1 starts, else player 2 starts*/
int tossAcoin()
{
    srand(time(NULL));//seeds the random number generator
    int headsOrTails = rand() % 2;//generates a random number between 0 and 1
    printf("Flipping a coin...\n");
    if (headsOrTails == 1)
    {//if the result is 1, then player 1 starts
        printf("\n%s makes the first move.\n\n", name1);
        return 1;
    }
    else
    {//if the result is 0, then player 2 starts
        if (choice == 2)
        {
            printf("\n%s makes the first move.\n\n", name2);
            return 2;
        }
        else
        {
            printf("\n The bot makes the first move.\n\n");
            return 2;
        }
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
