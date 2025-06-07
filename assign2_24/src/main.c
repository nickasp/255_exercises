

#include "mystring.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	char dest[100];
	char test[] = {'g','o','o','d',' ','v','i','b','e','s',' ','o','n','l','y','!','\0'};
        char test2[] = {'b','a','d','\0'}; 
	char test3[30] = "baby, where is my", test4[15] = " dog ?";
	char test5[30] = {'\0'};
	char test6[30];
	char *p;
	char *s1 = "hello";
	char *s2 = "hello";

	printf("----ms_length TESTING----\n");
    	/*printf("%lu\n",ms_length(NULL));*/
    	printf("%lu\n",ms_length(""));
    	printf("%lu\n",ms_length("hello world!"));
    	printf("-------------------------\n\n");
	

	printf("----ms_copy TESTING----\n");
	p = ms_copy(dest,test);
	while(*p){
		printf("%c",*p);
		p++;
	}
	printf("\n-----------------------\n\n");

	printf("----ms_ncopy TESTING----\n");
	p = ms_ncopy(dest,test2,7);
	while(*p){
		printf("%c",*p);
		p++;
	}
	printf("\n");

	p = dest;
	while(*p){
		printf("%c",*p);
		p++;
	}
	while(!(*p)){
		printf("%d",*p);
		p++;
	}
	while(*p){
		printf("%c",*p);
		p++;
	}
	printf("\n------------------------\n\n");
	
	
	printf("----ms_concat TESTING----\n");
	p = ms_concat(test3, test4);
	printf("%s\n",p);
	p = ms_concat(test5, test4);
	printf("%s\n",p);
	p = ms_concat(test6, test4);
	printf("%s\n",p);
	printf("-------------------------\n\n");
	
	printf("----ms_nconcat TESTING----\n");
	printf("%s\n",test);
	p = ms_nconcat(test3,test,4);
	printf("%s\n",p);
	printf("%s\n",test);
	p = ms_nconcat(test3,test,17);
	printf("%s\n",p);
	printf("%s\n",test);
	p = ms_nconcat(test3,test,45);
	printf("%s\n",p);
	printf("------------------------\n\n");

	printf("----ms_compare TESTING----\n");
	printf("%s %s %d\n",s1,s2,ms_compare(s1,s2));
	s1 = "hello";
	s2 = "add";
	printf("%s %s %d\n",s1,s2,ms_compare(s1,s2));
	printf("%s %s %d\n",s2,s1,ms_compare(s2,s1));
	s2 = "hel";
	printf("%s %s %d\n",s1,s2,ms_compare(s1,s2));
	printf("%s %s %d\n",s2,s1,ms_compare(s2,s1));
	printf("--------------------------\n\n");

	printf("----ms_ncompare TESTING----\n");
	s1 = "helloworld";
	s2 = "helloworld";
	printf("%s %s num=%d %d\n",s1,s2,11,ms_ncompare(s1,s2,11));
	printf("%s %s num=%d %d\n",s1,s2,110,ms_ncompare(s1,s2,110));
	s1 = "hela";
	printf("%s %s num=%d %d\n",s1,s2,11,ms_ncompare(s1,s2,11));
	printf("%s %s num=%d %d\n",s2,s1,11,ms_ncompare(s2,s1,11));
	printf("%s %s num=%d %d\n",s1,s2,110,ms_ncompare(s1,s2,110));
	printf("%s %s num=%d %d\n",s2,s1,110,ms_ncompare(s2,s1,110));
	s1 = "helloworld";
	printf("%s %s num=%d %d\n",s1,s2,4,ms_ncompare(s1,s2,4));
	s1 = "hela";
	printf("%s %s num=%d %d\n",s1,s2,4,ms_ncompare(s1,s2,4));
	printf("%s %s num=%d %d\n",s2,s1,4,ms_ncompare(s2,s1,4));
	printf("---------------------------\n\n");

	printf("----ms_search TESTING----\n");
	s1 = "hello world! Oh, what a beautiful day!!!";
	s2 = "abcd";
	p = ms_search(s1,s2);
	if(p){
		printf("%s\n",p);
	}else{
		printf("null\n");
	}

	s2 = "h";
	if(p){
		printf("%s\n",p);
	}else{
		printf("null\n");
	}

	s2 = "world";
	if(p){
		printf("%s\n",p);
	}else{
		printf("null\n");
	}

	s2 = "day!!!";
	if(p){
		printf("%s\n",p);
	}else{
		printf("null\n");	
	}
	printf("---------------------------\n\n");

	return 0; 
}













