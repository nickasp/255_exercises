/************************************************
 * * grid.c (implementation of grid.h) *        *
 *						*
 *						*
 * Aspridis Nikolaos csd5178 			*
 *						*
 * assignment 4, hy255, 2023-2024		*
 *						*
 ************************************************/


#include "grid.h"
#include <stdlib.h>
#include <time.h>

/*
 * grid_init(Grid_T, int[9][9]) is a procedure that "creates" a grid layout
 * (1st parameter) by assigning to each of its cells the unsigned integer 
 * (between 0 and 9) found into the corresponding position of the two-dimensional array 
 * (2nd parameter), as well as finds and sets the collection of possible values
 * (this time integers between 1 and 9) that could be used to fill the current "empty"
 * cells (those whose temporary value is no. 0). 
 *
 * Parameters: g is an instance of struct Grid_T (a puzzle for the sudocku game) 
 * 	       v is a two-dimensional integer array, with 81 (9x9) positions
 * 	         in total
 * Return value: an instance of struct Grid_T 
 *
 */
Grid_T grid_init(Grid_T g, int v[9][9]) {
	int i,j,k,k1,k2;

/*-------firstly, we initialise choices[0] of each cell with v[i][j] and
 * choices[k] (with 0<k<10) either with 1, or eith 0--------------------------*/
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			g.cell[i][j].count = 0;

			g.cell[i][j].choices[0] = v[i][j];	/*cell[i][j]
is assigned v[i][j]'s value*/
			if(!v[i][j]) {
				/*cell is "empty", so we have to check for
 * possible values. Concept is that I will initialise all choices[k], for 0<k<10,
 * with no. 1 so that afterwards, for each value (from 1 to 9) found,
 * choices[k] to be assigned with no. 0*/
				for(k=1; k<10; k++) {
					g.cell[i][j].choices[k] = 1;
				}	
			}else {
				/*cell is not "empty", so no other possible values*/
				for(k=1; k<10; k++) {
					g.cell[i][j].choices[k] = 0;
				}
			}
		}
	}

/*--------------- now , for the cells that contain no. 0, we have to
 * find all the possible choices so as to initialise choices[k] (for 0<k<10) -----------------------*/
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {

			if(!g.cell[i][j].choices[0]) {
				/*choices[0] equals 0, so we have to look for
 * the possible values*/
				/*checks cell[k][j], for 0<k<9 (lines)*/
				for(k=0; k<9; k++) {
					g.cell[i][j].choices[g.cell[k][j].choices[0]] = 0;
				}
				
				/*checks cell[i][k], for 0<=k<9 (columns)*/
				for(k=0; k<9; k++) {
					g.cell[i][j].choices[g.cell[i][k].choices[0]] = 0;
				}
				

				/*
				 * Checks the 3x3 squares  
				*/
				switch(j) {
					case 0:
					case 1:
					case 2:
						switch(i) {
							case 0:
							case 1:
							case 2:
								for(k1=0; k1<3; k1++){
									for(k2=0; k2<3; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;		
							case 3:
							case 4:
							case 5:
								for(k1=3; k1<6; k1++){
									for(k2=0; k2<3; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
							case 6:
							case 7:
							case 8:
								for(k1=6; k1<9; k1++){
									for(k2=0; k2<3; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
						}

						break;	
				
					case 3:
					case 4:
					case 5:	
						switch(i) {
							case 0:
							case 1:
							case 2:
								for(k1=0; k1<3; k1++){
									for(k2=3; k2<6; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;		
							case 3:
							case 4:
							case 5:
								for(k1=3; k1<6; k1++){
									for(k2=3; k2<6; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
							case 6:
							case 7:
							case 8:
								for(k1=6; k1<9; k1++){
									for(k2=3; k2<6; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
						}

						break;

					case 6:
					case 7:
					case 8:	
						switch(i) {
							case 0:
							case 1:
							case 2:
								for(k1=0; k1<3; k1++){
									for(k2=6; k2<9; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;		
							case 3:
							case 4:
							case 5:
								for(k1=3; k1<6; k1++){
									for(k2=6; k2<9; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
							case 6:
							case 7:
							case 8:
								for(k1=6; k1<9; k1++){
									for(k2=6; k2<9; k2++){
										g.cell[i][j].choices[g.cell[k1][k2].choices[0]] = 0;	
									}
								}
								break;
						}
						
						break;
				}

				/* counts the possible choices and initialises count */
				for(k=1; k<10; k++) {
					if(g.cell[i][j].choices[k]) {
						g.cell[i][j].count++;
					}
				}
			}
		}
	}
	
	return g;
}		




/*
 * grid_iterate(Grid_T, Choice_T) is a procedure that returns a choice of
 * possible value for a particular cell of the grid. Firstly, it traverses
 * the grid until it finds a zeroed element (cell == 0), with a unique choice.
 * If it does not find anything like that, it searches for the first zeroed
 * element it encounters. When that is found, it randomly chooses one of its 
 * possible choices of integers between 1 and 9 and returns it. If there is at
 * least an empty cell with no choices, it returns {0,0,0}. Also, if there is
 * no empty cell, it returns {0,0,0} as well. IMPORTANT NOTICE: Searching
 * begins from the coordinates Choice_T parameter contains! 
 *
 * Parameters: g is an instance of struct Grid_T (a puzzle for the sudocku
 *               game)
 *             t is an instance of struct Choice_T (a choice between the
 *               possible values for a particular cell into the grid)
 * Return value: instance t of struct Choice_T
 *
 */
Choice_T grid_iterate(Grid_T g, Choice_T t) {
	int n,k1,k2;	

	srand(time(NULL));
	
	n = (rand() % 9) + 1;	/* generates a pseudorandom integer between 1 and 9 */

	/* traverses the grid until it finds a zero element (cell == 0) with a unique solution (count )*/
	for(k1=t.i; k1<9; k1++) {
		for(k2=t.j; k2<9; k2++) {
			if(!g.cell[k1][k2].choices[0] && g.cell[k1][k2].count==1) {
				/* cell equal to zero , with unique solution, found */			
				/* initialises t's fields appropriately and returns */
				t.i = k1;
				t.j = k2;
				n=1;
				while(n<10) {
					if(g.cell[k1][k2].choices[n]) {
						/* n is the unique choice for that cell */
						t.n = n;
						break;
					}
					n++;
				}	

				return t;
			}
		}
	}

	/* traverses the grid until it finds a zero element (cell == 0) , that obviously will not have a unique solution */
	for(k1=t.i; k1<9; k1++) {
		for(k2=t.j; k2<9; k2++) {
			if(!g.cell[k1][k2].choices[0]) {
				/* cell equal to zero found */

				/* if count == 0, then : error!--> no possible choices : returns {0,0,0} */
				if(!g.cell[k1][k2].count) {
					t.i = 0;
					t.j = 0;
					t.n = 0;
					
					return t;
				}

				t.i = k1;
				t.j = k2;
							
				while(!g.cell[k1][k2].choices[n]) {
					/* we need to check another n value for possible choice */
					n = (rand() % 9) + 1;	/* generates another pseudorandom number*/
				}

				t.n = n;

				return t;
			}
		}
	}

	/* no choice is left! t's fields are initialised and procedure returns (0,0,0) */
	t.i = 0;
	t.j = 0;
	t.n = 0;

	return t;

/*=============================================================================================================================*/

	
}



/*
 * grid_update(Grid_T, Choice_T) is a procedure that is responsible for
 * assigning t.n to cell[t.i][t.j], as well as elliminating value t.n from 
 * the collection of possible choices for all the other cells of the same
 * line, column and 3x3 sub-grid.
 *
 * Parameters: g is an instance of struct Grid_T (a puzzle for sudocku game)
 *             t is an instance of struct Choice_T (the selected choice for
 *               cell[t.i][t.j])
 * Return value: g, after being modified appropriately
 *
 */
Grid_T grid_update(Grid_T g, Choice_T t) {
	int k,k1,k2;
	
	/* n is assigned to cell[i][j] and all its possible choices are zeroed */
	g.cell[t.i][t.j].choices[0] = t.n;
	for(k=1; k<10; k++){
		g.cell[t.i][t.j].choices[k] = 0;
	}
	g.cell[t.i][t.j].count = 0;	

	/*checks cell[k][t.j], for 0<=k<9 (lines)*/
	for(k=0; k<9; k++) {
		if(g.cell[k][t.j].choices[t.n]) {
			g.cell[k][t.j].choices[t.n] = 0;
			g.cell[k][t.j].count--;
		}
	}
				
	/*checks cell[t.i][k], for 0<k<10 (columns)*/
	for(k=0; k<9; k++) {
		if(g.cell[t.i][k].choices[t.n]) {
			g.cell[t.i][k].choices[t.n] = 0;
			g.cell[t.i][k].count--;
		}
	}
				

	/*
	 * Checks the 3x3 squares  
	*/
	switch(t.j) {
		case 0:
		case 1:
		case 2:
			switch(t.i) {
				case 0:
				case 1:
				case 2:
					for(k1=0; k1<3; k1++){
						for(k2=0; k2<3; k2++){
							if(g.cell[k1][k2].choices[t.n]){
								g.cell[k1][k2].choices[t.n] = 0;
	                                                	g.cell[k1][k2].count--;
							}
						}
					}
					break;		
				
				case 3:
				case 4:
				case 5:
					for(k1=3; k1<6; k1++){
						for(k2=0; k2<3; k2++){
							if(g.cell[k1][k2].choices[t.n]){
								g.cell[k1][k2].choices[t.n] = 0;
								g.cell[k1][k2].count--;	
							}
						}
					}
					break;

				case 6:
				case 7:
				case 8:
					for(k1=6; k1<9; k1++){
						for(k2=0; k2<3; k2++){
							if(g.cell[k1][k2].choices[t.n]){
								g.cell[k1][k2].choices[t.n] = 0;
								g.cell[k1][k2].count--;	
							}
						}
					}
					break;
			}

			break;	
				
		case 3:
		case 4:
		case 5:	
			switch(t.i) {
				case 0:
				case 1:
				case 2:
					for(k1=0; k1<3; k1++){
						for(k2=3; k2<6; k2++){
							if(g.cell[k1][k2].choices[t.n]) {
								g.cell[k1][k2].choices[t.n] = 0;
								g.cell[k1][k2].count--;
							}	
						}
					}
					break;	
	
					case 3:
					case 4:
					case 5:
						for(k1=3; k1<6; k1++){
							for(k2=3; k2<6; k2++){
								if(g.cell[k1][k2].choices[t.n]) {
									g.cell[k1][k2].choices[t.n] = 0;	
									g.cell[k1][k2].count--;
								}
							}
						}
						break;

					case 6:
					case 7:
					case 8:
						for(k1=6; k1<9; k1++){
							for(k2=3; k2<6; k2++){
								if(g.cell[k1][k2].choices[t.n]) {
									g.cell[k1][k2].choices[t.n] = 0;
									g.cell[k1][k2].count--;	
								}
							}
						}
						break;
			}

			break;

		case 6:
		case 7:
		case 8:	
			switch(t.i) {
				case 0:
				case 1:
				case 2:
					for(k1=0; k1<3; k1++){
						for(k2=6; k2<9; k2++){
							if(g.cell[k1][k2].choices[t.n]) {
								g.cell[k1][k2].choices[t.n] = 0;
								g.cell[k1][k2].count--;	
							}
						}
					}
					break;		

				case 3:
				case 4:
				case 5:
					for(k1=3; k1<6; k1++){
						for(k2=6; k2<9; k2++){
							if(g.cell[k1][k2].choices[t.n]) {
								g.cell[k1][k2].choices[t.n] = 0;	
								g.cell[k1][k2].count--;
							}
						}
					}
					break;

				case 6:
				case 7:
				case 8:
					for(k1=6; k1<9; k1++){
						for(k2=6; k2<9; k2++){
							if(g.cell[k1][k2].choices[t.n]) {
								g.cell[k1][k2].choices[t.n] = 0;
								g.cell[k1][k2].count--;
							}	
						}
					}
					break;
			}
						
			break;
	}

	return g;

}



/* grid_unique(Grid_T) is a procedure responsible for indicating if g (our
 * puzzle) has a unique solution or not. 
 *
 * Parameters: g is an instance of struct Grid_T (the puzzle of a sudocku game)
 * Return value: an integer indicating if there is a unique solution or not
 *
 */
int grid_unique(Grid_T g) {
	return g.unique;
}



/* grid_clear_unique(Grid_T) is responsible for setting grid's field named
 * "unique" with no. 0
 *
 * Parameters: g is an instance of struct Grid_T (the puzzle of a sudocku game)
 * Return value: an instance of struct Grid_T (g, after being modified)
 *
 */
Grid_T grid_clear_unique(Grid_T g) {
	g.unique = 0;
	return g;
}


/* grid_exist_unique(Grid_T) is responsible for returning the coordinates and
 * the possible value for the first empty cell with a unique possible value it
 * encounters into the grid.
 *
 * Parameters: g is an instance of struct Grid_T (the puzzle of a sudocku game)
 * Return value: an instance of Choice_T (the coordinates and the unique
 * 		 possible value n of the cell with the unique possible value).
 * 		 If no cell with unique possible value is encountered, (0,0,0)
 * 		 is returned. 
 *
 */
Choice_T grid_exist_unique(Grid_T g) {
	int i,j,k;	
	Choice_T s;

	s.i = 0;
	s.j = 0;
	s.n = 0;

	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			if(g.cell[i][j].count == 1) {
				s.i = i;
				s.j = j;
				for(k=1; k<10; k++) {
					if(g.cell[i][j].choices[k]) {
						s.n = k;
						break;
					}		
				}						
			} 			
		}
	}

	return s;

}


/*
 * grid_read_value(Grid_T, Choice_T) returns an instance of struct Choice_T,
 * that contains the coordinates of the given cell from grid g and its current value
 *
 * Parameters: g is an instance of struct Grid_T (the puzzle of a sudoku game)
 * 	       c is an instance of struct Choice_T 
 * Return value:  c, after it has been assigned the value cell[c.i][c.j]
 *                contains
 *
 */
Choice_T grid_read_value(Grid_T g, Choice_T c) {

	c.n = g.cell[c.i][c.j].choices[0];
	
	return c;
}





