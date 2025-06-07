/*********************** ASPRIDIS_NIKOLAOS *************** ASSIGNMENT_2 ****************** mystring_ptrs.c ********************/

#include <assert.h>
#include <stddef.h>
#include "mystring.h"
/*
 *The following function returns the length of the string given to it as its parameter my_str.
 *It is a checked runtime error for 'my_str' to be NULL.
 *
 *Parameters: my_str --> the string for which the length is counted
 *Return value: the length of the given string, counted in bytes 
 *
 */
size_t ms_length(const char *my_str) {
     const char *mystring_end = my_str;  
     assert(my_str); 
     while(*mystring_end) {
         mystring_end++;
     }
     return (mystring_end - my_str);
}



/*
 *The following function copies the string pointed to by 'source' parameter (pointer to char) to the position
 *in the memory, pointed to by 'destination' parameter (another pointer to char).
 *
 *Checked runtime errors: 'source' and 'destination' to be NULL
 *Unchecked runtime errors: 1)  'destination''s capacity to be smaller than needed, so as string (pointed to by 'source') to not
 *                              be able to fit into the memory pointed to by 'destination'.
 *                          2)  strings pointed to by 'source' and 'destination' to overlap.
 *                          3)  If the string pointed to by 'source' contains a '\0' character into an additional point, rather than only in the end
 *                              of the string, copying will terminate as soon as the first '\0' character is encountered. As a result, the rest of the string
 *                              (laying after the first '\0' character till the ending '\0' character) will not be copied.
 *Parameters:             destination ---> pointer to the part of the memory where the string pointed to by 'source' is going to be copied
                          source      ---> pointer to the part of the memory where the string that is to be copied has been stored
 *Return value:           the memory address of the starting byte of the memory where the string (pointed to by 'source') was copied into
 *
 * */
char *ms_copy(char *destination, const char *source) {
        char *tmp;

	assert(source && destination);
        /*assert();*/

	tmp = destination;

        while(*source){
                *destination = *source;
                destination++;
		source++;
        }
        *destination = '\0';

        return tmp;
}





/*
 *The following function copies the first "num" characters from the string pointed to by 'source' parameter (pointer to char) to the position
 *in the memory, pointed to by 'destination' parameter (pointer to char).If num is greater than the total number of characters that the string pointed to by
 *'source' contains, then the string is copied normally, but the rest of the (num - number_of_source_characters) characters are filled in with the '\0' character.
 *
 *Checked runtime errors: 'source' and 'destination' to be NULL
 *Unchecked runtime errors: 1)  'destination''s capacity to be smaller than needed, so as string (pointed to by 'source') to not
 *                              be able to fit into the memory pointed to by 'destination'.
 *                          2)  strings pointed to by 'source' and 'destination' to overlap.
 *                          3)  If the string pointed to by 'source' contains a '\0' character into an additional point, rather than only in the end
 *                              of the string, copying will terminate as soon as the first '\0' character is encountered. As a result, the rest of the string
 *                              (laying after the first '\0' character till the ending '\0' character) will not be copied.
 *Parameters:             destination ---> pointer to the part of the memory where the string pointed to by 'source' is going to be copied
                          source      ---> pointer to the part of the memory where the string that is to be copied has been stored
                          num         ---> number of characters from string pointed to by 'source' that are to be copied
 *Return value:           the memory address where the string (pointed to by 'source') was copied into
 *
 */
char *ms_ncopy(char *destination, const char *source, size_t num){
        size_t i;
        assert(source && destination);
        /*assert();*/

        i=0;
        while(*(source + i) && (i<num)){
                *(destination + i) = *(source + i);
                i++;
        }
        while(i<num){
                *(destination + i) = '\0';
                i++;
        }

        return destination;
}





/*
 *The following function appends the string pointed to by parameter 'source'(pointer to char) to the string pointed to by parameter 'destination' (pointer to char).
 *
 *Checked runtime errors: 'destination' and 'source' (pointers to char) to be null
 *Unchecked runtime errors: 1)  'destination''s capacity to be smaller than needed, so as string (pointed to by 'source') to not be able to be added after the string
 *                              pointed to by 'destination'.
 *                          2)  strings pointed to by 'source' and 'destination' to overlap.
 *                          3)  If the string pointed to by 'source' contains a '\0' character into an additional point, rather than only in the end
 *                              of the string, appending will terminate as soon as the first '\0' character is encountered. As a result, the rest of the string pointed
 *                              to by 'source' (laying after the first '\0' character till the ending '\0' character) will not be appended.
 *
 *Parameters:            destination ---> pointer to the string that is going to be used for the other string to be appended to
 *                       source      ---> pointer to the string that is going to be appended to the string pointed to by 'destination'
 *Return value:          the memory address of the final string, after string pointed to by 'source' has been appended to the string pointed to by 'destination'
 *
 * */
char *ms_concat(char *destination, const char *source){
        size_t j;
	char *tmp;	

	assert(destination && source);

        j = ms_length(destination);
	tmp = destination;
	destination = destination + j;
	while(*source){
                *destination = *source;
                destination++;
		source++;
        }
        *destination = '\0';

        return tmp;
}



/*
 *The following function appends the first "num" characters of the string pointed to by parameter 'source'(pointer to char) to the string pointed to by parameter 'destination' (pointer to char).
 *If num is greater than or equal to the total number of characters string pointed by 'source' has, then the whole string is appended.
 *
 *Checked runtime errors: 'destination' and 'source' (pointers to char) to be null
 *Unchecked runtime errors: 1)  'destination''s capacity to be smaller than needed, so as the first "num" characters of the string pointed to by 'source' to not be able
 *                              to be added after the string pointed to by 'destination'.
 *                          2)  strings pointed to by 'source' and 'destination' to overlap.
 *                          3)  If the string pointed to by 'source' contains a '\0' character in between its first "num" characters, rather than only in the end appending
 *                              will terminate as soon as the first '\0' character is encountered. As a result, the rest of the "num" first characters of the string pointed
 *                              to by 'source' (laying after the first '\0' character till the "num"th character) will not be appended.
 *
 *Parameters:            destination ---> pointer to the string that is going to be used for the other string to be appended to
 *                       source      ---> pointer to the string whose first "num" characters are going to be appended to the string pointed to by 'destination'
 *Return value:          the memory address of the final string, after the first "num" characters of the string pointed to by 'source' have been appended
 *                       to the string pointed to by 'destination'
 *
 * */
char *ms_nconcat(char *destination, const char *source, size_t num){
      	char *tmp;
	size_t i;

        assert(destination && source);

	tmp = destination;
	destination = destination + ms_length(destination);
	i = 0;
	while(*source && (i<num)){
                *destination = *source;
                destination++;
		source++;
		i++;
        }
        *destination = '\0';

        return tmp;
}



/*
 *The following function lexicographically compares the two strings (pointed to by 's1' and 's2') given to it as its parameters. If the string pointed to by s1 is smaller than
 *the string pointed to by s2, the function will return a negative number. If the string pointed to by s1 is bigger than the string pointed to by s2, the function will return a
 *positive number instead. Lastly, if the string pointed to by s1 is equal to the string pointed to by s2, the function will return 0.
 *
 *Checked runtime errors: strings pointed to by s1 and s2 to be null
 *Unchecked runtime errors: If one of the two strings contains a '\0' character into an additional point, rather than only in the end
 *                          of it, comparing will terminate as soon as the first '\0' character is encountered. As a result, the rest of the string
 *                          (laying after the first '\0' character till the ending '\0' character) will not be taken into consideration. 
 *Parameters  : s1 ---> pointer to the first string
 *              s2 ---> pointer to the second string
 *Return value: The integer value that indicates whether the two strings are equal, or one of them is smaller/bigger than the other ((equal --> 0), (s1<s2 --> negative value), 
 *		(s1>s2 --> positive value)).
 *
 * */
int ms_compare(const char *s1, const char *s2){
        int result;

        assert(s1 && s2);

        while((*s1 == *s2) && *s1){
                s1++;
		s2++;
        }
        result = (int)*s1 - (int)*s2;

        return result;
}



/*
 *The following function lexicographically compares the first "num" (at most) characters of the two strings (pointed to by 's1' and 's2'), given to it as its parameters. If the 
 *string (consisting of the first "num", at most, characters of the string) pointed to by s1 is smaller than the string (consisting of the first "num", at most, characters of the string)
 *pointed to by s2, the function will return a negative number. If the string (consisting of the first "num", at most, characters of the string) pointed to by s1 is bigger than the string
 *(consisting of the first "num", at most, characters of the string) pointed to by s2, the function will return a positive number instead. Lastly, if the string (+++) pointed to by s1 is equal
 *to the string (+++) pointed to by s2, the function will return 0.
 *
 *Checked runtime errors: strings pointed to by s1 and s2 to be null
 *Unchecked runtime errors: If one of the two strings contains a '\0' character into an additional point, rather than only in the end
 *                          of it, and that '\0' character belongs to string's first "num" characters, comparing will terminate as soon as the first that '\0' character is encountered. 
 *			    As a result, the rest of the string (laying after the first '\0' character till the "num"th character) will not be taken into consideration.
 *Parameters  : s1 ---> pointer to the first string
 *              s2 ---> pointer to the second string
 *		num --> the number of characters that are checked (at most) for each string
 *Return value: The integer value that indicates whether the two strings are equal, or one of them is smaller/bigger than the other ((equal --> 0), (s1<s2 --> negative value),
 *              (s1>s2 --> positive value)).
 *
 * */
int ms_ncompare(const char *s1, const char *s2, size_t num){
	size_t i;
	int result;

	assert(s1 && s2);

	i = 0;
	while(((*s1 == *s2) && *s1) && (i < num)){
		i++;
		s1++;
		s2++;
	}
	if(!(i < num)){
		s1--;
		s2--;
	}
	result = (int)*s1 - (int)*s2;

	return result;
}








