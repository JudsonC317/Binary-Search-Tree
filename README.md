# Binary-Search-Tree

This was a school project for one of my C programming courses.

This application provides an implementation of a binary search tree. There are drivers provided
to run various tests, with different settings for building the tree.

To run the application, run ./lab5 and follow with the flags for which test driver and settings
you would like to use. Further information about each test driver itself can be found in the lab5.c
comments for each driver.

-u x: run with test driver 'x', using driver 0 through 8.   
-o: run the driver with an optimal tree.  
-r: run with a randomly generated tree.  
-p: run with a poor order for inserting keys.  
-w: set the number of levels in the initial tree.  
-t: set number of access trials.  
-e: run the equilibrium driver.  

Below is a brief description of each file in the application. Further information can be found
in the header comment of each file. 

lab5.c: Contains main loop and test drivers for the binary search tree.  
bst.c: Contains functions for interacting with the binary search tree.  
MP5testScript.c: test script to run several of the drivers to test the functionality of the application.  
bst.h: structure definitions and function prototypes for bst.c.  
makefile: compiles the application.   
