#include "grid.h"
#include <assert.h>
#define ASSERT_DIMENTIONS(row, col)            \
    {                                          \
        assert(0 <= row && row < GRID_LENGTH); \
        assert(0 <= col && col < GRID_LENGTH); \
    }
#define ASSERT_CHOICE(n)                    \
    {                                       \
        assert(0 <= n && n <= GRID_LENGTH); \
    }

/* update value of i,j to n */
void grid_update_value(Grid_T *g, int i, int j, int n)
{
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    ASSERT_CHOICE(n);
    g->elts[i][j].val = n;
}
/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j)
{
    ASSERT_DIMENTIONS(i, j);
    return g.elts[i][j].val;
}

/* set (to 1) or clear (to 0) choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    ASSERT_CHOICE(n);
    if (g->elts[i][j].choices.num[n] == 0)
        g->elts[i][j].choices.count++;
    g->elts[i][j].choices.num[n] = 1;
}
void grid_clear_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    ASSERT_CHOICE(n);
    g->elts[i][j].choices.num[n] = 0;
}
/* true if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n)
{
    ASSERT_DIMENTIONS(i, j);
    ASSERT_CHOICE(n);
    return g.elts[i][j].choices.num[n] == 1;
}
/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    ASSERT_CHOICE(n);
    if (g->elts[i][j].choices.num[n] == 1)
        g->elts[i][j].choices.count--;
    grid_clear_choice(g, i, j, n);
}

/* return count, set (to 9), or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j)
{
    ASSERT_DIMENTIONS(i, j);
    return g.elts[i][j].choices.count;
}
void grid_set_count(Grid_T *g, int i, int j)
{
    int k;
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    g->elts[i][j].choices.count = 9;
    g->elts[i][j].choices.num[0] = 0;
    for (k = 1; k <= GRID_LENGTH; k++)
        g->elts[i][j].choices.num[k] = 1;
}
void grid_clear_count(Grid_T *g, int i, int j)
{
    int k;
    assert(g);
    ASSERT_DIMENTIONS(i, j);
    g->elts[i][j].choices.count = 0;
    for (k = 0; k <= GRID_LENGTH; k++)
        g->elts[i][j].choices.num[k] = 0;
}

/* return val, set (to 1), or clear (to 0) unique flag for g */
int grid_read_unique(Grid_T g)
{
    return g.unique;
}
void grid_set_unique(Grid_T *g)
{
    assert(g);
    g->unique = 1;
}
void grid_clear_unique(Grid_T *g)
{
    assert(g);
    g->unique = 0;
}
