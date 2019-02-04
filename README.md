# SimpleDatabase
## Assignment objective:

You are to implement a simple database using a sorted file of fixed length records. The data that you are to use for testing is in file: input.txt. This data comes from Wages and Education of Young Males. The goal of this assignment is to understand and practice using file management techniques to implement a database system.
Your file needs to handle overflow in anyway you choose. You must implement a way to detect that overflow has exceeded some threshold and that the file needs to be reorganized. When that happens, your program must reorganize the file so that the overflow records are merged back in with the sorted records.. You may design your file so that you have a sorted area at the top and an unsorted overflow area at the bottom. Whenever the overflow area becomes X% as large as the sorted area, the file is resorted. New records are appended at the end.

Or, you may choose to create a mostly blank file initially, with M blank records. Insertions are done in a sorted fashion, and records inserted into the appropriate blank areas. When a blank area is not available, the file is rewritten to add M blank records after every real one again, increasing the file size.

Or, you may want to put overflows in a second overflow record and have an overflow pointer from the original file. Whenever the overflow file becomes X% as large as the sorted file, the two are recombined.

## Program Description
Create a program which offers the user the following menu of operations :

1) Create new database  
2) Open database  
3) Close database  
4) Display record  
5) Update record  
6) Create report  
7) Add record  
8) Delete record  
9) Quit  

## Compiling and running

### Compile:
`
g++ SimpleDatabase.cpp -o SimpleDatabase
`

### Run:
Type the following in the windows command prompt:

`
SimpleDatabase.exe
`
