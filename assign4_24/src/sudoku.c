#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "grid.h"
#include "sudoku.h"
#include <time.h>

int main(int argc, char *argv[]) {
	int i,j;	
	Grid_T g;
	Choice_T c;

	if(argc == 1) {
		/* terminal: sudoku */
		
		/* reads a puzzle from stdin */
		g = sudoku_read();
		
		/* prints input puzzle into stderr stream */			
		sudoku_print(stderr, g);		
		
		/* solves puzzle */
		c.i = 0;
		c.j = 0;
		c.n = 1;
		g = sudoku_solve(g, c);			
				
		/* prints into stderr if puzzle has one, more than one solutions 
		 or no solutions at all */
		if(g.unique) {
			/* unique solution */
			fprintf(stderr, "Puzzle has a unique solution!\n");
		}else {			
			/* not unique solution */			
			if(!sudoku_is_correct(g)) {
				/* multiple solutions */
				fprintf(stderr, "Puzzle has multiple solutions!\n");
			}else {
				/* no solutions */
				fprintf(stderr, "Puzzle has no solutions!\n");
			}
		}
		
		/* prints into stdout last instance pf grid */
		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				printf("%d ", g.cell[i][j].choices[0]);
			}
			printf("\n");
		}
		printf("\n");	

	}else if((argc == 2) && (!strcmp("-c", argv[1]))) {
		/* terminal: sudoku -c */
		
		/* reads a puzzle from stdin */
		g = sudoku_read();
		
		/* prints input puzzle into stderr stream */			
		sudoku_print(stderr, g);			

		if(!sudoku_is_correct(g)) {
			/* sudoku is correct */
			fprintf(stderr, "Sudoku is correct!\n");
		}else  {
			/* sudoku is not correct */
			fprintf(stderr, "Sudoku is not correct!\n");
			if(sudoku_is_correct(g) == 1) {
				fprintf(stderr, "empty cell found!\n");
			}else {
				fprintf(stderr, "duplicate value found\n");
			}
		}

	}else if((argc == 4) && !(strcmp("-g", argv[1]) || strcmp("-u", argv[3]))) {
		if(atoi(argv[2])) {
			/* argv[2] is an integer != 0 */
			g = sudoku_generate(atoi(argv[2]), 1);
			for(i=0; i<9; i++) {
				for(j=0; j<9; j++) {
					printf("%d ", g.cell[i][j].choices[0]);
				}
				printf("\n");
			}
			printf("\n");
		}else {
			/* atoi returned 0. checks if argv[2] is 0 or not */
			i=0;		
			while(argv[2][i] != '\0') {
				if(!isdigit(argv[2][i])) {
					fprintf(stderr, "ERROR: nelts not int!\n\n");
					return -1;
				}
				i++;
			}
			g = sudoku_generate(0, 1);
			for(i=0; i<9; i++) {
				for(j=0; j<9; j++){
					printf("%d ", g.cell[i][j].choices[0]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
      
	return 0;
}



/*
 * sudoku_read(void) is responsible for receiving (as input from stdin) a
 * puzzle and creating a grid according to it. It initialises a two-
 * dimensional array with the values of the puzzle that has just been read
 * from stdin and afterwards, grid_init(Grid_T, int[9][9]) is called, with
 * the grid and the two-dimensional array to be given to it as its parameters.
 *
 * Parameters: -(void)
 * Return value: an instance of struct Grid_T, whose cell[9][9] is initialised
 *               with the values of the integer 9x9 two-dimensional array
 *
 */
Grid_T sudoku_read(void) {
        int i,j,v[9][9];
        int ch;
        Grid_T g;

        i=0;
        while(i<9) {
                j=0;
                while(j<9) {
                        if((scanf("%d",&ch)) != EOF){
                                if((ch!=32) && (ch!=10)) {
                                        v[i][j] = ch;
                                        j++;
                                }
                        }
                }
                i++;
        }

        g = grid_init(g, v);

        return g;
}


/*
 * sudoku_print(FILE*, Grid_T) is responsible for printing out (onto stdout) a
 * grid given to it as its second parameter, in the same format as it is
 * expected from procedure sudoku_read(void).
 *
 * Parameters: s is a pointer to a file stream of type FILE
 *             g is an instance of struct Grid_T (the puzzle of the sudoku
 *               game)
 * Return value: -(void)
 *
 */
void sudoku_print(FILE *s, Grid_T g) {
	int k1,k2;
	
	for(k1=0; k1<9; k1++) {
		for(k2=0; k2<9; k2++) {
			fprintf(s, "%d", g.cell[k1][k2].choices[0]);

			if(k2<8) {
				fprintf(s, " ");
			}
		}
		fprintf(s, "\n");
	}
}


/* 
 * sudoku_is_correct(Grid_T) checks whether the puzzle passed in as the
 * procedure's parameter is correct or not. If it is full and the elements 
 * are correct, it returns 0 (true). Otherwise, it returns 1 or -1 (false), if
 * there is at least one empty element or there is a duplicate correspondingly.  
 *
 * Parameters: g is an instance of struct Grid_T (the puzzle of the game)
 * Return value: 0 for true and 1/-1 for false 
 *
 */
int sudoku_is_correct(Grid_T g) {
	int i,j,k, subgrids[9][9];
	
	/* checks if grid is full or not */
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			if(!g.cell[i][j].choices[0]) {
				/* empty cell found */
				return 1;
			}
		}
	}

	/* grid is full, so now it's time to check if it is full correctly */
	/* checks columns */
	for(j=0; j<9; j++) {
		for(i=0; i<9; i++) {
			k = i+1;
			while(k<9) {
				if(g.cell[i][j].choices[0] == g.cell[k][j].choices[0]){
					/* double element found */
					return -1;
  				}
				k++;
			}	
		}
	}

/* ----------------------------- checks rows ---------------------------*/
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			k = j+1;
			while(k<9) {
				if(g.cell[i][j].choices[0] == g.cell[i][k].choices[0]) {
					/* double element found */
					return -1;
				}
				k++;
			}
		}
	}


/*---------------------- checks subgrids
 * --------------------------------------------------------*/
	/* step1 : each 3x3 subgrid becomes a row of 9x9 array called "subgrids" */	
	/* step 2: checks rows of array called "subgrids" */
	
	/* step1 : */
	k = 0;
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			subgrids[0][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=3; i<6; i++) {
		for(j=0; j<3; j++) {
			subgrids[1][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=6; i<9; i++) {
		for(j=0; j<3; j++) {
			subgrids[2][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=0; i<3; i++) {
		for(j=3; j<6; j++) {
			subgrids[3][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=3; i<6; i++) {
		for(j=3; j<6; j++) {
			subgrids[4][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=6; i<9; i++) {
		for(j=3; j<6; j++) {
			subgrids[5][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=0; i<3; i++) {
		for(j=6; j<9; j++) {
			subgrids[6][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=3; i<6; i++) {
		for(j=6; j<9; j++) {
			subgrids[7][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	k = 0;
	for(i=6; i<9; i++) {
		for(j=6; j<9; j++) {
			subgrids[8][k] = g.cell[i][j].choices[0];
			k++;
		}
	}

	/* -------------- step2 : ------------------- */
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			k = j+1;
			while(k<9) {
				if(subgrids[i][j] == subgrids[i][k]) {
					/* double element found */
					return -1;
				}
				k++;
			}
		}
	}

	return 0;

}

/*
 * sudoku_generate(int, int) generates a solvable sudoku puzzle, with "nelts"
 * (param. 1) empty cells and "unique" (param. 2) solution/s. If that is not
 * possible , it returns a pre-defined solvable sudoku puzzle with
 * "unique" (param. 2) solution/s.
 *
 * Parameters: nelts is the number of empty elements the grid that is to be
 * 	       returned is going to have
 *	       unique equals to 1 or 0, if the sudoku has a unique solution or
 *	              not correspondigly
 * Return value: the grid / sudoku puzzle generated (instance of struct Grid_T) 
 *
 */
Grid_T sudoku_generate(int nelts, int unique) {
	int v[9][9],i,j,x,y;
	Grid_T g;
        Choice_T c;

	/* pre-defined puzzle with a unique solution, in case solve fails 10 times in a row */
	int sud_un_sol[9][9] = {
		{5,3,4,6,7,8,9,1,2},
		{6,7,2,1,9,5,3,4,8},
		{1,9,8,3,4,2,5,6,7},
		{8,5,9,7,6,1,4,2,3},
		{4,2,6,8,5,3,7,9,1},
		{7,1,3,9,2,4,8,5,6},
		{9,6,1,5,3,7,2,8,4},
		{2,8,7,4,1,9,6,3,5},
		{3,4,5,2,8,6,1,7,9}
	};
	
	/* pre-defined puzzle with multiple solutions, in case solve fails 10 times in a row */
	int sud_mul_sol[9][9] = {
		{5,3,4,6,7,8,9,1,2},
		{6,7,2,1,9,5,3,4,8},
		{1,9,8,3,4,2,5,6,7},
		{8,5,9,7,6,1,4,2,3},
		{4,2,6,8,5,3,7,9,1},
		{7,1,3,9,2,4,8,5,6},
		{9,6,1,5,3,7,2,8,4},
		{2,8,7,4,1,9,6,3,5},
		{3,4,5,2,8,6,1,7,9}
	};

	/* generates a 9x9 array with 0s */
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			v[i][j] = 0;
		}
	}

	/* a grid is generated, with all elements equal to 0 and all of its choices equal to 1 */
	g = grid_init(g, v);

	for(i=0; i<10; i++) {
		/* initialise c with a random choice for a randomly chosen cell */
		c.i = 0;
		c.j = 0;
		c.n = 0;
		c = grid_iterate(g, c);
	
		/* calls sudoku_solve */
		g = sudoku_solve(g, c);

		if(!sudoku_is_correct(g)) {
			/* sudoku is correct */
			/* 1) copies puzzle into v (9x9 int array) */
			/* 2) puts 0 into nelt random positions of array v */
			/* 3) initialises grid g with array v and returns g */

			/* step 1: */
			for(i=0; i<9; i++) {
				for(j=0; j<9; j++) {
					v[i][j] = g.cell[i][j].choices[0];
				}
			}

			/* we put nelt zero elements (randomly chosen) into two-dimensional array v */
			/* step 2: */
			j = 0;
			while(j<nelts) {
				x = rand() % 9;
				y = rand() % 9;
				if(v[x][y]) {
					/* v[x][y] is not 0 */
					v[x][y] = 0;
					j++;
				}
			}
			
			/* step 3: */			
			g = grid_init(g, v);

			return g;	
		}
	}	

	/* sudoku was not solved, so we are going to use a pre-defined puzzle */
	if(unique) {
		/* uses pre-defined puzzle with the unique solution */
		g = grid_init(g, sud_un_sol);
	}else {
		/* uses pre-defined puzzle with multiple solutions */
		g = grid_init(g, sud_mul_sol);
	}
	
	return g; 	

}


Grid_T sudoku_solve(Grid_T g, Choice_T c) {
	int flag, i, j, k;
	/* Grid_T g; */
	Choice_T choice;

	if(!(c.i || c.j || c.n)) {
		return g;
	} 
	
	g = grid_update(g, c);

	flag = 1;
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			if(!g.cell[i][j].choices[0]) {
				/* cell[i][j] is empty */
				/* checks if number of choices is 1 */
				if(g.cell[i][j].count != 1) {
					/* number of choices is not only 1 */
					flag = 0;
				}
			}
		}
	}
	
	/* checks flag. if flag = 1 ---> unique solution. If flag = 0 ----> more than one solutions */
	if(flag) {
		/* unique solution */	
		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				if(!g.cell[i][j].choices[0]) {
					choice.i = i;
					choice.j = j;
					choice = grid_iterate(g, choice);
					g = grid_update(g, choice);	 		
				}		
			}
		}
		return g;
	}else {
		/* not unique solution */
		/* 1) fills in the unique choice empty cells */	
		/* 2) recursively calls sudoku_solve() */
		
		/* step 1: */	
		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				if(!g.cell[i][j].choices[0] && g.cell[i][j].count==1) {
					choice.i = i;
					choice.j = j;
					choice = grid_iterate(g, choice);
					g = grid_update(g, choice);
				}		
			}
		}

		/* step 2: */
		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				if(!g.cell[i][j].choices[0]) {
					for(k=1; k<10; k++) {
						if(g.cell[i][j].choices[k]) {
							/*choice for empty cell[i][j]exists*/
							choice.i = i;
							choice.j = j;
							choice.n = k;
							g = sudoku_solve(g, choice);
						
							if(!sudoku_is_correct(g)) {
								return g;
							}	
						}
					}
				}
			}
		}
	}
}
			

