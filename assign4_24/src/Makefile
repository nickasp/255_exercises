
###################################################
#
# file: Makefile
#
# @Author:   Nikolaos Aspridis
# @Version:  09-04-2024
# @email:    csd5178@csd.uoc.gr
#
# Makefile
#
####################################################

all: sudoku


sudoku : grid.o sudoku.o
	gcc grid.o sudoku.o -o sudoku

grid.o : grid.c grid.h
	gcc -Wall -ansi -pedantic -c grid.c

sudoku.o : sudoku.c sudoku.h grid.h
	gcc -Wall -ansi -pedantic -c sudoku.c

clean : 
	rm -f *.o
	rm -f sudoku
	rm -f *.txt 


