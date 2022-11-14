#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "Functions.h"

#define ROWS    6
#define COLS    7
#define FOUR    4

/*The following c code represents the connect 4 game between two players
Each player has to input in a column a letter from A to G (A-B-C-D-E-F-G)
which will fill the table with a token ( represented by 1 and 2 ) in the corresponding place.

The objective of the game is to be the first to form a horizontal,
vertical, or diagonal line of four of one's own tokens. 

If a player wins the game, the program will print the winner.
TEST CASES:
The code runs for all the cases:

1) If the player wins or loses:
-Who wins:
    First player wins
    Second player wins
-How does the player win:
    Vertical:Insert the following letters: A-B-A-B-A-B-A
    Horizontal:Insert the following letters: A-A-B-A-C-A-D
    Upper diagonal:Insert the following letters: A-B-C-D-B-C-D-E-C-D-D
    Lower diagonal: Insert the following letters: G-F-E-D-F-E-D-C-F-E-E
    
2) If the game is a draw:
    The winner is based on the speed of the input of the letters: the faster player wins.
    Insert the following letters: A-C-B-D-E-F-G-G-F-C-E-D-E-F-A-C-B-A-C-B-D-C-G-D-A-E-B-G-F-G-D-F-G-E-F-D-E-A-A-B-B-C-C


3) If the player inputs a wrong input:

-Wrong letter: 
    Try inserting: H //The program will print that the letter is wrong and ask for another letter
-Inputing a word: 
    Try inserting: Hello //The program will print that the letter is wrong and ask for another letter since H is not a bin
    Try inserting: Apple //It will take the first letter

4)The Column is full: 
    Try inserting: A-A-A-A-A-A-A //The program will print that the column is full and ask for another letter

*/


/* variables *************************************************************/
char scores[ROWS][COLS];
int bin = 0;
char disc;
char name1[20];
char name2[20];

time_t begin, end;
int time1 = 0;
int time2 = 0;


/* main function *************************************************************/

int main()
{
    Players();
    Coin();
    init_scores();
    board();
    Conditions();
}

/* end of main function *************************************************************/

/* ***********************************************************************/
/* ***********************************************************************/

/* helper functions **********************************************************/

void init_scores()
{
    /*
    requirement: n/a
    effect: initializes the scores array with spaces
    */
    // fill the scores with the empty character:
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            scores[i][j] = '0'; 
        }
    }
}

void board()
{
    /*
    requirement: n/a
    effect: prints the board
    */
    char header[] = "  A   B   C   D   E   F   G  ";
    char horbar[] = "|---|---|---|---|---|---|---|";

    // print the board and the scores according to current game
    printf("%s\n", header);
    printf("%s\n", horbar);
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        printf("%s\n", horbar);
    }
}

void choose()
{
    /*
    requirement: choose A B C D E F G
    effects: fills the bin with the chosen column
            / ask again if input is wrong
            / ask again if column is full
            / records time in case game Draws
    */

    char c;
    begin=0;
    end=0;
    time(&begin);   //timer begins

    while (1)
    {
        printf("\nChoose bin: ");
        scanf(" %s", &c);
        switch(c)
        {       //changes bin depending on First Index of inputted Character.
            case 'A':
            case 'a':
                bin = 0;
                break;
            case 'B':
            case 'b':
                bin = 1;
                break;
            case 'C':
            case 'c':
                bin = 2;
                break;
            case 'D':
            case 'd':
                bin = 3;
                break;
            case 'E':
            case 'e':
                bin = 4;
                break;
            case 'F':
            case 'f':
                bin = 5;
                break;
            case 'G':
            case 'g':
                bin = 6;
                break;
            default:
                bin = 666;
                printf("\nWrong letter! Try again.\n\n");
                board();
        }
        // break out of while loop if the right letter was chosen:
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] == '0'))
        {
            fill_bin();
            time(&end); //end timer
                if (disc == '1')
                {   //increment timer for player disc 1
                    time1 = time1 + difftime(end, begin);
                }
                else
                {   //increment timer for player disc 2
                    time2 = time2 + difftime(end, begin);
                }
            if (disc == '1')
            {   //replace current disc from 1 to 2 and vice versa
                disc='2';
            }
            else
            {
                disc='1';
            }
            
            break;
        }
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] != '0'))
        {   //if column is full, ask again
            printf("\nThis bin is full! Try again.\n\n");
            board();
        }
        
    }
}

void fill_bin()
{
    /*
    requirement: n/a
    effect: fills the bin with the chosen column
    */
    // fills the bin according to what's already in there
    int level ;     // lowest level or bottom of the board 

    for (level = ROWS-1; level >= 0; level--)
    {
        if (scores[level][bin] == '0')
        {
            scores[level][bin] = disc;
            break;
        }
    }                
}

int check(char disc)
{
    /*
    requirement: disc = 1 or 2
    effect: checks if there are 4 discs of the same kind in a row/diagonal/vertical
    */

    // checks for a 4-disc row, column or diagonal:
   
    int i, j, k;
    int count;
   
   //checks for 4 in a row horizontally
    for (int j = 0; j<=ROWS-3 ; j++ ){
        for (int i = 0; i<COLS; i++){
            if (scores[i][j] == disc && scores[i][j+1] == disc && scores[i][j+2] == disc && scores[i][j+3] == disc){
                return 1;
            }          
        }
    }

   //checks for 4 in a row vertically
    for (int i = 0; i<COLS-3 ; i++ ){
        for (int j = 0; j<=ROWS; j++){
            if (scores[i][j] == disc && scores[i+1][j] == disc && scores[i+2][j] == disc && scores[i+3][j] == disc){
                return 1;
            }          
        }
    }
   
   //checks for 4 in a row in the first diagonal
    for (int i=3; i<COLS; i++){
        for (int j=0; j<=ROWS-3; j++){
            if (scores[i][j] == disc && scores[i-1][j+1] == disc && scores[i-2][j+2] == disc && scores[i-3][j+3] == disc)
                return 1;
        }
    }

    //checks for 4 in a row in the second diagonal
    for (int i=3; i<COLS; i++){
        for (int j=3; j<=ROWS; j++){
            if (scores[i][j] == disc && scores[i-1][j-1] == disc && scores[i-2][j-2] == disc && scores[i-3][j-3] == disc)//diagonal
                return 1;
        }
    }
    return 0;
}

    
int checkString(char str1[]) {
    /*
    requirement: str1[] = string to be checked
    effect: checks if player name input contains a White Space
    */
    int i, p;   
    p=strlen(str1);
    for (i = 0; i < p ; i++){
        if (str1[i]== ' ') {
            return 0;
        } 
    }
  return 1;
}

int randomizer(){
    /*
    requirement: n/a
    effect: generates a random number between 0 and 1
    */
    int i, n, result;
    time_t t;
    n = 1;
    // Intializes random number generator 
    srand((unsigned) time(&t));
    return result= rand() % 2;  //returns 0 or 1 depending if random number is even or not
  }

void Players(){
    /*
    requirement: n/a
    effect: asks for player names and checks if they are valid
    */

    printf("\nWelcome to connect Four!\n");
    printf("Please enter your names: \n");

    printf("Player 1: ");
    // we need to find a new way to get the names
    //gets() is unsafe and leaks to next scan
    //as well as gets causes an error in terminal since it is a dangerous function
    scanf("%s", &name1);
    while(checkString(name1) == 0) {
    printf("Invalid input. \nPlease enter a valid string with no spaces. \n");
    printf("Player 1: ");
    scanf("%s", &name1);
    }

    printf("Player 2: ");
    scanf("%s", &name2);
    while(checkString(name2) == 0) {
    printf("Invalid input. \nPlease enter a valid string with no spaces. \n");
    printf("Player 2: ");
    scanf("%s", &name2);
    }

    printf("\nHello %s, you are playing with %s \n", name1, name2);

}

void Coin(){
    /*
    requirement: n/a
    effect: Flips a coin to see who starts first
    */
    printf("Randomizing who goes first...\n");
    int starter = randomizer();
    if (starter==0){
        printf("\n\n%s goes first!\n\n", name1);
        disc='1';
    }
    else{
        printf("\n\n%s goes first!\n\n", name2);
        disc='2';
        /*switches the discs*/
    }
}

void Conditions(){
    /*
    requirement: n/a
    effect: Asks user to choose a column to drop their disc in
            //checks if player won
            // through draw or normal win
    */
    while (1)
    {
        if (Tie())
            {
                printf("\nGame ends in draw.\n\n");
                printf("Winner is based on speed of input:\n");
                if (time1>time2){
                    printf("%s wins!\n", name2);
                    printf("%s won by %d Seconds!\n", name2, time1-time2);
                }
                else if (time2>time1){
                    printf("%s wins!\n", name1);
                    printf("%s won by %d Seconds!\n", name1, time2-time1);
                }
                else{
                    printf("It's a tie!\n");
                }
                break;
            }
        if (disc=='1')
        {
            printf("\n%s, please choose a column: ", name1);
        }
        else
        {
            printf("\n%s, please choose a column: ", name2);
        }
        choose();
        printf("\n\n");
        board();
        if (check('1'))
        {
            printf("\n\n%s wins!\n\n", name1);
            break;  
        }
        if (check('2'))
        {
            printf("\n\n%s wins!\n\n", name2);
            break;  
        }   
    }
    
}

bool Tie(){
    /*
    requirement: n/a
    effect: checks if the board is full
    */
    for (int i=0; i<7; i++){
        if (scores[0][i] == '0'){
            return false;  //The board is not full
        }
    }
    return true;    //The board is full
}

//checking the MinMax of each possible move, calculating the best move 
int MinMax(int depth, int turn){
    /*
    requirement: depth = depth of the tree
                 turn = 1 if it is the AI's turn, 0 if it is the player's turn
    effect: checks the MinMax of each possible move, calculating the best move
    */
   
    int score = 0;
    if (Tie()) return 0;

    if (turn == 1){ //AI's turn
        int best = -1000;   //best score
        for (int i=0; i<7; i++){    //for each possible move
            if (scores[0][i] == '0'){   //if the column is not full
                for (int j=5; j>=0; j--){   //find the lowest empty row
                    if (scores[j][i] == '0'){   //if the row is empty
                        scores[j][i] = '1'; //drop the disc
                        score = MinMax(depth+1, 0); //calculate the score
                        scores[j][i] = '0'; //undo the move
                        if (score > best){  //if the score is better than the best score
                            best = score;   //update the best score
                        }
                        break;
                    }
                }
            }
        }
        return best;
    }
    else{
        int best = 1000;
        for (int i=0; i<7; i++){
            if (scores[0][i] == '0'){
                for (int j=5; j>=0; j--){
                    if (scores[j][i] == '0'){
                        scores[j][i] = '2';
                        score = MinMax(depth+1, 1);
                        scores[j][i] = '0';
                        if (score < best){
                            best = score;
                        }
                        break;
                    }
                }
            }
        }
        printf("best: %d\n", best);
        return best;
    }
}

int MonteCarlomove(){
    /*
    requirement: n/a
    effect: calculates the best move using Monte Carlo Tree Search
    */
    int best = -1000;
    int bestMove = 0;
    int score = 0;
    for (int i=0; i<7; i++){
        if (scores[0][i] == '0'){
            for (int j=5; j>=0; j--){
                if (scores[j][i] == '0'){
                    scores[j][i] = '1';
                    score = MonteCarlo(0);
                    scores[j][i] = '0';
                    if (score > best){
                        best = score;
                        bestMove = i;
                    }
                    break;
                }
            }
        }
    }
    return bestMove;
}