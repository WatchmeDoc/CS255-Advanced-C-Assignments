#include "sudoku.h"
#include <assert.h>
#define GENERATION_ATTEMPTS 10
/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9 
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1 
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7 
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5 
9 1 2 3 4 5 6 7 8 

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
/* Global variable, a flag only true if user chose -u option when generating a puzzle */
extern int unique_gen;
static int check_row(Grid_T g, int i, int j);
static int check_column(Grid_T g, int i, int j);
static int check_block(Grid_T g, int i, int j);

static void sudoku_init_choices(Grid_T *g);
static void update_row_choices(Grid_T *g, int i, int j);
static void update_column_choices(Grid_T *g, int i, int j);
static void update_block_choices(Grid_T *g, int i, int j);

static int sudoku_update_choice(Grid_T *g, int i, int j, int n);
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n);
static int sudoku_try_next(Grid_T g, int *row, int *col);

static Grid_T sudoku_generate_complete(void);

/******************************** MAIN FUNCTIONS ********************************/
Grid_T sudoku_read(void)
{
   Grid_T grid;
   int i = 0, j = 0, n;
   char c;
   while ((c = getchar()) != EOF)
   {
      if (c < 48 || c > 57)
         continue; /* Ignore all characters but numbers, and create integer from character */
      n = (int)c - 48;
      grid_update_value(&grid, i, j, n);
      if (n == 0) /*Set count to 9 if empty cell, or 0 if not empty.*/
         grid_set_count(&grid, i, j);
      else
         grid_clear_count(&grid, i, j);
      if (++j == GRID_LENGTH)
      {
         if (++i == GRID_LENGTH)
            break;
         j = 0;
      }
   }
   if (!(i == GRID_LENGTH && j == GRID_LENGTH))
   { /* If read EOF before completing sudoku */
      fprintf(stderr, "Incomplete sudoku given. Program exits.\n");
      exit(-1);
   }
   grid_set_unique(&grid);
   return grid;
}

/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g)
{
   int i, j;
   assert(s);
   for (i = 0; i < GRID_LENGTH; i++)
   {
      for (j = 0; j < GRID_LENGTH; j++)
         fprintf(s, "%d ", grid_read_value(g, i, j));
      fprintf(s, "\n");
   }
}

/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g)
{
   int i, j;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         if (!check_row(g, i, j))
            fprintf(stderr, "Element %d in row %d, column %d already exists in that row\n", grid_read_value(g, i, j), i, j);
         if (!check_column(g, i, j))
            fprintf(stderr, "Element %d in row %d, column %d already exists in that column\n", grid_read_value(g, i, j), i, j);
         if (!check_block(g, i, j))
            fprintf(stderr, "Element %d in row %d, column %d already exists in that block\n", grid_read_value(g, i, j), i, j);
         if ((grid_read_value(g, i, j) == 0))
         { /* Not actually an error, yet I chose to print empty cells as well. */
            fprintf(stderr, "Element %d in row %d, column %d is empty", grid_read_value(g, i, j), i, j);
            if (grid_read_count(g, i, j) == 0)
               fprintf(stderr, " and has no available choices");
            fprintf(stderr, "\n");
         }
      }
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g)
{
   int i, j;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
         if (!check_row(g, i, j) || !check_column(g, i, j) || !check_block(g, i, j) || (grid_read_value(g, i, j) == 0 && grid_read_count(g, i, j) == 0))
         {
            return 0;
         }

   return 1;
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g)
{
   int i, j, k;
   Grid_T ret;
   sudoku_init_choices(&g);
   if (!sudoku_is_correct(g))
   { /* If incorrect puzzle, it is definitely not one with a unique solution. */
      grid_clear_unique(&g);
      return g;
   }
   while (sudoku_try_next(g, &i, &j) != 0)
   { /* Find our next target cell. If try_next returns 0, that means there isn't any. */
      for (k = 1; k <= GRID_LENGTH; k++)
      { /* Find the proper value for the chosen cell */
         if (grid_choice_is_valid(g, i, j, k))
         {
            grid_update_value(&g, i, j, k);
            break;
         }
      }
      if (sudoku_update_choice(&g, i, j, k) == 0)
      { /* Update choice for the specific cell, and if it has no other choices, eliminate it. */
         sudoku_eliminate_choice(&g, i, j, k);
         if (sudoku_is_correct(g) == 0)
            return g;
      }
      else
      { /* If the specific cell has more choices, we have to check recursively if we made the right choice */
         grid_clear_unique(&g);
         ret = sudoku_solve(g);
         if (sudoku_is_correct(ret))
         {
            g = ret;
         }
         else
         { /* If we didn't make the right choice, we go back to zero 
            (and the value we chose is already opted-out for the specific cell) */
            grid_update_value(&g, i, j, 0);
         }
      }
   }
   return g;
}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g)
{
   return grid_read_unique(g);
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. */
Grid_T sudoku_generate(int nelts)
{ /* Generate a complete Grid */
   Grid_T grid = sudoku_generate_complete(), ret;
   int N = GRID_LENGTH * GRID_LENGTH - nelts, i, j, cnt = 0, prev_value;
   int att = GENERATION_ATTEMPTS * GENERATION_ATTEMPTS; /* MAX ATTEMPS FOR UNIQUE PUZZLE: 10K */
   assert(nelts >= 0 && nelts <= 81);
   while (cnt < N)
   { /* Random cell, if empty we move on, otherwise  */
      i = rand() % GRID_LENGTH;
      j = rand() % GRID_LENGTH;
      prev_value = grid_read_value(grid, i, j);
      if (prev_value == 0)
         continue;
      grid_update_value(&grid, i, j, 0);
      grid_set_count(&grid, i, j);
      if (unique_gen)
      { /* If we want a unique solution puzzle, try solving it. If it is unique solution, we keep it, otherwise reverting the change. */
         /* If att reaches 0 that means we couldn't create a unique solution puzzle with that amount of nelts, so
                           we return the best possible outcome. */
         if (att == 0)
         {
            att = GENERATION_ATTEMPTS * GENERATION_ATTEMPTS;
            cnt++;
         }
         ret = sudoku_solve(grid);
         if (!sudoku_solution_is_unique(ret))
         {
            grid_update_value(&grid, i, j, prev_value);
            grid_clear_count(&grid, i, j);
            att--;
            continue;
         }
      }
      cnt++;
   }
   return grid;
}
/* Generate and return a random solved grid. Attempts GENERATION_ATTEMPTS before returning a default solved one.  */
static Grid_T sudoku_generate_complete(void)
{ /* Generate a random correct grid, if not suceeded within GENERATION_ATTEMPTS attemps we return a default grid. */
   int default_arr[GRID_LENGTH][GRID_LENGTH] = {
       {2, 7, 6, 4, 1, 5, 9, 3, 8},
       {3, 4, 5, 7, 8, 9, 2, 1, 6},
       {9, 8, 1, 2, 3, 6, 4, 5, 7},
       {7, 2, 3, 8, 9, 1, 5, 6, 4},
       {6, 5, 8, 3, 4, 7, 1, 9, 2},
       {4, 1, 9, 5, 6, 2, 8, 7, 3},
       {5, 6, 4, 1, 2, 3, 7, 8, 9},
       {1, 3, 2, 9, 7, 8, 6, 4, 5},
       {8, 9, 7, 6, 5, 4, 3, 2, 1}};
   int zero[GRID_LENGTH][GRID_LENGTH] = {0}, i, j;
   Grid_T generated, ret;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         grid_update_value(&generated, i, j, zero[i][j]);
         grid_set_count(&generated, i, j);
      }
   j = 0;
   for (i = 0; i < GENERATION_ATTEMPTS; i++)
   {
      ret = sudoku_solve(generated);
      if (sudoku_is_correct(ret))
      {
         j = 1;
         break;
      }
   }
   grid_set_unique(&generated);
   grid_set_unique(&ret);
   if (j == 1)
      return ret;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         grid_update_value(&generated, i, j, default_arr[i][j]);
         grid_clear_count(&generated, i, j);
      }
   return generated;
}

/******************************** CHECKERS ********************************/

/* Check column for any duplicate values.
   Return: 1 if column is correct
           0 if there are duplicates in the same column */
static int check_column(Grid_T g, int i, int j)
{
   int row, n = grid_read_value(g, i, j);
   if (n == 0)
      return 1;
   for (row = 0; row < GRID_LENGTH; row++)
   {
      if (row == i)
         continue;
      if (grid_read_value(g, row, j) == n)
         return 0;
   }

   return 1;
}

/* Check row for any duplicate values.
   Return: 1 if row is correct
           0 if there are duplicates in the same row */
static int check_row(Grid_T g, int i, int j)
{
   int column, n = grid_read_value(g, i, j);
   if (n == 0)
      return 1;
   for (column = 0; column < GRID_LENGTH; column++)
   {
      if (column == j)
         continue;
      if (grid_read_value(g, i, column) == n)
         return 0;
   }
   return 1;
}

/* Check grid block for any duplicate values.
   Return: 1 if block is correct
           0 if there are duplicates in the same block */
static int check_block(Grid_T g, int i, int j)
{
   int row, col, block_row = 3 * ((int)i / 3), block_column = 3 * ((int)j / 3), n = grid_read_value(g, i, j);
   if (n == 0)
      return 1;
   for (row = block_row; row < block_row + 3; row++)
      for (col = block_column; col < block_column + 3; col++)
      {
         if (row == i && col == j)
            continue;
         if (n == grid_read_value(g, row, col))
            return 0;
      }
   return 1;
}

/******************************** UPDATING CHOICES ********************************/

/*
Removes choice n from the specific cell and returns its count.
*/
static int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
   grid_remove_choice(g, i, j, n);
   return grid_read_count(*g, i, j);
}

/*
Removes choice n from grid block, row and column.
*/
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
   int iter;
   if (n == 0)
      return;
   for (iter = 0; iter < GRID_LENGTH; iter++)
   {
      grid_remove_choice(g, r, iter, n);
      grid_remove_choice(g, iter, c, n);
   }
   update_block_choices(g, r, c);
}

/* Initialize choices for input grid. */
static void sudoku_init_choices(Grid_T *g)
{
   int i, j;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         update_row_choices(g, i, j);
         update_column_choices(g, i, j);
         update_block_choices(g, i, j);
      }
   return;
}

/* Removes the value of the given cell from all cells in the same row */
static void update_row_choices(Grid_T *g, int i, int j)
{
   int column, n = grid_read_value(*g, i, j);
   if (n == 0)
      return;
   for (column = 0; column < GRID_LENGTH; column++)
      grid_remove_choice(g, i, column, n);
}

/* Removes the value of the given cell from all cells in the same column */
static void update_column_choices(Grid_T *g, int i, int j)
{
   int row, n = grid_read_value(*g, i, j);
   if (n == 0)
      return;
   for (row = 0; row < GRID_LENGTH; row++)
      grid_remove_choice(g, row, j, n);
}

/* Removes the value of the given cell from all cells in the same block */
static void update_block_choices(Grid_T *g, int i, int j)
{
   int row, col, block_row = 3 * ((int)i / 3), block_column = 3 * ((int)j / 3), n = grid_read_value(*g, i, j);
   if (n == 0)
      return;
   for (row = block_row; row < block_row + 3; row++)
      for (col = block_column; col < block_column + 3; col++)
         grid_remove_choice(g, row, col, n);
}

/***************** STEP 2 **********************/

/* Chooses an empty cell from the grid with the least amount of choices.
   Return: 1 if found one
           0 if there aren't any choices for any cell */
static int sudoku_try_next(Grid_T g, int *row, int *col)
{ /* We could easily skip 2nd grid iteration using a stack here, but I thought it wasn't worth it
this time. */
   int i, j, cnt = 0, min = 10, n;
   *row = -1;
   *col = -1;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         if (grid_read_value(g, i, j) != 0)
            continue;
         n = grid_read_count(g, i, j);
         if (n < min && n != 0)
         {
            cnt = 1;
            min = n;
            *row = i;
            *col = j;
         }
         else if (n == min)
            cnt++;
      }
   if (cnt == 0)
      return 0;
   n = rand() % cnt;
   for (i = 0; i < GRID_LENGTH; i++)
      for (j = 0; j < GRID_LENGTH; j++)
      {
         if (grid_read_value(g, i, j) != 0)
            continue;
         if (grid_read_count(g, i, j) == min)
         {
            if (n == 0)
            {
               *row = i;
               *col = j;
               return 1;
            }
            n--;
         }
      }
   /* NO MAN'S LAND */
   assert(0);
   return 0;
}