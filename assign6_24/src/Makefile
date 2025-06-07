#########################################################
#							#
# @Author : Aspridis Nikolaos csd5178			#
# @academic_year : 2023-2024				#
# @ Assignment 6 -/- hy255				#
#							#
#########################################################



all: createdata3 createdata6 createdata9
	./createdata3
	./createdata6
	./createdata9

data3 : createdata3
	./createdata3

createdata3 : createdata3.c
	gcc -Wall -ansi -pedantic createdata3.c -o createdata3

data6 : createdata6
	./createdata6

createdata6 : createdata6.c
	gcc -Wall -ansi -pedantic createdata6.c -o createdata6

data9 : createdata9
	./createdata9

createdata9 : createdata9.c
	gcc -Wall -ansi -pedantic createdata9.c -o createdata9

t1 : t1.s
	gcc t1.s -o t1

clean :
	rm -f *.tmp

	rm -f t1 

	rm -f data3
	rm -f data6
	rm -f data9

	rm -f createdata3
	rm -f createdata6
	rm -f createdata9



