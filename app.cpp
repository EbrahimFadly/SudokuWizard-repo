#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <memory>
#include <string.h>

// board is 9x9
// row, column, and box 3x3


typedef struct Board
{
    int rows[9][9];
    int columns[9][9];
    int boxes[9][9];
}Board;

void print_board(Board* board);
bool solve_backtracking(Board* board);
bool solve_Branch_And_Bound(Board board);
bool board_isvalid(Board* board);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Not enough arguments");
        exit(1);
    }

    int opt;
    char *input_fname;

    while((opt = getopt(argc, argv, "f:")) != -1){
        if (opt == 'f')
        {
            input_fname = optarg;
        }else
        {
            printf("error in the parameters format {-f input_file}");
            exit(1);
        }
    }

    FILE* file = fopen(input_fname, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[100];
    int row = 0;
    Board board;

    while (fgets(line, sizeof(line), file) && row < 9) {
        char* token = strtok(line, ",");
        int col = 0;

        while (token != NULL && col < 9) {
            int value = atoi(token);

            board.rows[row][col] = value;
            board.columns[col][row] = value;

            /*Fill the boxes array based on row and col*/
            int box_index = (row / 3) * 3 + (col / 3);
            int box_pos = (row % 3) * 3 + (col % 3);
            board.boxes[box_index][box_pos] = value;

            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }
    fclose(file);





    bool isvalid = board_isvalid(&board);
    if (isvalid)
    {
        bool solved = solve_backtracking(&board);
        if (!solved)
        {
            printf("board is unsolvable\n");
        }
        print_board(&board);
    }else{
        printf("board is invalid\n");
    }
    
    return 0;
}

bool solve_backtracking(Board* board){
    int row = 0;
    while (row < 9)
    {
        int col = 0;
        while (col < 9)
        {
            int value = board->rows[row][col];
            if (value == 0)
            {
                int box_index = (row / 3) * 3 + (col / 3);
                int box_pos = (row % 3) * 3 + (col % 3);
                for (int j = 1; j <= 9; j++)
                {
                    bool valid = true;

                    // Check the row if j is valid
                    for (int i = 0; i < 9; i++) {
                        if (board->rows[row][i] == j) {
                            valid = false;
                            break;
                        }
                    }
                    // Check the column if j is valid
                    for (int i = 0; i < 9; i++) {
                        if (board->columns[col][i] == j) {
                            valid = false;
                            break;
                        }
                    }
                    // Check the box if j is valid
                    for (int i = 0; i < 9; i++) {
                        if (board->boxes[box_index][i] == j) {
                            valid = false;
                            break;
                        }
                    }

                    if (valid) {
                        board->rows[row][col] = j;
                        board->columns[col][row] = j;
                        board->boxes[box_index][box_pos] = j;

                        // solving the rest of the board
                        if (solve_backtracking(board)) {
                            return true;
                        }

                        // backtracking 
                        board->rows[row][col] = 0;
                        board->columns[col][row] = 0;
                        board->boxes[box_index][box_pos] = 0;
                    }
                }
                return false;
            }
            col++;
        }
        row++;
    }
    return true;
}

bool board_isvalid(Board* board){
    int row = 0;
    while (row < 9)
    {
        int col = 0;
        while (col < 9)
        {
            int value = board->rows[row][col];
            int box_index = (row / 3) * 3 + (col / 3);
            int box_pos = (row % 3) * 3 + (col % 3);
            if (value != 0)
            {
                for (int i = 0; i < 9; i++) {
                    if (i != col && board->rows[row][i] == value) return false;
                }
                for (int i = 0; i < 9; i++) {
                    if (i != row && board->columns[col][i] == value) return false;
                }
                for (int i = 0; i < 9; i++) {
                    if (i != box_pos && board->boxes[box_index][i] == value) return false;
                }
            }
            col++;
        }
        row++;
    }
    return true;
}

void print_board(Board* board) {
    printf("Sudoku Board:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board->rows[i][j]);
        }
        printf("\n");
    }
}