#include "sudoku.h"
#include <string.h>
void argument_error();

int main(int argc, char **argv)
{ /* Main is pretty straightforward, no need for any comments I think. */
    unique_gen = 0;
    srand(getpid());
    if (argc == 1)
    {
        Grid_T grid = sudoku_read();
        fprintf(stderr, "Input puzzle:\n");
        sudoku_print(stderr, grid);
        grid = sudoku_solve(grid);
        if (sudoku_solution_is_unique(grid) == 1)
        {
            fprintf(stderr, "Puzzle has a (unique choice) solution:\n");
            sudoku_print(stdout, grid);
        }
        else
        {
            if (sudoku_is_correct(grid))
            {
                fprintf(stderr, "Puzzle has a (non-unique choice) solution:\n");
                sudoku_print(stdout, grid);
            }
            else
            {
                fprintf(stderr, "Puzzle has no actual solution. Potential solution (with the following errors):\n");
                sudoku_print(stdout, grid);
                sudoku_print_errors(grid);
            }
        }
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-c") == 0)
        {
            Grid_T grid = sudoku_read();
            fprintf(stderr, "Input puzzle:\n");
            sudoku_print(stderr, grid);
            if (sudoku_is_correct(grid))
            {
                fprintf(stderr, "Puzzle is correct!\n");
            }
            else
            {
                fprintf(stderr, "Puzzle is incorrect!\n");
                sudoku_print_errors(grid);
            }
        }
        else
        {
            argument_error();
            exit(-1);
        }
    }
    else
    {
        if (argc == 3 || argc == 4)
        {
            if (strcmp(argv[1], "-g") == 0)
            {
                int x = atoi(argv[2]);
                Grid_T grid;

                if (x < 0 || x > GRID_LENGTH * GRID_LENGTH)
                {
                    fprintf(stderr, "Invalid nelts choice. Please choose an integer between 0 and 81.\n");
                    exit(-1);
                }
                if (argc == 4)
                {
                    if (strcmp(argv[3], "-u") == 0)
                    {
                        unique_gen = 1;
                    }
                    else
                    {
                        argument_error();
                        exit(-1);
                    }
                }
                grid = sudoku_generate(x);
                fprintf(stdout, unique_gen ? "Generated Puzzle with unique solution:\n" : "Generated Puzzle:\n");
                sudoku_print(stdout, grid);
            }
            else
            {
                argument_error();
                exit(-1);
            }
        }
        else
        {
            argument_error();
            exit(-1);
        }
    }

    return 0;
}

void argument_error()
{
    fprintf(stderr, "Invalid execution command\n");
    fprintf(stderr, "Execution formats:\n");
    fprintf(stderr, "./sudoku\t\t -> (no arguments) Read a puzzle from stdin and try to solve it\n");
    fprintf(stderr, "./sudoku -c\t\t -> Read a puzzle from stdin and check for any errors\n");
    fprintf(stderr, "./sudoku -g nelts\t -> Generate a puzzle with 81 - nelts empty cells (add optional param -u to generate a unique solution puzzle*)\n");
    fprintf(stderr, "\n\n*: Caution: in that case there may be less empty cells than requested, especially if nelts number is small.\n");
}