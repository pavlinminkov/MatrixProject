#Matrix Calculator
Simple matrix calculator which aims to simplify some of the basic calculations for working with matrices.

##Table of contents
*[How to use](#how-to-use)
*[Operations with two matrices](#operations-with-two-matrices)
*[Operations with one matrix](#operations-with-one-matrix)
*[Warnings](#warnings)

##How to use
Write out the matrices in a text file like shown below. You can leave as many spaces as you want between numbers but make sure that the lines are straight and the amount of numbers is the same in each row. After the matrix leave a space and then write the operator if you want to work with two matrices or don't leave a space and just write out the operator if you plan to work with on matrix. There will be more examples int the showcase of the operations. You can write out as many operations as you want, as long as you seperate each one with an Enter and the file doesn't get longer than 100 lines. After you are ready with the file save it in the directory of matrix.cpp, compile the program with GCC and write the name of the file in the console when you are asked to do so. All operations will be printed out in the console. You can use the include file.txt to test out the program.

###Examples:

####One matrix:

|9 8 7|X23
|6 5 4|
|3 2 1|

|9 8 7|T
|6 5 4|
|3 2 1|
|3 1 2|

####Two matrices

|1.5  2  3| X |9 8 7 1 2|
|  4  5  6|   |6 5 4 2 4|
|  7  8  9|   |3 2 1 3 5|

|1 2  35| + |9 8 7|
|3 5  61|   |6 5 4|
|7 8 925|   |3 2 1|

##Operations with two matrices

###Multiplication

|1.5  2  3| X |9 8 7 1 2|
|  4  5  6|   |6 5 4 2 4|
|  7  8  9|   |3 2 1 3 5|

###Addition

|1 2  35| + |9 8 7|
|3 5  61|   |6 5 4|
|7 8 925|   |3 2 1|

##Operations with one matrix

###Multiplication

|9 8 7|X23
|6 5 4|
|3 2 1|

###Division

|9 8 7|/10
|6 5 4|
|3 2 1|

###Transposition

|9 8 7|T
|6 5 4|
|3 2 1|
|3 1 2|

###Determinant

|9 8 7|D
|6 3 4|
|3 2 1|

###Inversion

|2 4 6 7|-1
|5 1 8 8|
|1 7 3 4|
|3 9 2 4|

##Warning
*Don't leave unnecessary empty spaces.
*Don't write out matrices with uneven borders.
*Don't try to use files with over 100 lines.