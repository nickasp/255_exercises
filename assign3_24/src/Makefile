###################################################
#
# file: Makefile
#
# @Author:   Nikolaos Aspridis
# @Version:  24-03-2024
# @email:    csd5178@csd.uoc.gr
#
# Makefile
#
####################################################

all : list hash

list : testsymtab.o symtablelist.o
	gcc testsymtab.o symtablelist.o -o list 

hash : testsymtab.o symtablehash.o
	gcc testsymtab.o symtablehash.o -o hash



testsymtab.o : testsymtab.c symtable.h
	gcc -Wall -ansi -pedantic -c testsymtab.c

symtablelist.o : symtablelist.c symtable.h
	gcc -Wall -ansi -pedantic -c symtablelist.c

symtablehash.o : symtablehash.c symtable.h
	gcc -Wall -ansi -pedantic -c symtablehash.c
	




clean : 
	rm -f *.o
	rm -f list hash
