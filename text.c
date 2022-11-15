int  best_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int playerNum;
    int bestMove;

    playerNum = (computer_num == 1 ? 2 : 1); //if computer is player 1, then player is 2 

    if (check3win(board, computer_num) != 8)    //if there is a 3 in a row block
    {
        bestMove = check3win(board, computer_num);
        update_board(board, bestMove, computer_num);
        return bestMove;
    }
    else if (build2(board,computer_num) != 8)
    {
        bestMove = build2(board, computer_num);
        update_board(board, bestMove, computer_num);
        return bestMove;
    }
/*    else if (build1(board,computer_num) != 8)
    {
        bestMove = build1(board,computer_num);
        update_board(board, bestMove, computer_num);
        return bestMove;
    }*/
    else bestMove = random_move(board, computer_num);

    return bestMove;
}

/*  Function build2()  */
int build2(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int build2;

    if (build2_diagDN(board,computer_num) != 8)
    {
        build2 = build2_diagDN(board,computer_num);
        return build2;
    }

    if (build2_diagUP(board,computer_num) != 8)
    {
        build2 = build2_diagUP(board,computer_num);
        return build2;
    }
    if (build2vert(board,computer_num) != 8)
    {
        build2 = build2vert(board,computer_num);
        return build2;
    }
    if (build2horiz(board,computer_num) != 8)
    {
        build2 = build2horiz(board,computer_num);
        return build2;
    }
    return 8;
}

/*  Function build2_diagDN()  */
int build2_diagDN(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c][r]     == computer_num  &&
                board[c+1][r+1] == computer_num  &&
                board[c+3][r+3] == 0             &&
                board[c+2][r+2] == 0)
            {
                if (is_column_full(board,c+3)) continue;

                if (r == 3 || board[c+2][r+1] != 0) return c+3;
            }

            //check [] [] X X
            if (board[c+2][r+2]  == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+1][r+1]  == 0             &&
                board[c+1][r+2]  != 0)
            {
                if (is_column_full(board,c+2)) continue;

                return c+2;
            }

            //check [] X X []
            if (board[c+2][r+2]  == computer_num  &&
                board[c+1][r+1]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+3][r+3]  == 0)
            {
                if (is_column_full(board,c+4)) continue;

                if (r == 3 || board[c+3][r+3]  != 0) return c+4;
            }

            //check [] X [] X
            if (board[c+1][r+1]  == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+2][r+2]  == 0             &&
                board[c][r+1]    != 0)
            {
                if (is_column_full(board,c+1)) continue;

                return c+1;
            }

            //check X [] X []
            if (board[c+2][r+2]  == computer_num  &&
                board[c][r]      == computer_num  &&
                board[c+1][r+1]  == 0             &&
                board[c+3][r+3]  == 0)
            {
                if (is_column_full(board,c+4)) continue;

                if (r == 3 || board[c+3][r+3]  != 0) return c+4;
            }

            //check X [] [] X
            if (board[c][r+1]    == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c+1][r+1]  == 0             &&
                board[c+2][r+2]  == 0             &&
                board[c+2][r+3]  != 0)
            {
                if (is_column_full(board,c+3)) continue;

                return c+3;
            }
        }
    }
    return 8;
}


/*  Function build2_diagUP()  */
int build2_diagUP(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 3; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c][r]      == computer_num  &&
                board[c+1][r-1]  == computer_num  &&
                board[c+3][r-3]  == 0             &&
                board[c+2][r-2]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check [] [] X X
            if (board[c+2][r-2]  == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+1][r-1]  == 0)
            {
                if (r == BOARD_SIZE_VERT || board[c][r+1] != 0) return c+1;
            }

            //check [] X X []
            if (board[c+2][r-2]  == computer_num  &&
                board[c+1][r-1]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+3][r-3]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check [] X [] X
            if (board[c+1][r-1]  == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+2][r-2]  == 0)
            {
                if (r == BOARD_SIZE_VERT || board[c][r+1] != 0)  return c+1;
            }

            //check X [] X []
            if (board[c+2][r-2]  == computer_num  &&
                board[c][r]      == computer_num  &&
                board[c+1][r-1]  == 0             &&
                board[c+3][r-3]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check X [] [] X
            if (board[c][r+1]    == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c+1][r-1]  == 0             &&
                board[c+2][r-2]  == 0             &&
                board[c+1][r-2]  != 0)

                return c+2;
        }
    }
    return 8;
}


/*  Function build2vert()  */
int build2vert(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 2; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < BOARD_SIZE_HORIZ; c++)
        {
            if (is_column_full(board,c))
            {
                printf("column %d full. Skipping\n", c);
                continue;
            }
            if (board[c][r-1]  == 0            &&
                board[c][r]    == computer_num &&
                board[c][r+1]  == computer_num)
            {
                return c+1;
            }
        }
    }
    return 8;
}


/*  Function build2horiz()  */
int build2horiz(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 5; r >= 0; r--)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c+3][r]  == 0             &&
                board[c+2][r]  == 0             &&
                board[c+1][r]  == computer_num  &&
                board[c][r]    == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4;
            }
            //check [] [] X X
            if (board[c][r]    == 0             &&
                board[c+1][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1;
            }
            //check [] X X []
            if (board[c][r]    == 0             &&
                board[c+3][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c+1][r]  == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+1;
            }

            //check X [] X []
            if (board[c+3][r]  == 0             &&
                board[c+1][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c][r]    == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4;
            }
            //check [] X [] X
            if (board[c][r]    == 0             &&
                board[c+2][r]  == 0             &&
                board[c+1][r]  == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1;
            }
            //check X [] [] X
            if (board[c+1][r]  == 0             &&
                board[c+2][r]  == 0             &&
                board[c][r]    == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+2;
            }
        }
    }
    return 8;
}


/*  Function check3win()  */
int check3win(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int winMove;
    int blockMove;
    int playerNum;

    playerNum = (computer_num == 1 ? 2 : 1);

    if (check3_vertwin(board, computer_num) != 8) {
        winMove = check3_vertwin(board, computer_num);
        return winMove;
    }
    if (check3_horizwin(board, computer_num) != 8) {
        winMove = check3_horizwin(board, computer_num);
        return winMove;
    }
    if (check3_diagRUwin(board, computer_num) != 8) {
        winMove = check3_diagRUwin(board, computer_num);
        return winMove;
    }
    if (check3_diagRDwin(board, computer_num) != 8) {
        winMove = check3_diagRDwin(board, computer_num);
        return winMove;
    }
    if (check3_vertwin(board, playerNum) != 8) {
        blockMove = check3_vertwin(board, playerNum);
        return blockMove;
    }
    if (check3_horizwin(board, playerNum) != 8) {
        blockMove = check3_horizwin(board, playerNum);
        return blockMove;
    }
    if (check3_diagRUwin(board, playerNum) != 8) {
        blockMove = check3_diagRUwin(board, playerNum);
        return blockMove;
    }
    if (check3_diagRDwin(board, playerNum) != 8) {
        blockMove = check3_diagRDwin(board, playerNum);
        return blockMove;
    }
    return 8;
}
/*  Function check3_vertwin()  */
int check3_vertwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    //start checking from 5th row; can't make a move if top row full
    for (r = 1; r < 4; r++)
    {
        for (c = 0; c < BOARD_SIZE_HORIZ; c++)
        {
            if (is_column_full(board,c))
            {
                printf("Column %d full. Skipping\n", c);
                continue;
            }

            if (board[c][r-1]   == 0                 &&
                board[c][r]     == computer_num      &&
                board[c][r+1]   == computer_num      &&
                board[c][r+2]   == computer_num)
            {
                return c+1; //changed from c
            }
        }
    }
    return 8;
}
/*  Function check3_horizwin()  */
int check3_horizwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 5; r >= 0; r--)
    {
        for (c = 0; c < 5; c++)
        {
            //check X X X []
            if (board[c+3][r]  == 0                 &&
                board[c][r]    == computer_num      &&
                board[c+1][r]  == computer_num      &&
                board[c+2][r]  == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4; //changed from 3
            }
            //check X [] X X
            if (board[c+1][r] == 0                 &&
                board[c][r]   == computer_num      &&
                board[c+2][r] == computer_num      &&
                board[c+3][r] == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+2;  //changed from 1
            }
            //check X X [] X
            if (board[c+2][r]   == 0                 &&
                board[c][r]     == computer_num      &&
                board[c+1][r]   == computer_num      &&
                board[c+3][r]   == computer_num)
            {
                if (r == 5 || board[c+2][r+1] != 0) return c+3; //changed from 2
            }
            //check [] X X X
            if (board[c][r]   == 0                 &&
                board[c+1][r] == computer_num      &&
                board[c+2][r] == computer_num      &&
                board[c+3][r] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}

/*  Function check3_diagRDwin()  */
int check3_diagRDwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X X []
            if (board[c+3][r+3] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r+1] == computer_num &&
                board[c+2][r+2] == computer_num)
            {
                if (r == 3 || board[c+3][r+4] == 1 || board[c+3][r+4] == 2) return c+4;
            }

            //check X X [] X
            if (board[c+2][r+2] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r+1] == computer_num &&
                board[c+3][r+3] == computer_num &&
                board[c+2][r+3] != 0 )
            {
                return c+3;
            }
            //check X [] X X
            if (board[c+1][r+1] == 0            &&
                board[c][r]     == computer_num &&
                board[c+2][r+2] == computer_num &&
                board[c+3][r+3] == computer_num &&
                board[c+1][r+2] != 0)
            {
                return c+2;
            }
            //check [] X X X
            if (board[c][r]     == 0                 &&
                board[c+1][r+1] == computer_num      &&
                board[c+2][r+2] == computer_num      &&
                board[c+3][r+3] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}
/*  Function check3_diagRUwin()  */
int check3_diagRUwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 3; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X X []
            if (board[c+3][r-3] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r-1] == computer_num &&
                board[c+2][r-2] == computer_num &&
                board[c+3][r-2] != 0)
            {
                return c+4; //changed from 3?
            }

            //check X X [] X
            if (board[c+2][r-2] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r-1] == computer_num &&
                board[c+3][r-3] == computer_num &&
                board[c+2][r-1] != 0)
            {
                return c+3;  //changed from 2?
            }
            //check X [] X X
            if (board[c+1][r-1] == 0            &&
                board[c][r]     == computer_num &&
                board[c+2][r-2] == computer_num &&
                board[c+3][r-3] == computer_num &&
                board[c+1][r] != 0)
            {
                return c+2;  //changed from 1?
            }
            //check [] X X X
            if (board[c][r]     == 0                 &&
                board[c+1][r+1] == computer_num      &&
                board[c+2][r+2] == computer_num      &&
                board[c+3][r+3] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}
