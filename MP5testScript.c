/* MP5testScript.c
 * Judson Cooper
 * MP5
 *
 * This file is a test scipt to quickly test the functionality of MP5. It
 * automatically runs several of the drivers included in the lab5.c file
 * using various settings.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	
	system("./lab5 -o -w 5 -t 0 -v"); // tests inserts only and prints tree 
	puts("\n \n \n ");
	system("./lab5 -r -w 5 -t 0 -v -s 1"); // same with random tree 
	puts("\n \n \n ");
	system("./lab5 -p -w 5 -t 0 -v -s 1"); // same with poor tree 
	puts("\n \n \n ");
	system("./lab5 -o -w 16 -t 50000"); // tests inserts and accesses 
	puts("\n \n \n ");
	system("./lab5 -r -w 16 -t 50000"); // same with random tree 
	puts("\n \n \n ");
	system("./lab5 -p -w 16 -t 50000"); // same with poor tree 
	puts("\n \n \n ");
	system("./lab5 -u x"); // unit test x with removes 
	puts("\n \n \n ");
	system("./lab5 -e -w 5 -t 10 -v -s 2"); // tests random removes 
	puts("\n \n \n ");
	system("./lab5 -e -w 20 -t 100000"); // exercise the tree 
	puts("\n \n \n ");

	system("./lab5 -u 4"); // test replace with duplicate key, and removal of single item
	puts("\n \n \n ");
	system("./lab5 -o"); // test optimal tree
	puts("\n \n \n ");
	system("./lab5 -r"); // test random tree
	puts("\n \n \n ");
	system("./lab5 -p"); // test poor tree
	puts("\n \n \n ");
	system("./lab5 -q"); // test worst tree
	puts("\n \n \n ");
	system("./lab5 -u 7"); // test accuracy of internal path length function
	puts("\n \n \n ");
	system("./lab5 -u 8"); // test accuracy of bst num key comparisons function
	puts("\n \n \n ");

	
	return 0;
}
