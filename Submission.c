#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "submission.h"

#define ROWS 6
#define COLS 7
int scores[6][7]; // 6 rows, 7 columns

int numOfZeros[7] = {5, 5, 5, 5, 5, 5, 5};


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

botMove minimax(int depth, int alpha, int beta, int maximizingPlayer)
{
    botMove ret;//the return value
    int check = checkWinningSide(2) - checkWinningSide(1);//checks if there is a winner

    if (depth == 0 || check == 1 || check == -1)
    {//if the depth is 0 or there is a winner, then it returns the score
        if (check == 1 || check == -1)
        {//if there is a winner, then it returns the score
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

int hardMove()
{
    int columnNumber;
    //time_t start, end;

    printf("You are playing against the Hard Bot...\n\n");
    //start = time(NULL);

    columnNumber = minimax(12, -1000, 1000, 0).column;  //calls the minimax function and stores the column number the bot chooses in the variable columnNumber with a depth of 12

    printf("Column number: %d \n", columnNumber+1);

    scores[numOfZeros[columnNumber]][columnNumber] = 2;
    numOfZeros[columnNumber]--;
    //end = time(NULL);
    return columnNumber;
    //time2 += ((double)(end - start));
}

int main(){
    return 0;
}