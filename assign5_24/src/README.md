## ASPRIDIS NIKOLAOS csd5178 ----- assignment_5 -----------------------------

# Exercise 1 :
	a) The sum from 11 to 1000 is 500445

	d) nmuber of instructions (main): 19
	   number of bytes (main): 58
	   offset : 27 (main+27)
 
	e) S = 500445
	   &S = 0x804c01c
	   Msg = "The sum from 11 to %d is %d\n"
	   &Msg = 0x804c020
           After I set the value of variable S to 99, the programme prints :
	   "The sum from 11 to 1000 is 99" 

# Exercise 2 :
	a) The sum from 11 to 1000 is 500445

	b) main function consists of 28 assembly instructions 
	
	d) 29 assembly instructions 
	   98 bytes
	   15 (offset used)
	
	e) Sum = 500445
	   &Sum = 0x804c024
	   n = 10
	   &n = 0x804c01c
	   After I set the value of variable Sum to 99, the programme prints :
	   "The sum from 11 to 1000 is 500445" 
		
	f) The sum from 11 to 1000 is 495450

# Exercise 3 :
	a) The sum from 11 to 1000 is 495450

	b) main consists of 26 assembly instructions	

	c) The sum from 11 to 1000 is 500445

## --------------------------------------------------------------------------

## Assignment 5: C and Assembly Code Tutorial: Computing Sums

## Make Repository Private and Add TAs as Members
You can make the repo private and add TAs as members by hand or using
the private.py script

### By Hand
1. Go to Project Settings -> General
2. Visibility
3. Change Project Visibility to Private

Also add the TA in your project
1. Go to ProjectSettings -> Members
2. Add Iacovos Kolokasis as a Developer

### Using the Script

The private.py script is written in [Python 3](https://www.python.org/). 
To run private.py script, please have 
**Python 3.4 or higher**, **Git 1.8 or higher** and **python-gitlab** installed.

* Install gitlab lib
```
pip3 install --upgrade python-gitlab --user
```

* Run the script
```
python3 private.py -t <personal token> -p <project_ id>
```
## Submission
* You should submit the source files of each assignment. Do not submit the object or executable file
* Commit all files (not executables or object files!)

```
git add file1.c file2.c file3.c
git commit -m "Commit message"
git push
```
