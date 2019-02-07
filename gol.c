#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gol.h"
#include "cell.h"
#include "stack.h"

/* grid size */
#define ROWS 25
#define COLS 81
/*
#define ROWS 100
#define COLS 100
*/
#define STARTROW 1
#define STARTCOL 1

void print_board(CELL board[ROWS+1][COLS+1])
{
    int r;
    int c;
    /* clear screen */
    printf("\033[2J\033[;H");

    for(r = STARTROW; r < ROWS; r++)
    {
        for(c = STARTCOL; c < COLS; c++)
        {
            printf("%s", (board[r][c] -> c_state == DEAD) ? " " : "X"); 
        }
    }
    
    sleep(1);
    
}

void init_board(CELL board[ROWS+1][COLS+1])
{
    int r;
    int c;
    int n_times;
    int i;
    int s; /* status */
    
    /*set borders to DEAD */
    for(c = 0; c < COLS+1; c++)
    {
        board[0][c] = create_cell(DEAD, 0, c);
        board[ROWS+1][c] = create_cell(DEAD, ROWS+1, c);
    }
    for(r = 0; r < ROWS+1; r++)
    {
        board[r][0] = create_cell(DEAD, 0, c);
        board[r][COLS+1] = create_cell(DEAD, 0, c);
    }

    /*set the board to all DEAD */
    for(r = STARTROW; r <= ROWS; r++)
    {
        for(c = STARTCOL; c <= COLS; c++)
        {
            board[r][c] = create_cell(DEAD, r, c);
        }
    }
    /* filling the board with random data */
    srand(time(NULL));
    
    /* numero compreso tra 1 e ROWS*COLS */
    n_times = 1 + rand() % ((ROWS+1) * (COLS + 1));
    for(i = 0; i < n_times; i++)
    {
        r = 1 + (rand() % (ROWS + 1));
        c = 1 + (rand() % (COLS + 1));
        board[r][c] = create_cell(ALIVE, r, c);
    }
/*
    for(r = STARTROW; r <= ROWS; r++)
    {
        for(c = STARTCOL; c <= COLS; c++)
        {
            s = rand();
            board[r][c] = create_cell((s % 2)? DEAD : ALIVE, r, c);
        }
    }
*/
}

int all_dead(CELL board[ROWS+1][COLS+1])
{
    int r;
    int c;
    for (r = 0; r < ROWS; r++)
    {
        for(c = 0; c < COLS; c++)
        {
            if(board[r][c] -> c_state == ALIVE)
            {
                return 0;
            }
        }
    }
    return 1;
}

void look_around(CELL grid[ROWS+1][COLS+1], int row, int col, int *n_alive, int *n_dead)
{
    int r;
    int c;

    for(r = row - 1; r <= row + 1; r++)
    {
        for(c = col - 1; c <= col + 1; c++)
        {
            if (r == row && c == col)
            {
                continue;
            }
            else
            {
                if(grid[r][c] -> c_state == ALIVE)
                {
                *   n_alive = *n_alive + 1;
                }
                else
                {
                    *n_dead = *n_dead + 1;
                }
            }
            
        }
    }
}
void stack_changes(CELL board[ROWS+1][COLS+1], int r, int c, int n_alive, int n_dead, Stack *s)
{
    if (board[r][c] -> c_state == ALIVE)
    {
        if(n_alive < 2)
        {
            push(*s, create_cell(DEAD, r, c));
        }
        else if(n_alive == 2 || n_alive == 3)
        {
            push(*s, create_cell(ALIVE, r, c));
        }
        else if (n_alive > 3)
        {
            push(*s, create_cell(DEAD, r, c));
        }
        else
        {
            return;
        }
    }
    else
    {
        if (n_alive == 3)
        {
            push(*s, create_cell(ALIVE, r, c));
        }
        else
        {
            return;
        }
        
    }  
}

void play(CELL board[ROWS+1][COLS+1], Stack s)
{
    while(1)
    {
        int r = 0;
        int c = 0;
        int n_alive = 0;
        int n_dead = 0;
        if(all_dead(board))
        {
            return;
        }
        
        print_board(board);
        
        /* push in the stack all the updates */
        for(r = STARTROW ; r < ROWS; r++)
        {
            for(c = STARTCOL; c < COLS; c++)
            {
                look_around(board, r, c, &n_alive, &n_dead);
                stack_changes(board, r, c, n_alive, n_dead, &s);
                n_alive = 0;
                n_dead = 0;
            }
        }
        if(stack_empty(s))
        {
            /* no changes -- exit */
        }
        /* apply the updates */
        while(!stack_empty(s))
        {
            CELL t = (CELL) pop(s);
            board[t->x][t->y] = t;
        }
    }

    return;
}

int main()
{
    /* do nothing */
    Stack s = init_stack(); /* nello Stack inserisco tutte le variazioni */
    CELL game_board[ROWS+1][COLS+1]; /* campo di gioco + cornice */

    printf("An overly complex \"Game of Life\" implementations in plain c\n");

    init_board(game_board); /* riempio con cellule casuali */
    play(game_board, s);
    return EXIT_SUCCESS;
}