struct cell
{
    int x;
    int y;
    int c_state;
};

typedef struct cell cell;
typedef cell* CELL;
enum c_states {DEAD, ALIVE } C_STATE;


CELL create_cell(int C_STATE, int pos_x, int pos_y);
void set_state(CELL cell, int C_STATE);
int get_state(CELL cell);
