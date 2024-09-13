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

void print_sudoku_board(Board* board);

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

    // --------------------------------------------------------------------------------------
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

    print_sudoku_board(&board);
    return 0;
}


void print_sudoku_board(Board* board) {
    printf("Sudoku Board:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board->rows[i][j]);
        }
        printf("\n");
    }
}