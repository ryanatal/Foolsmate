#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"
#define ROWS    6
#define COLS    7
#define FOUR    4

/* variables *************************************************************/
//tester for first-branch
//tester commit
//adding a tester comment to see if this works
//adding another comment to see if this works
/*TO DO

-timer for each player and compare time if draw  (check hello.c)
-input leaking to next scan
-gets() error is unsafe remove from terminal output


*/



char scores[ROWS][COLS];
char header[] = "  A   B   C   D   E   F   G  ";
char horbar[] = "|---|---|---|---|---|---|---|";
int bin = 0;
char disc;
char name1[20];
char name2[20];
//tie between two players sequence
//ACBDEFGGFCEDEFACBACBDCGDAEBGFGDFGEFDEAABBCC

/* main function *************************************************************/

int main()
{
    
    printf("\nWelcome to connect Four!\n");
    printf("Please enter your names: \n");

    printf("Player 1: ");
// we need to find a new way to get the names
//gets() is unsafe and leaks to next scan
//as well as gets causes an error in terminal since it is a dangerous function
    gets(name1);
    while(checkString(name1) == 0) {
    printf("Invalid input. \nPlease enter a valid string with no spaces. \n");
    printf("Player 1: ");
    gets(name1);
    }

    printf("Player 2: ");
    gets(name2);
    while(checkString(name2) == 0) {
    printf("Invalid input. \nPlease enter a valid string with no spaces. \n");
    printf("Player 2: ");
    gets(name2);
    }

    printf("\nHello %s, you are playing with %s \n", name1, name2);

/* ----------------------- */

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

//on each if and else we change disc==1 to disc==2 and vice versa depending on what we need and then
//we loop and call choose();
/* ----------------------- */

    init_scores();
    board();
    

    while (1)
    {
        if ((scores[0][0] != '0') && (scores[0][1] != '0') && (scores[0][2] != '0') && (scores[0][3] != '0')
         && (scores[0][4] != '0') && (scores[0][5] != '0') && (scores[0][6] != '0'))
            {
                printf("\nGame ends in draw.\n\n");
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
    
    return 0; 
}

/* end of main function *************************************************************/

/* helper functions **********************************************************/

/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
/* ***********************************************************************/
void init_scores()
{
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
    // print the board and the scores according to current game:
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
    // choose A B C D E F G:

    //getchar();
    //scanf(_%S);
    //scanf("%c", &bin);
    //get_s
    // use %s to read as string
    // my idea: create  a decoy scanf that collects all remaining chars so that when
    //system calls it it only takes one character
    char c;
    
    while (1)
    {
          
        printf("\nChoose bin: ");
        scanf(" %c", &c);
        switch(c)
        {
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
            if (disc == '1')
            {
                disc='2';
            }
            else
            {
                disc='1';
            }
            break;
        }
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] != '0'))
        {
            printf("\nThis bin is full! Try again.\n\n");
            board();
        }
        
    }
}

void fill_bin()
{
    // fills the bin according to what's already in there:
    int level ;     /* lowest level or bottom of the board */

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
    // checks for a 4-disc row, column or diagonal:
    
    
    /* check for 4-disc rows
    each row has 4 different ways to connect 4
    
    | X | X | X | X |   |   |   |
    |   | X | X | X | X |   |   |
    |   |   | X | X | X | X |   |
    |   |   |   | X | X | X | X |
    
     */
     
    int i, j, k;
    int count;
    int ways = 4;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i][j + k] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }
    
    
    /* check for 4-disc columns 
    each column has 3 different ways to connect 4 
    
    | X |   |   |
    | X | X |   |
    | X | X | X |
    | X | X | X |
    |   | X | X |
    |   |   | X |
    
    */
    
    ways = 3;
    
    for (j = 0; j < COLS; ++j)
    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i + k][j] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }
    
    /* check for 4-disc diagonals 
    
      A B C D E F G
    0| | | | | | | |
    1| |\|\|\|\|\| |
    2| |\|\|\|\|\| |
    3| |\|\|\|\|\| |
    4| |\|\|\|\|\| |
    5| | | | | | | |
    
    */
    
    int ii, jj;
    for (i = 1; i < ROWS-1; i++)
    {
        for (j = 1; j < COLS-1; j++)
        {
            
            /* left-tilted diagonals */
            count = 0;
            // left-upwards:
            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;    
                }
                else
                    break;
            }
            // right-downwards:
            for (ii = i+1, jj = j+1; (ii <= ROWS-1) || (jj <= COLS-1); ii++, jj++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            
            /* right-tilted diagonals */
            count = 0;
            // left-downwards:
            for (ii = i, jj = j; (ii <= ROWS-1) || (jj >= 0); ii++, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;    
                }
                else
                    break;
            }
            // right-upwards:
            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COLS-1); ii--, j++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            
        }
    }

    return 0;       
}
    
int checkString(char str1[]) {
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
    int i, n, result;
    time_t t;
    n = 1;
   /* Intializes random number generator */
    srand((unsigned) time(&t));
    return result= rand() % 2;
  }

