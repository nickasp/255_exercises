/************************ SYMTABLEHASH.C ***************** assignment_3
 * ******************* Aspridis Nikolaos ******************* csd5178
 * *****************/

#include "symtable.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define HASH_MULTIPLIER 65599

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey);



/*
 * ADT Symbol Table
*/
struct SymTable {
	struct binding **header;
	unsigned int num_of_bindings;
	unsigned int num_of_backets;	
};



/* Each SymTable consists of bindigs. Each one of them is of type "struct
 * binding".
*/
struct binding {
	const char *key;
	const void *value;
	struct binding *next;
};




/* 
 * SymTable_new(void) creates a new , empty (without any binding) SymTable,
 * that fits up to 509 bindings totally. More precisely, memory for 509 bindings is
 * allocated, with "header" to be pointing onto the 1st one of them. Each
 * binding's fields are initialised with null.
 *
 * Return value: a pointer to the newly created SymTable.
 * 
 **/
SymTable_T SymTable_new(void) {
	SymTable_T tmp;
	int i;
 
	tmp = (SymTable_T)malloc(sizeof(struct SymTable));
	assert(tmp);

	tmp->num_of_bindings = 0u;
	
	tmp->header = (struct binding **)malloc(509 * sizeof(struct binding *));
	assert(tmp->header);
	
	for(i=0; i<509; i++) {
		*((tmp->header) + i) = NULL;
	}

	tmp->num_of_backets = 509u;

	return tmp;
}


/*
 * SymTable_free(SymTable_T oSymTable) is responsible for releasing all the
 * memory used by the SymTable that oSymTable is referring to. First of all,
 * it checks whether oSymTable is null. If so, it returns. Otherwise, it
 * checks if oSymTable->header (the header pointer to the hash table) is null.
 * If so, again it simply returns. If oSymTable->header is not null, though, 
 * it deallocates the memory used for the storage of the hash table and sets
 * oSymTable->header to null.
 *
 * Parameters: oSymTable (of type SymTable_T) is a pointer to an instance of struct SymTable
 * Return value: - (void)
 *
 **/
void SymTable_free(SymTable_T oSymTable) {
	size_t i;
	struct binding *tmp, *tmp_helper;
	
	if(oSymTable) {
	/*======if oSymTable != NULL==============*/
		for(i=0; i<(oSymTable->num_of_backets); i++) {
			if(*(oSymTable->header + i)) {
				/*chain no. i is not "empty"*/
				tmp = *(oSymTable->header + i);
				tmp_helper = NULL;
				while(tmp) {
					tmp_helper = tmp;
					tmp = tmp->next;
					free(tmp_helper);
				}
				tmp_helper = NULL;
				*(oSymTable->header + i) = NULL;
			}
			/*chain no. i is "empty" (null pointer to struct binding), so do nothing and check the next one*/			
		}		
		oSymTable->num_of_bindings = 0u;
	}
	/*if oSymTable == NULL, then do nothing and return*/
}



/*
 * SymTable_getLength(SymTable_T oSymTable) procedure returns how many
 * bindings there are into the SymTable right now. It actually returns the
 * value of SymTable's field called "num_of_bindings", that is constantly
 * updated, so as to keep track of the total number of bindings.
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 * Checked runtime errors : oSymTable to be null
 * Return value: the number (unsigned int) of bindings that can be found (at that) point into
 * 		 the instance of struct SymTable 
 * 
 **/
unsigned int SymTable_getLength(SymTable_T oSymTable) {
	assert(oSymTable);
	return (oSymTable->num_of_bindings);	
}



/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey) {
	size_t ui;
	unsigned int uiHash;

	uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++) {
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	}

	return uiHash;
}


/*
 * Procedure named "SymTable_put" is responsible for checking if there is a
 * binding with the same key as the one provided as "pcKey" parameter. If so,
 * it does nothing and returns 0 (FALSE). If there is no such a binding,
 * instead, it is added into the hash table of the SymTable and returns 1
 * (TRUE). New binding's key and value are the same with the ones provided as
 * parameter "pcKey" and "pvValue" respectively. 
 *
 * Parameters: oSymtable is a pointer to an instance of struct SymTable
 *	       pcKey is a pointer to characters (to a string actually), that
 *	       	     is going to  be used as the key for the new binding
 *	       pvValue is a pointer to the value (it could be of any type)
 *	             that is going to be used as the value corresponding to 
 *                   the key used for the new binding
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value: 0 for false and 1 for true. False means that a binding with a
 * 		     key same as pcKey was found, so no new binding was
 *                   added to the hash table, while true means that no
 * 		     such a binding was found and, as a result, a new one was
 *                   added to the hash table.
 *		
 **/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
	unsigned int hash, i;	
	struct binding *tmp, *tmp_helper;	
	char *ptr;

	assert(oSymTable);
	assert(pcKey);		

/*	
	i=0u;
	while(i<num_of_backets && *(oSymTable->header + i)) 
		i++;
	if(i == num_of_backets) { 				
		then there is need for resizing the hash table and reallocating the bindings into it



*/
	


	hash = SymTable_hash(pcKey) % (oSymTable->num_of_backets);
	tmp = *(oSymTable->header + hash);
	tmp_helper = NULL;

	while(tmp && strcmp(tmp->key, pcKey)) {
		if(!(tmp->next))
			tmp_helper = tmp;
		tmp = tmp->next;
	}
	if(!tmp) {
		/*pcKey was not found into chain of number hash*/
		
		/*memory is allocated for the new binding*/
		tmp = (struct binding *)malloc(sizeof(struct binding));
		assert(tmp);
		
		/*memory allocation for the storage*/
		ptr = (char *)malloc(strlen(pcKey)+1);
		
		/*pcKey is copied on ptr*/
		i = 0u;
		while(*(pcKey + i)) {
			*(ptr + i) = *(pcKey + i);
			i++;
		}
		*(ptr + i) = '\0';
		
		/*binding's fields are initialised*/
		tmp->key = ptr;
		tmp->value = pvValue;
		tmp->next = NULL;
		
		if(tmp_helper) {
			/*new binding will be the last one in the chain (not the first one)*/
			tmp_helper->next = tmp;
		}else {
			/*new binding will be the first one into the chain*/
			*(oSymTable->header + hash) = tmp;
		}
		
		oSymTable->num_of_bindings += 1;		

		return 1;
	
	}else {
		/*pcKey was found into chain of number hash*/
		/*nothing happens and procedure returns 0 (FALSE)*/
		return 0;
	}
}




/*
 * SymTable_remove(SymTable_T oSymTable, const char *pcKey) is responsible for
 * finding the binding whose key is the same as pcKey into the hash table of
 * SymTable (if there is such a binding in there) and throwing it away. In
 * case everything goes as expected, it returns 1 (TRUE). If the binding is
 * not found into the hash table, the last one does not change and the
 * procedure returns 0 (FALSE).
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pcKey is a pointer to characters (a pointer to a string
 *                   actually) that is going to be used as the key that the
 *                   procedure will look for, into the hash table
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
	unsigned int hash;
	struct binding *tmp, *tmp_helper;

	assert(oSymTable);
	assert(pcKey);

	hash = SymTable_hash(pcKey) % (oSymTable->num_of_backets);
	
	tmp_helper = NULL;
	tmp = *(oSymTable->header + hash);
	while(tmp && strcmp(tmp->key, pcKey)) {
		tmp_helper = tmp;
		tmp = tmp->next;
	}
	if(!tmp) {
		/*pcKey was not found into chain of number hash*/
		/*nothing happens and procedure returns 0 (FALSE)*/
		return 0;
	}else {
		/*pcKey was found into chain of number hash*/
		/*binding whose key is the same as pcKey is deleted*/
		if(!tmp_helper) {
			/*pcKey was found into the first binding of the chain of number hash*/
			*(oSymTable->header + hash) = tmp->next;
			free(tmp);
			tmp = NULL;
		}else {
			/*pcKey was not found into the first binding of the chain of number hash*/			
			tmp_helper->next = tmp->next;
			free(tmp);
			tmp = NULL;
		}

		oSymTable->num_of_bindings -= 1;

		/*procedure returns 1 (TRUE)*/
		return 1;
	}
}


/*
 * SymTable_contains(SymTable_T oSymTable, const char *pcKey) checks if there
 * is a binding, into the hash table, whose key is the same as pcKey. If
 * that's the case, it returns 1(TRUE). Otherwise, it returns 0(FALSE).
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pcKey is a pointer to characters (to a string actually) that
 *                   are going to be used as the key that the procedure will
 *                   look for, into the hash table       
 * Checked runtime errors : oSymTable or pcKey to be null     
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
	unsigned int hash;
	struct binding *tmp;

	assert(oSymTable);
	assert(pcKey);

	hash = SymTable_hash(pcKey) % (oSymTable->num_of_backets);

	
	tmp = *(oSymTable->header + hash); 	/*tmp points where pointer to "chain" number 'hash' points, too*/
	while(tmp && strcmp(tmp->key, pcKey)) {
		/*traverse the list until tmp==NULL or tmp->key equals pcKey*/
		tmp = tmp->next;
	}
	if(!tmp) {
		/*pcKey was not found into chain number 'hash'. Chain does not change and procedure returns 0 (FALSE)*/
		return 0;
	}else {
		/*pcKey was found into "chain" number 'hash'. Chain does not change and procedure returns 1 (TRUE)*/
		return 1;
	}
}


/*
 * SymTable_get(SymTable_T oSymTable, const char *pcKey) looks for a binding
 * whose key is the same as pcKey into the hash table of SymTable. If it
 * finds one, it returns the address of its value. Otherwise, it returns null.
 * 
 * Warning : return discards ‘const’ qualifier from pointer target type 
 * Parameters : oSymTable is a pointer to an instance of struct SymTable
 * 		pcKey is a pointer to characters (to a string, actually) that
 * 		      are going to be used as the key that the procedure will
 * 		      look for, into the SymTable 
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value : the address of binding's value (success), or null (failure)
 *
 **/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
	unsigned int hash;
	struct binding *tmp;

	assert(oSymTable);
	assert(pcKey);

	hash = SymTable_hash(pcKey) % (oSymTable->num_of_backets);
	tmp = *(oSymTable->header + hash);
	while(tmp && strcmp(tmp->key, pcKey))
		tmp = tmp->next;
	if(!tmp) {
		/*pcKey was not found into chain of number hash*/
		/*procedure returns null*/
		return NULL;
	}else {
		/*pcKey was found into chain of number hash*/
		/*procedure returns the address of binding's value*/
		return (void *)tmp->value;
	} 		
}



/*
 * SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void
 * *pvValue, void *pvExtra), const void *pvExtra) is responsible for applying
 * function pointed to by pfApply on each binding of the hash table. Function
 * pointed to by pfApply takes binding's key, binding's value and data pointed to by
 * pvExtra as arguments for its call on each binding.
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pfApply is a pointer to a function that returns void and takes
 *                     a pointer to characters (string) and two pointers to 
 *                     void as its parameters
 *	       pvExtra is a pointer to void, that is going to be used as
 *	               pfApply's third parameter on each of its calls	       
 * Checked runtime errors : oSymTable or pfApply to be null
 * Warning :  passing arguments 2 and 3 of ‘pfApply’ discard ‘const’ qualifier from
 * 	      pointer target type [-Wdiscarded-qualifiers] 
 * Return value : -(void)
 *
 **/
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey,
	void *pvValue, void *pvExtra), const void *pvExtra) {
	
	int i;
	struct binding *tmp;

	assert(oSymTable);
	assert(*pfApply);

	for(i=0; i<(oSymTable->num_of_backets); i++) {
		tmp = *(oSymTable->header + i);
		while(tmp) {
			pfApply(tmp->key, (void *)tmp->value, (void *)pvExtra);
			tmp = tmp->next;
		}
	}
}




/*
 * SymTable_print is a procedure of my own that is supposed to print the key
 * and the value of each of the bindings that "exist" into the hash table. The
 * reason I made this procedure is to be able to check any time I choose to
 * the stored data into the hash table.
 *  
 * Checked runtime errors: oSymTable to be null
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 * Return value: -(void)
 *
 **/
void SymTable_print(SymTable_T oSymTable) {
	struct binding *tmp;
	size_t i;

	assert(oSymTable);

	if(!(oSymTable->num_of_bindings)) {
		printf("hash table is empty!\n\n");
		return;
	}	

	for(i=0; i<(oSymTable->num_of_backets); i++) {
		tmp = *(oSymTable->header + i);
		while(tmp) {
			printf("%s %u\n", tmp->key, *((unsigned int *)(tmp->value)));
			tmp = tmp->next;
		}
	}
	printf("\n\n");
}





