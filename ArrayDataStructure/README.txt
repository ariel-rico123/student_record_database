############################# WARNING #############################
THE FOLLOWING PROGRAM WILL ONLY WORK IF COMPILED WITH C99.
USE THE FOLLOWING COMMAND TO COMPILE WITH GCC.
    gcc -std=c99 -o output Lab4.c
############################# WARNING #############################

This program stores and manipulates student records.
Each student record stores the following information:
1. Student first name (max. 20 characters)
2. Student last name, (max. 20 characters)
3. Student scores (float/double), e.g. 85.4

The user enters the initial number of records to be stored, 
then enters the information for each record, with the format of 
firstname, lastname, and score, separated by a space. 
Example: 
FirstName LastName Score

The program then provides 8 functions to the user:

1. Print records – prints records of all students
2. Add a new record – take a new record from the user for a new student.
3. Delete record(s) – to delete a record, enter the last name of the student. If there are
multiple students with same last name, all of their records will be deleted. 
4. Search by last name – prints record of the student with a given last name. If there are
multiple students with the same last name, prints records for all of them.
5. Sort by score – sort the records of students according to their scores, and then print the
sorted records. 
6. Sort by last name – sort the records of students according to their names alphabetically, and
then print the sorted records.
7. Find the median score – compute the median score and print it. Also, print how many students are
above this median score.
8. Exit the program – terminate the program on the input of 0 from the user.