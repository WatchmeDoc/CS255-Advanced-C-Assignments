Usage explanation:
sudoku		   -> Reads from stdin a puzzle and attempts to solve it. Also indicates if the puzzle given has a unique choice solution.
sudoku –c	   -> Reads from stdin a puzzle and testes its validity.
sudoku –g nelts –u -> Generates a new puzzle that has approximately nelts non-empty elements and prints it on stdout. -u Parameter
		      is optional to ensure puzzle has a unique choice solution.

Usage example:
sudoku -g 50 -u | sudoku | sudoku -c

The algorithm used is the one described on the assignment description, at least as much as I could understand it. Works pretty
good overall, still not perfect. I've tried another implementation of mine without following the assignment's steps and aside
from being much more efficient and faster, it also worked quite better. I'm excluding the other solution for purity purposes.