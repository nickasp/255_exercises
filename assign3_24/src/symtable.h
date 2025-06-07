/***************** SYMTABLE.H ******************** assignment_3 *********************** Aspridis Nikolaos
 * ***************** csd5178 *******************/

#ifndef __SYMTABLE_H__

/*
 * SymTable_T is a pointer to struct SymTable (a pointer to a Symbol Table
 * (ADT), actually).
*/
typedef struct SymTable* SymTable_T;



/* 
 * SymTable_new(void) creates a new , empty (without any binding) SymTable.
 * 
 * Parameters: - (void)
 * Return value: a pointer to the newly created SymTable.
 * 
 **/
SymTable_T SymTable_new(void); 



/*
 * SymTable_free(SymTable_T oSymTable) is responsible for releasing all the
 * memory used by the SymTable that oSymTable is referring to.
 *
 * Parameters: oSymtable is a reference to the SymTable
 * Return value: -(void)
 * 
 **/
void SymTable_free(SymTable_T oSymTable);



/*
 * SymTable_getLength(SymTable_T oSymTable) procedure returns the number of
 * bindings into the SymTable.
 *
 * Parameters: oSymTable is a reference to the SymTable
 * Checked runtime errors : oSymTable to be null
 * Return value: the number of bindings that exist into the SymTable
 * (num_of_bindings) 
 *
 **/
unsigned int SymTable_getLength(SymTable_T oSymTable);


/*
 * Procedure named "SymTable_put" is responsible for checking if there is a
 * binding with the same key as the one provided as "pcKey" parameter. If so,
 * it does nothing and returns 0 (FALSE). If there is no such a binding,
 * it creates a new binding (allocating memory using malloc()) and adds it in
 * the end of the linked-list, instead. New binding's key and value are the
 * same with the ones provided as parameter "pcKey" and "pvValue"
 * respectively. 
 *
 * Parameters: oSymtable is a reference to the SymTable
 *	       pcKey is a reference to the key that the procedure will look
 *	       	     for into the SymTable
 *	       pvValue is a reference to the value that pcKey will correspond
 *	             to, if finally a new binding is created
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value: 0 for false and 1 for true. False means that a binding with a
 * 		     key same as pcKey was found, so no new binding was
 * 		     created and added to the linked-list, while true means that no
 * 		     such a binding was found and, as a result, a new one with
 * 		     the proper data was created and added to the linked-list.
 *		
 **/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void
*pvValue);




/*
 * SymTable_remove(SymTable_T oSymTable, const char *pcKey) is responsible for
 * finding the binding whose key is the same as pcKey into SymTable (if there is
 * such a binding in there) and throwing it away. In case everything goes as expected,
 * it returns 1 (TRUE). If the binding is not found into SymTable, the last one
 * does not change and the procedure returns 0 (FALSE).
 *
 * Parameters: oSymTable is a reference to SymTable
 *             pcKey is a reference to the string that is going 
 *                   to be used as the key that the procedure will
 *                   look for, into SymTable
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);


/*
 * SymTable_contains(SymTable_T oSymTable, const char *pcKey) checks if there
 * is a binding (into SymTable) whose key is the same as pcKey. If
 * that's the case, it returns 1(TRUE). Otherwise, it returns 0(FALSE).
 *
 * Parameters: oSymTable is a reference to SymTable
 *             pcKey is a reference to the string that is going to be used as 
 *                   the key that the procedure will look for, into the SymTable            
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value: 0 (FALSE) for not finding a binding whose key is the same as
 * 		 pcKey and 1 (TRUE) for finding one
 *
 **/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);


/*
 * SymTable_get(SymTable_T oSymTable, const char *pcKey) looks for a binding
 * whose key is the same as pcKey into the SymTable. If it finds one, it returns
 * the address of its value. Otherwise, it returns null.
 * 
 * Warning : return discards ‘const’ qualifier from pointer target type 
 * Parameters : oSymTable is a reference to SymTable
 * 		pcKey is a reference to the string that is going to be 
 *                    used as the key that the procedure will look for, 
 *                    into the SymTable 
 * Checked runtime errors : oSymTable or pcKey to be null
 * Return value : the address of binding's value (success), or null (failure)
 *
 **/
void *SymTable_get(SymTable_T oSymtable, const char *pcKey);


/*
 * SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void
 * *pvValue, void *pvExtra), const void *pvExtra) is responsible for applying
 * function pointed to by pfApply on each binding of SymTable. Function pointed 
 * to by pfApply takes binding's key, binding's value and data pointed to by
 * pvExtra as arguments for its call on each binding.
 *
 * Parameters: oSymTable is a reference to SymTable
 *             pfApply is a reference to a function that returns void and takes
 *                     a pointer to characters (string) and two pointers to 
 *                     void as its parameters
 *	       pvExtra is a reference to void (it could be reference to any
 *	               type of data) , that is going to be used as pfApply's 
 *                     third parameter on each of its calls	       
 * Checked runtime errors : oSymTable or pfApply to be null 
 * Return value : -(void)
 *
 **/
void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, 
	void *pvValue, void *pvExtra), const void *pvExtra);


/*
 * SymTable_print is a procedure of my own that is supposed to print the key
 * and the value of each of the bindings into the Symbol Table. The reason 
 * I made this procedure is to be able to check any time I choose to
 * the stored data into the Symbol Table.
 *
 * Checked runtime errors: oSymTable to be null
 * Parameters: oSymTable is a reference to a Symbol Table
 * Return value: -(void)
 *
 **/
void SymTable_print(SymTable_T oSymTable);



#define __SYMTABLE_H__

#endif
