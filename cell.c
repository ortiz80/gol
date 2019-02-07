#include <stdlib.h>
#include "cell.h"

CELL create_cell(int C_STATE, int pos_x, int pos_y)
{
    CELL new_cell = (CELL) malloc(sizeof(cell));
    new_cell -> x = pos_x;
    new_cell -> y = pos_y;
    new_cell -> c_state = C_STATE;
    return new_cell;
}

void set_state(CELL cell, int C_STATE)
{
    cell -> c_state = C_STATE;
    return;
}

int get_state(CELL cell)
{
    return (cell -> c_state);
}