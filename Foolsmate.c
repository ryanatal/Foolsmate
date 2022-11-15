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
Each player has to input in a column a number from 1 to 7 (1-2-3-4-5-6-7)
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
    Vertical:Insert the following letters: 1-2-1-2-1-2-1
    Horizontal:Insert the following letters: 1-1-2-1-3-1-4
    Upper diagonal:Insert the following letters: 1-2-3-4-2-3-4-5-3-4-4
    Lower diagonal: Insert the following letters: 7-6-5-4-3-6-4-4
    
2) If the game is a draw:
    The winner is based on the speed of the input of the letters: the faster player wins.
    Insert the following letters: 1-3-2-4-5-6-7-7-6-3-5-4-5-6-1-3-2-1-3-2-4-3-7-4-1-5-2-7-6-7-4-6-7-5-7-6-5-4-5-1-1-2-2-3-3


3) If the player inputs a wrong input:

-Wrong letter: 
    Try inserting: H //The program will print that the letter is wrong and ask for another letter
-Inputing a word: 
    Try inserting: Hello //The program will print that the letter is wrong and ask for another letter since H is not a bin
    Try inserting: Apple //It will take the first letter

4)The Column is full: 
    Try inserting: 1-1-1-1-1-1-1 //The program will print that the column is full and ask for another letter

*/


/* variables *************************************************************/
char matrix[ROWS][COLS];
int bin = 0;
char disc;
char name1[20];
char name2[20];
int choice;
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

void Players(){
    /*
    requirement: n/a
    effect: asks for player names and checks if they are valid
    */

    printf("\nWelcome to connect Four!\n");

    printf("Would you like to play against a bot or player?\n");
    printf("1. Player VS Player\n");
    printf("2. Player VS Bot\n");
    scanf("%d", &choice);

    if(choice==1){
    printf("Please enter your names: \n");

    printf("Player 1: ");
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
    //---------------------------
    else if(choice==2){
    printf("Please enter your name: \n");
    scanf("%s", &name1);
    while(checkString(name1) == 0) {
    printf("Invalid input. \nPlease enter a valid string with no spaces. \n");
    printf("Player: ");
    scanf("%s", &name1);
    }
    printf("\nThe bot will be called Bot\n");
    printf("\nHello %s, you are playing with Bot \n\n", name1);
    }
    //---------------------------
    else{
    printf("Invalid input. \nPlease enter a valid number. \n");
    Players();
    }
}

void Coin(){
    /*
    requirement: n/a
    effect: Flips a coin to see who starts first
    */
    printf("\nRandomizing who goes first...\n");
    
    int starter = randomizer();
    if(choice==1){
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
    else if(choice==2){
    if (starter==0){
        printf("\n\n%s goes first!\n\n", name1);
        disc='1';
    }
    else{
        printf("\n\nBot goes first!\n\n");
        disc='2';
        /*switches the discs*/
    }
    }
}

void init_scores()
{
    /*
    requirement: n/a
    effect: initializes the matrix array with spaces
    */
    // fill the matrix with the empty character:
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            matrix[i][j] = '0'; 
        }
    }
}

void board()
{
    /*
    requirement: n/a
    effect: prints the board
    */
    char header[] = "  1   2   3   4   5   6   7  ";
    char horbar[] = "|---|---|---|---|---|---|---|";

    // print the board and the matrix according to current game
    printf("%s\n", header);
    printf("%s\n", horbar);
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", matrix[i][j]);
        }
        printf("|\n");
        printf("%s\n", horbar);
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
            //---------------------------
        if (choice==1){
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
        //---------------------------
        else if(choice==2){
        if (disc=='1')
        {
            printf("\n%s, please choose a column: ", name1);
            choose();
            printf("\n\n");
            board();
        }
        else
        {
            printf("\nBot, please choose a column: ");
            //whatever the bot calls
            //best_move(array[][]);
        }
        if (check('1'))
        {
            printf("\n\n%s wins!\n\n", name1);
            break;  
        }
        if (check('2'))
        {
            printf("\n\nBot wins!\n\n");
            break;  
        }   
        }
    }
}


/* helper of the helper functions **********************************************************/

void choose()
{
    /*
    requirement: choose 1 2 3 4 5 6 7
    effects: fills the bin with the chosen column
            / ask again if input is wrong
            / ask again if column is full
            / records time in case game Draws
    */

    int c;
    begin=0;
    end=0;
    time(&begin);   //timer begins

    while (1)
    {
        printf("\nChoose bin: ");
        scanf(" %d", &c);
        switch(c)
        {       //changes bin depending on First Index of inputted Character.
            case 1:
                bin = 0;
                break;
            case 2:
                bin = 1;
                break;
            case 3:
                bin = 2;
                break;
            case 4:
                bin = 3;
                break;
            case 5:
                bin = 4;
                break;
            case 6:
                bin = 5;
                break;
            case 7:
                bin = 6;
                break;
            default:
                bin = 666;
                printf("\nInvalid Number! Try again.\n\n");
                board();
        }
        // break out of while loop if the right letter was chosen:
        if ((bin >= 0 && bin <= 6) && (matrix[0][bin] == '0'))
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
        if ((bin >= 0 && bin <= 6) && (matrix[0][bin] != '0'))
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
        if (matrix[level][bin] == '0')
        {
            matrix[level][bin] = disc;
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
            if (matrix[i][j] == disc && matrix[i][j+1] == disc && matrix[i][j+2] == disc && matrix[i][j+3] == disc){
                return 1;
            }          
        }
    }

   //checks for 4 in a row vertically
    for (int i = 0; i<COLS-3 ; i++ ){
        for (int j = 0; j<=ROWS; j++){
            if (matrix[i][j] == disc && matrix[i+1][j] == disc && matrix[i+2][j] == disc && matrix[i+3][j] == disc){
                return 1;
            }          
        }
    }
   
   //checks for 4 in a row in the first diagonal
    for (int i=3; i<COLS; i++){
        for (int j=0; j<=ROWS-3; j++){
            if (matrix[i][j] == disc && matrix[i-1][j+1] == disc && matrix[i-2][j+2] == disc && matrix[i-3][j+3] == disc)
                return 1;
        }
    }

    //checks for 4 in a row in the second diagonal
    for (int i=3; i<COLS; i++){
        for (int j=3; j<=ROWS; j++){
            if (matrix[i][j] == disc && matrix[i-1][j-1] == disc && matrix[i-2][j-2] == disc && matrix[i-3][j-3] == disc)//diagonal
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

bool Tie(){
    /*
    requirement: n/a
    effect: checks if the board is full
    */
    for (int i=0; i<7; i++){
        if (matrix[0][i] == '0'){
            return false;  //The board is not full
        }
    }
    return true;    //The board is full
}

