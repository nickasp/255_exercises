/********************* SYMTABLELIST.C ******************* assignment_3
 * ***************** Aspridis Nikolaos ********************* csd5178
 ****************/


#include "symtable.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

/* Each Symbol Table (ADT) will consist of some bindings. Each binding will be of 
 * type "struct binding", no matter its value's type.
*/
struct binding {
	const char *key;
	const void *value;
	struct binding *next;
};



/*
 * ADT Symbol Table
*/
struct SymTable {
	struct binding *header;
	unsigned int num_of_bindings;
}; 



/* 
 * SymTable_new(void) creates a new , empty (without any binding) SymTable.
 *
 * Return value: a pointer to the newly created SymTable.
 * 
 **/
SymTable_T SymTable_new(void) {
	SymTable_T tmp;

	tmp = (SymTable_T)malloc(sizeof(struct SymTable));
	assert(tmp);

	tmp->num_of_bindings = 0u;

	tmp->header = NULL;	

	return tmp;
}





/*
 * SymTable_free(SymTable_T oSymTable) is responsible for releasing all the
 * memory used by the SymTable that oSymTable is referring to. 
 *
 * First of all,it checks whether oSymTable is null. If so, it returns. Otherwise, it
 * checks if oSymTable->header (the header pointer to the hash table) is null.
 * If so, it simply returns. If oSymTable->header is not null, though, it has to traverse 
 * the linked-list of the bindings and deallocate the memory used for the storage of each 
 * one of them.
 *
 * Parameters: oSymTable (of type SymTable_T) is a pointer to an instance of struct SymTable
 * Return value: - (void)
 *
 **/
void SymTable_free(SymTable_T oSymTable) {
	struct binding *ptr, *ptr_helper;

	if(oSymTable) {
	/*======if oSymTable != NULL===============*/
		if(oSymTable->header) {
			ptr = oSymTable->header;
			ptr_helper = ptr;
			while(ptr) {
				ptr = ptr->next;
				free(ptr_helper);
				ptr_helper = ptr;
			}
			oSymTable->header = NULL;
		}
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



/*
 * Procedure named "SymTable_put" is responsible for checking if there is a
 * binding with the same key as the one provided as "pcKey" parameter. If so,
 * it does nothing and returns 0 (FALSE). If there is no such binding,
 * instead, it creates a new binding (allocating memory using malloc()) and
 * adds it in the end of the linked-list. New binding's key and value are the
 * same with the ones provided as parameter "pcKey" and "pvValue"
 * respectively. Procedure, then, returns 1 (TRUE). 
 *
 * Parameters: oSymtable is a pointer to an instance of struct SymTable
 *	       pcKey is a pointer to characters (to a string actually), that
 *	       	     is going to  be used as the key for the new binding (if 
 *                   a new binding is going to be created)
 *	       pvValue is a pointer to the value (it could be of any type)
 *	             that is going to be used as the value corresponding to pcKey
 * Checked runtime errors: oSymTable or pcKey to be null
 * Return value: no. 1 (TRUE) or no. 0 (FALSE)
 * 
 **/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
	struct binding *tmp, *tmp_helper;	
	char *ptr;
	int i;

	assert(oSymTable);
	assert(pcKey);
	
	tmp_helper = NULL;
	tmp = oSymTable->header;
	while(tmp && strcmp(tmp->key, pcKey)) {
		tmp_helper = tmp;
		tmp = tmp->next;
	}
	if(!tmp) {
	/*======binding was not found into the collection====================*/
		tmp = (struct binding *)malloc(sizeof(struct binding));
		assert(tmp);
		
		/*pcKey is copied onto ptr and then, ptr is assigned into tmp->key*/
		ptr = (char *)malloc(strlen(pcKey)+1);	
		assert(ptr);		
		for(i=0; i<strlen(pcKey); i++) {
			*(ptr + i) = pcKey[i];   
		}	
		*(ptr + i) = '\0';      
		tmp->key = ptr;
		ptr = NULL;		

		/*binding's value refers to pvValue*/
		tmp->value = pvValue;

		if(tmp_helper) {
		/*======the new binding is not the first binding into the list======*/
			tmp_helper->next = tmp;
		}else {
		/*======the new binding is the first one into the list===========*/
			oSymTable->header = tmp;
		}
	        tmp->next = NULL;
		
		(oSymTable->num_of_bindings)++;

		return 1;
	}else {
	/*======binding was found into the collection==========================*/
		return 0;
	}
}



/*
 * SymTable_remove(SymTable_T oSymTable, const char *pcKey) is responsible for
 * finding the binding whose key is the same as pcKey into the linked-list of
 * SymTable (if there is such a binding in there) and throwing it away. In
 * case everything goes as expected, it returns 1 (TRUE). If the binding is
 * not found into the linked-list, the last one does not change and the
 * procedure returns 0 (FALSE).
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pcKey is a pointer to characters (a pointer to a string
 *                   actually) that is going to be used as the key that the
 *                   procedure will look for, into the linked-list
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
	struct binding *tmp, *tmp_helper;

	assert(oSymTable);
	assert(pcKey);
	
	tmp_helper = NULL;
	tmp = oSymTable->header;
	while(tmp && strcmp(tmp->key, pcKey)) {
		tmp_helper = tmp;
		tmp = tmp->next;
	}
	if(!tmp) {
	/*======binding was not found into the collection====================*/
		return 0;
	}else {
	/*======binding was found into the collection==========================*/
		if(tmp_helper) {
		/*====the binding that is to be deleted is not the first one into the linked-list=====*/
			tmp_helper->next = tmp->next;
			free(tmp);
			tmp = NULL;	
		}else {
		/*====the binding that is to be deleted is the first one into the linked-list=========*/
			oSymTable->header = tmp->next;		
			free(tmp);
			tmp = NULL;
		}
		return 1;
	}
}


/*
 * SymTable_contains(SymTable_T oSymTable, const char *pcKey) checks if there
 * is a binding, into the linked list, whose key is the same as pcKey. If
 * that's the case, it returns 1(TRUE). Otherwise, it returns 0(FALSE).
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pcKey is a pointer to characters (to a string actually) that
 *                   are going to be used as the key that the procedure will
 *                   look for, into the linked list            
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
	struct binding *tmp;

	assert(oSymTable);
	assert(pcKey);
	
	tmp = oSymTable->header;
	while(tmp && strcmp(tmp->key, pcKey)) {
		tmp = tmp->next;
	}
	if(!tmp) {
	/*======binding was not found into the collection====*/
		return 0;
	}else {
	/*======binding was found into the collection========*/
		return 1;
	}

}




/*
 * SymTable_get(SymTable_T oSymTable, const char *pcKey) looks for a binding
 * whose key is the same as pcKey into the linked-list of SymTable. If it
 * finds one, it returns the address of its value. Otherwise, it returns null.
 * 
 * Warning : return discards ‘const’ qualifier from pointer target type 
 * Parameters : oSymTable is a pointer to an instance of struct SymTable
 * 		pcKey is a pointer to characters (to a string, actually) that
 * 		      are going to be used as the key that the procedure will
 * 		      look for, into the SymTable 
 * Return value : the address of binding's value (success), or null (failure)
 *
 **/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
	struct binding *tmp;

	assert(oSymTable);
	assert(pcKey);
	
	tmp = oSymTable->header;
	while(tmp && strcmp(tmp->key, pcKey)) {
		tmp = tmp->next;
	}
	if(!tmp) {
	/*======binding was not found into the collection====*/
		return NULL;
	}else {
	/*======binding was found into the collection========*/
		return (void *)(tmp->value);
	}
}


/*
 * SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void
 * *pvValue, void *pvExtra), const void *pvExtra) is responsible for applying
 * function pointed to by pfApply on each binding of the linked list. Function
 * pointed to by pfApply takes binding's key, binding's value and data pointed to by
 * pvExtra as arguments for its call on each binding.
 *
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 *             pfApply is a pointer to a function that returns void and takes
 *                     a pointer to characters (string) and two pointers to
 *                     void as its parameters
 *             pvExtra is a pointer to void, that is going to be used as
 *                     pfApply's third parameter on each of its calls
 * Checked runtime errors : oSymTable or pfApply to be null
 * Warning :  passing arguments 2 and 3 of ‘pfApply’ discard ‘const’ qualifier from
 *            pointer target type [-Wdiscarded-qualifiers]
 * Return value : -(void)
 *
 **/
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra) {
	struct binding *tmp;	

	assert(oSymTable);
	assert(*pfApply);

	tmp = oSymTable->header;
	while(tmp) {
		pfApply(tmp->key, (void *)tmp->value, (void *)pvExtra);
		tmp = tmp->next;
	}
}


/*
 * SymTable_print is a procedure of my own that is supposed to print the key
 * and the value of each of the bindings that "exist" into the linked list. The
 * reason I made this procedure is to be able to check any time I choose to
 * the stored data into the linked-list.
 *  
 * Checked runtime errors: oSymTable to be null
 * Parameters: oSymTable is a pointer to an instance of struct SymTable
 * Return value: -(void)
 *
 **/
void SymTable_print(SymTable_T oSymTable) {
	struct binding *tmp;

	assert(oSymTable);

	if(oSymTable->header) {
		/*list is not empty*/
		tmp = oSymTable->header;
		while(tmp) {
			printf("%s %u\n", tmp->key, *((unsigned int *)(tmp->value)));
			tmp = tmp->next;
		}
	}else {
		/*list is empty*/
		printf("linked-list is empty (no bindings)!");
	}	
	
	printf("\n\n");
}



