############################# WARNING #############################
THE FOLLOWING PROGRAM WILL ONLY WORK IF COMPILED WITH C99.
USE THE FOLLOWING COMMAND TO COMPILE WITH GCC.
    gcc -std=c99 -o output Lab5.c
############################# WARNING #############################

This program stores and manipulates student records.
Each student record stores the following information:
1. Student first name (max. 20 characters)
2. Student last name, (max. 20 characters)
3. Student scores (float/double), e.g. 85.4
4. Zip code (may be a string)

The user enters the initial number of records to be stored, 
then enters the information for each record, with the format of 
firstname, lastname, score, and zipcode, separated by a space. 
Example: 
FirstName LastName Score ZipCode

The program then provides 7 functions to the user:

1. Print records – prints records of all students
2. Add a new record – take a new record from the user for a new student.
3. Delete record(s) – to delete a record, enter the last name of the student. If there are
multiple students with same last name, all of their records will be deleted. 
4. Search by zip code – prints records of all students with a given zip code.
5. Search by score range – take two scores max, min; then print records of all students who have
scores between [max, min] (inclusive). 
6. Find the median score – compute the median score and print it. Also, print how many students are
above this median score.
7. Exit the program – terminate the program on the input of 0 from the user.