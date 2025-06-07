#include "symtable.h"
#include <assert.h>
#include <stdio.h>

void print(const char *key, void *pvValue, void *pvExtra); 

int main(void){
	SymTable_T s;
	unsigned int x, age_of_Nikos, age_of_Nikoletta, age_of_Giannhs, age_of_Nikos_2;	
	
/*===== construction of a new, empty symbol table (SymTable_new() procedure is checked) =============================*/
	
	s = SymTable_new();
	assert(s);	

/*===== checks if SymTable_getLength will return 0 ===========================================================*/
	
	x = SymTable_getLength(s);
	printf("SymTable's length: %u\n\n",x);
	assert(!x);

/*===== checks SymTable_put and SymTable_get ========================================================================*/
	
	/*bindings that are to be added : {"Nikos",20}, {"Nikoletta",21}, {"Giannhs", 24}
	 *
	 **/
	age_of_Nikos = 20;
	x = SymTable_put(s, "Nikos", &age_of_Nikos);
	assert(x);				/*checks that x == 1 (TRUE)*/
	printf("ok1\n\n");

	age_of_Nikoletta = 21;
	x = SymTable_put(s, "Nikoletta", &age_of_Nikoletta);
	assert(x);				/*checks that x == 1 (TRUE)*/
	printf("ok2\n\n");

	age_of_Giannhs = 24;
	x = SymTable_put(s, "Giannhs", &age_of_Giannhs);
	assert(x);				/*checks that x == 1 (TRUE)*/	
	printf("ok3\n\n");

	age_of_Nikos_2 = 18;
	x = SymTable_put(s, "Nikos", &age_of_Nikos_2);
	assert(!x);				/*checks that x == 0 (FALSE)*/
	printf("ok4\n\n");

	printf("SymTable's length: %u\n\n", SymTable_getLength(s));

	printf("binding no. 1: %s %u\n","Nikos",*((unsigned int *)SymTable_get(s, "Nikos")));
	printf("binding no. 2: %s %u\n","Nikoletta", *((unsigned int *)SymTable_get(s, "Nikoletta")));	
	printf("binding no. 3: %s %u\n", "Giannhs", *((unsigned int *)SymTable_get(s, "Giannhs")));
	printf("ok5\n\n");


	/*expected output: Nikos 20
			   Nikoletta 21
			   Giannhs 24		*/

/*===== checks SymTable_contains ===================================================================================*/	
	printf("%u\n\n", SymTable_contains(s, "Alexandros"));  /*expected output : 0 (FALSE)*/
	printf("%u\n\n", SymTable_contains(s, "Giannhs"));     /*expected output : 1 (TRUE)*/
	
	SymTable_print(s);
	/*expected output : Nikos 20\nNikoletta 21\nGiannhs 24*/
	
/*===== checks SymTable_remove =================================================================================*/
	assert(SymTable_remove(s, "Nikos"));	/*checks that function returned 1 (TRUE)*/
				/*if so, {"Nikos",20} was supposedly removed from SymTable*/
	
	assert(!(SymTable_remove(s, "Alexandros"))); /*checks that function returned 0 (FALSE)*/
	
	SymTable_print(s);
	/*expected output : Nikoletta Giannhs*/
	
	assert(SymTable_remove(s, "Giannhs"));		/*checks that function returned 1 (TRUE)*/
	
	SymTable_print(s);
	/*expected output : Nikoletta */

	assert(SymTable_remove(s, "Nikoletta"));	/*checks that function returned 1 (TRUE)*/
	
	SymTable_print(s);
	/*expected output : no bindings!*/

/*===== checks SymTable_free ======================================================================================*/	
	assert(SymTable_put(s, "Nikos", &age_of_Nikos));	/*checks that SymTable_put() returns 1 (TRUE) on all three calls*/
	assert(SymTable_put(s, "Nikoletta", &age_of_Nikoletta));
	assert(SymTable_put(s, "Giannhs", &age_of_Giannhs));
					
	SymTable_print(s); 
	/*expected output : Nikos, Nikoletta, Giannhs*/

	SymTable_free(s);

	SymTable_print(s);
	/*expected output : no bindings!*/

/*===== checks SymTable_map ========================================================================*/
	x = SymTable_put(s, "Nikos", &age_of_Nikos);
	x = SymTable_put(s, "Nikoletta", &age_of_Nikoletta);	
	x = SymTable_put(s, "Giannhs", &age_of_Giannhs);

	x = 15;
	SymTable_map(s, &print, &x);




	return 0;
}




void print(const char *key, void *pvValue, void *pvExtra) {
	printf("%s %u %u\n", key, *((unsigned int *)pvValue), *((unsigned int *)pvExtra));
}

