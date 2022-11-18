#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "connect4_Foolsmate.h"
#define ROWS 6
#define COLS 7
int scores_foolsmate[6][7]; // 6 rows, 7 columns

int numOfZeros_foolsmate[7] = {5, 5, 5, 5, 5, 5, 5};


/*Requires: a side which is either 1 or 2
  Modifies: nothing
  Effects: checks if there is a winner  whether horizontaly, vertically or diagonally and if there is, then it returns 1, else it returns 0*/
int checkWinningSide_foolsmate(int side)
{
    int winningSide = 0;
    // check horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores_foolsmate[i][j] == side && scores_foolsmate[i][j + 1] == side && scores_foolsmate[i][j + 2] == side && scores_foolsmate[i][j + 3] == side)
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
            if (scores_foolsmate[i][j] == side && scores_foolsmate[i + 1][j] == side && scores_foolsmate[i + 2][j] == side && scores_foolsmate[i + 3][j] == side)
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
            if (scores_foolsmate[i][j] == side && scores_foolsmate[i + 1][j + 1] == side && scores_foolsmate[i + 2][j + 2] == side && scores_foolsmate[i + 3][j + 3] == side)
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
            if (scores_foolsmate[i][j] == side && scores_foolsmate[i + 1][j - 1] == side && scores_foolsmate[i + 2][j - 2] == side && scores_foolsmate[i + 3][j - 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    return winningSide;
}

 /*Requires: nothing
      Effects: returns the score of the favorability of the position*/
int favOfPosition_foolsmate()
{
    // check horizontal
    int score = 0;

    // check horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i][j + 1] == 2 && scores_foolsmate[i][j + 2] == 2 && scores_foolsmate[i][j + 3] == 2)
            {
                score += 100;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i][j + 1] == 2 && scores_foolsmate[i][j + 2] == 2)
            {
                score += 10;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i][j + 1] == 2)
            {
                score += 2;
            }

            else if (scores_foolsmate[i][j] == 1 && scores_foolsmate[i][j + 1] == 1 && scores_foolsmate[i][j + 2] == 1)
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
            if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j] == 2 && scores_foolsmate[i + 2][j] == 2 && scores_foolsmate[i + 3][j] == 2)
            {
                score += 100;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j] == 2 && scores_foolsmate[i + 2][j] == 2)
            {
                score += 10;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j] == 2)
            {
                score += 2;
            }

            else if (scores_foolsmate[i][j] == 1 && scores_foolsmate[i + 1][j] == 1 && scores_foolsmate[i + 2][j] == 1)
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
            if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j + 1] == 2 && scores_foolsmate[i + 2][j + 2] == 2 && scores_foolsmate[i + 3][j + 3] == 2)
            {
                score += 100;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j + 1] == 2 && scores_foolsmate[i + 2][j + 2] == 2)
            {
                score += 10;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j + 1] == 2)
            {
                score += 2;
            }

            else if (scores_foolsmate[i][j] == 1 && scores_foolsmate[i + 1][j + 1] == 1 && scores_foolsmate[i + 2][j + 2] == 1)
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
            if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j - 1] == 2 && scores_foolsmate[i + 2][j - 2] == 2 && scores_foolsmate[i + 3][j - 3] == 2)
            {
                score += 100;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j - 1] == 2 && scores_foolsmate[i + 2][j - 2] == 2)
            {
                score += 10;
            }
            else if (scores_foolsmate[i][j] == 2 && scores_foolsmate[i + 1][j - 1] == 2)
            {
                score += 2;
            }

            else if (scores_foolsmate[i][j] == 1 && scores_foolsmate[i + 1][j - 1] == 1 && scores_foolsmate[i + 2][j - 2] == 1)
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
botMove_foolsmate minimax_foolsmate(int depth, int alpha, int beta, int maximizingPlayer)
{
    botMove_foolsmate ret;//the return value
    int check = checkWinningSide_foolsmate(2) - checkWinningSide_foolsmate(1);//checks if there is a winner

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
            ret.score = favOfPosition_foolsmate();
            return ret;
        }
    }

    if (maximizingPlayer)
    {//if it is the bot's turn
        int bestScore = -1000000;
        int col;

        do//it loops until it finds a valid move
            (col = rand() % 7);//generates a random number between 0 and 6
        while (scores_foolsmate[0][col] != 0);//checks if the column is full

        for (int i = 0; i < 7; i++)
        {//it loops through all the columns
            if (scores_foolsmate[0][i] == 0)
            {//if the column is not full, then it makes a move
                scores_foolsmate[numOfZeros_foolsmate[i]][i] = 2;//makes a move
                numOfZeros_foolsmate[i]--;
                int score = minimax_foolsmate(depth - 1, alpha, beta, 0).score;//calls the minimax_foolsmate function
                scores_foolsmate[numOfZeros_foolsmate[i] + 1][i] = 0;
                numOfZeros_foolsmate[i]++;

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
        while (scores_foolsmate[0][col] != 0);

        for (int i = 0; i < 7; i++)
        {
            if (scores_foolsmate[0][i] == 0)
            {
                scores_foolsmate[numOfZeros_foolsmate[i]][i] = 1;
                numOfZeros_foolsmate[i]--;
                int score = minimax_foolsmate(depth - 1, alpha, beta, 1).score;
                scores_foolsmate[numOfZeros_foolsmate[i] + 1][i] = 0;
                numOfZeros_foolsmate[i]++;

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

/*Requires: nothing however it uses the global variable scores_foolsmate
  Effects: asks the bot to make a move and then returns correponding column*/
int make_move_foolsmate()
{

    printf("You are playing against the Hard Bot...\n\n");

    int columnNumber = minimax_foolsmate(12, -1000, 1000, 0).column;  

    printf("Column number: %d \n", columnNumber+1);

    numOfZeros_foolsmate[columnNumber]--;
    return columnNumber;
    
}

int main(){
    return 0;
}