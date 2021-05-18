# The makefile for MP5
# Type:
#		make			-- to build program lab5
#		make clean	-- to delete executable files, object files, and core

lab5 : bst.c lab5.c
	gcc -Wall -g bst.c lab5.c -o lab5 -lm

clean : 
	rm -f *.o lab5 core a.out


