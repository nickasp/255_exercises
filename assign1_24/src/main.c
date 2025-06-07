/******************************_"ASPRIDIS NIKOLAOS"_**********************_"assignment1"_*************************_"main.c"_*************************************************************************************/


#include <stdio.h>

void initialise_map(char** map);
void character_translation(char** map);

/*
 * This enumeration set is global. Its role is to describe the states of the fsm used to translate "Mp"/"MP" to 'B', "mp"/"mP" to 'b', "Nt"/"NT" to 'D' and "nt"/"nT" to 'd'. s0 is the starting state or, else,
 * the state to describe that no letter (n,N,m or M) is left to be printed. For example, if the input character is the greek small letter 'n', then we go from state s0 to state n. If the next input character is  *  the greek small letter 't' or the greek capital letter 'T', then from state n we go to state s0 again and 'd' gets printed. If the next input character is something other than the greek characters 't', 'T',
 * 'm','M','n' or 'N', then both 'n' and the next input character get printed, one after the other and state remains the same. If the next input character is one of 'm','M','N' or 'n', then 'n' gets printed
 * and state becomes either m, either M, either N or n, accordingly. Similar procedures as the one described above are used to print 'D','b' or 'B', given the appropriate input characters.
 * 
 * */
enum machine_states {
	s0, n, N, m, M
} state;



/*
 * Main function is used to declare an  array of pointers to characters, with 73 positions, that is going to be used for the mapping, call initialise_map(char**) function to initialise the array appropriately,
 * as well as call character_translation(char**) function to deal with character input's appropriate translation. main returns 0 to the OS if everything works fine and no error occurs.
 *
 * Return value: 0 (everything okay) or (!=0) (an error has occured)
 * */
int main(void){

	char* map[73];
	
	initialise_map(map);
	
	character_translation(map);

	return 0;
}


/*
 * initialise_map(char**) function is responsible for the appropriate initialisation of the mapping array, that it takes as a parameter. It is called by main function once, in the beginning of the programme, 
 * to initialise the array. This one-dimensional array of strings, actually, is going to contain the strings with which the input characters (that are to change) are going to be exchanged. Let's say, for 
 * example, that the greek small letter a is the input character. On iso8859-7, this letter's number is no. 225. So , the string literall with which it will be exchanged is going to be stored into th
 * (225-182)th position of the array.
 * 
 * Parameter : a double pointer to the string array that is going to be initialised
 * Return value: void
 * */
void initialise_map(char** map){

	/*My goal was to make the array as small as possible!*/
	
	/*index's value = char's value - 182*/

	map[0] = "'A"; 
	map[1] = NULL; /*middle dot*/
	map[2] = "'E";
	map[3] = "'H";
	map[4] = "'I";
	map[5] = NULL; /*right-pointing double angle quotation mark*/
	map[6] = "'O";
	map[7] = NULL; /*vulgar fraction one half*/
	map[8] = "'Y";
	map[9] = "'W";
	
	map[10] = "i\"'";
	
	map[11] = "A";     
	map[12] = "V";
	map[13] = "G";
	map[14] = "D";
	map[15] = "E";
	map[16] = "Z";
	map[17] = "H";
	map[18] = "8";
	map[19] = "I";
	map[20] = "K";
	map[21] = "L";
	map[22] = "M";
	map[23] = "N";
	map[24] = "KS";
	map[25] = "O";
	map[26] = "P";
	map[27] = "R";
	
	map[28] = NULL; /*something else (perhaps a control character)*/

	map[29] = "S";
	map[30] = "T";
	map[31] = "Y";
        map[32] = "F";
	map[33] = "X";
	map[34] = "PS";
	map[35] = "W";
	
	map[36] = "I\"";
	map[37] = "Y\"";
	
	map[38] = "a'";
	map[39] = "e'";
	map[40] = "h'";
	map[41] = "i'";
	
	map[42] = "y\"'";

	map[43] = "a";
	map[44] = "v";
	map[45] = "g";
	map[46] = "d";
	map[47] = "e";
	map[48] = "z";

	map[49] = "h";
	map[50] = "8";
	map[51] = "i";
	map[52] = "k";
	map[53] = "l";
	map[54] = "m";
	map[55] = "n";
	map[56] = "ks";
	map[57] = "o";
	map[58] = "p";
	map[59] = "r";
	map[60] = "s"; /*greek small letter final sigma*/
	map[61] = "s"; /*greek small letter sigma*/
	map[62] = "t";
	map[63] = "y";
	map[64] = "f";
	map[65] = "x";
	map[66] = "ps";
	map[67] = "w";

	map[68] = "i\"";
	map[69] = "y\"";
	
	map[70] = "o'";
	map[71] = "y'";
	map[72] = "w'";

}



/*
 * character_translation(char**) function is responsible for the characters' input 'translation', from iso8859-7 to iso8859-1 . Characters given as input from stdin are read one by one and either get printed
 * (onto stdout) right away (characters' numbers smaller than 182), or they are exchanged with their 'translation' ones, found into the mapping array, and get printed afterwards (characters' numbers greater 
 * than or equal to 182). Enumeration type called 'machine_states' is used to make clear when the greek letters 'n','m','N' and 'M' have to get printed out as their latin characters 'n', 'm', 'N' and 'M' 
 * correspondingly, OR the programme has to print 'b','B','d' or 'D' instead. 
 *
 * ATTENTION: ***All numeric values refer to their corresponding characters from iso8859-7 character encoding!***
 *
 * Parameter: a double pointer to the string array used for the characters' mapping
 * Return value: void
 * */
void character_translation(char** map){

	unsigned char c = '\0';
	char* s = NULL;
	int i;
	
	state = s0;
	while((c = getchar()) != 255){
		if(c >= 182){
			if(c == 237){
			/*c == greek small letter n*/
				if(state == s0){
					/*state becomes n*/
					state = n;
				}else if(state == n){
					/*'n' is printed onto stdout*/
					/*state remains equal to n*/
					putchar('n');
				}else if(state == N){
					/*the previous letter was the greek capital letter N*/
					/*'N' is printed onto stdout*/
					putchar('N');
					/*state becomes n*/
					state = n;
				}else if(state == M){
					/*the previous letter was the greek capital letter M*/
					/*'M' is printed onto stdout*/
					putchar('M');
					/*state becomes n*/
					state = n;
				}else if(state == m){
					/*the previous letter was the greek small letter m*/
					/*'m' is printed onto stdout*/
					putchar('m');
					/*state becomes n*/
					state = n;
				}
			}else if(((c == 244)&&(state == n)) || ((c == 212)&&(state == n))){
			/*c == (greek small letter t / greek capital letter T) and the previous letter was the greek small letter n (state == n)*/
				/*'d' is printed onto stdout*/
				putchar('d');
				/*state becomes s0*/
				state = s0;
			}else if(c == 205){
			/*c == greek capital letter N*/
				if(state == n){
					/*the previous letter was the greek small letter n*/
					/*'n' is printed onto stdout*/
					putchar('n');
					/*state becomes N*/
					state = N;
				}else if(state == N){
					/*the previous letter was the greek capital letter N*/
					/*'N' is printed onto stdout*/
					putchar('N');
					/*state remains N*/
				}else if(state == m){
					/*the previous letter was the greek small letter m*/
					/*'m' is printed onto stdout*/
					putchar('m');
					/*state becomes N*/
					state = N;
				}else if(state == M){
					/*the previous letter was the greek capital letter M*/
					/*'M' is printed onto stdout*/
					putchar('M');
					/*state becomes N*/
					state = N;
				}else {
					/*state == s0*/
					/*state becomes N*/
					state = N;
				}
			}else if(((c == 244)&&(state == N)) || ((c == 212)&&(state == N))){
			/*c == (greek small letter t / greek capital letter T) and the previous letter was the greek capital letter N (state == N)*/
				/*'D' is printed onto stdout*/
				putchar('D');
				/*state becomes s0*/
				state = s0;
			}else if(c == 236){
			/*c == greek small letter m*/
				if(state == n){
					/*the previous letter was the greek small letter n*/
					/*'n' is printed onto stdout*/
					putchar('n');
					/*state becomes m*/
					state = m;
				}else if(state == N){
					/*the previous letter was the greek capital letter N*/
					/*'N' is printed onto stdout*/
					putchar('N');
					/*state becomes m*/
					state = m;
				}else if(state == m){
					/*the previous letter was the greek small letter m*/
					/*'m' is printed onto stdout*/
					putchar('m');
					/*state remains m*/
				}else if(state == M){
					/*the previous letter was the greek capital letter M*/
					/*'M' is printed onto stdout*/
					putchar('M');
					/*state becomes m*/
					state = m;
				}else {
					/*state == s0*/
					/*state becomes m*/
					state = m;	
				}
			}else if(c == 204){
			/*c == greek capital letter M*/
				if(state == n){
					/*the previous letter was the greek small letter n*/
					/*'n' is printed onto stdout*/
					putchar('n');
					/*state becomes M*/
					state = M;
				}else if(state == N){
					/*the previous letter was the greek capital letter N*/
					/*'N' is printed onto stdout*/
					putchar('N');
					/*state becomes M*/
					state = M;
				}else if(state == m){
					/*the previous letter was the greek small letter m*/
					/*'m' is printed onto stdout*/
					putchar('m');
					/*state becomes M*/
					state = M;
				}else if(state == M){
					/*the previous letter was the greek capital letter M*/
					/*'M' is printed onto stdout*/
					putchar('M');
					/*state remains M*/
				}else {
					/*state == s0*/
					/*state becomes M*/
					state = M;
				}
			}else if(((c==208)||(c==240))&&(state==m)){
			/*c == (greek capital letter P or greek small letter p) and the previous letter was the greek small letter m*/
				/*'b' is printed onto stdout*/
				putchar('b');
				/*state becomes s0*/
				state = s0;
			}else if(((c==208)||(c==240))&&(state==M)){
			/*c == (greek capital letter P or greek small letter p) and the previous letter was the greek capital letter M*/
				/*'B' is printed onto stdout*/
				putchar('B');
				/*state becomes s0*/
				state = s0;
			}else{
			/*c == any other possible character */
				if(state == n){
					/*the previous letter was the greek small letter n*/
					/*firstly, 'n' is printed onto stdout*/
					putchar('n');
					/*state becomes s0*/
					state = s0;
				}else if(state == N){
					/*the previous letter was the greek capital letter N*/
					/*firstly, 'N' is printed onto stdout*/
					putchar('N');
					/*state becomes s0*/
					state = s0;
				}else if(state == m){
					/*the previous letter was the greek small letter m*/
					/*firstly, 'm' is printed onto stdout*/
					putchar('m');
					/*state becomes s0*/
					state = s0;
				}else if(state == M){
					/*the previous letter was the greek capital letter M*/
					/*firstly, 'M' is printed onto stdout*/
					putchar('M');
					/*state becomes s0*/
					state = s0;
				}
				/*else{
					state == s0
					state remains s0
				}*/

				/*secondly, c is 'translated' and its translation gets printed onto stdout*/
			
				/*printf("%d\n",(c-182));*/
				s = map[c-182];
				
				i=0;
				while(s[i]!='\0'){
					/*english 'translation' characters that correspond to the greek input character (c) get printed one by one, onto stdout*/
					putchar(s[i]);
					i++;
				}
			}
		}else {
			/*the character is not 'translated' and gets printed as it is*/
			if(state == n){
				/*the previous letter was the greek small letter n*/
				/*'n' and c are printed onto stdout*/
				putchar('n');
				putchar(c);
				/*state becomes s0*/
				state = s0;
			}else if(state == N){
				/*the previous letter was the greek capital letter N*/
				/*'N' and c are printed onto stdout*/
				putchar('N');
				putchar(c);
				/*state becomes s0*/
				state = s0;
			}else if(state == m){
				/*the previous letter was the greek small letter m*/
				/*'m' and c are printed onto stdout*/
				putchar('m');
				putchar(c);
				/*state becomes s0*/
				state = s0;
			}else if(state == M){
				/*the previous letter was the greek capital letter M*/
				/*'M' and c are printed onto stdout*/
				putchar('M');
				putchar(c);
				/*state becomes s0*/
				state = s0;
			}else{
				/*state == s0*/
				/*c gets printed onto stdout*/
				putchar(c);
				/*state remains s0*/
			}
		}
	}

}


