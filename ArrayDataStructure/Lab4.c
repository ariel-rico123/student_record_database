#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printMenu();
void printRecords(int number, char **firstnames, char **lastnames, double *scores);
void addRecord(int *number, char ***firstnames, char ***lastnames, double **scores, char *input, int buffer, int length);
bool findLastName(char *lastname, int number, char **lastnames, int **indexes, int *count);
void searchForStudents(int number, char **firstnames, char **lastnames, double *scores);
void swapRecords(int a, int b, char **firstnames, char **lastnames, double *scores);
void deleteRecords(int *number, char ***firstnames, char ***lastnames, double **scores);
void sortByLastName(int number, char **firstnames, char **lastnames, double *scores);
void sortByScore(int number, char **firstnames, char **lastnames, double *scores);
void computeMedianScore(int number, char **firstnames, char **lastnames, double *scores);

int main()
{
    int number, length = 20, buffer = 80, command;
    double *scores;
    char **firstnames, **lastnames, *input;
    bool exit = false;

    printf("\nPlease indicate number of records you want to enter (min 5, max 15): ");
    scanf("%d", &number);

    /*  Intializing size of arrays based on user input  */
    firstnames = (char**)malloc(number*sizeof(char*));
    lastnames = (char**)malloc(number*sizeof(char*));
    scores = (double*)malloc(number*sizeof(double));

    /*  Inputting intial student records    */
    printf("\nPlease input records of students (enter a new line after each record), with following format: FirstName LastName Score\n");
    for(int i=0; i<number; i++)
    {
        /*  Parsing the data in each input to their respective arrays   */
        input = (char*)malloc(buffer*sizeof(char));
        //Program seems to register a keystroke from Enter as 2 keystrokes/2 newline characters.
        if(i==0) fgets(input, buffer, stdin);   //So this is an extra gets() to catch the extra newline character. It serves no other purpose.
        printf("%d. ", i+1);
        fgets(input, buffer, stdin);

        firstnames[i] = strtok(input," ,");
        lastnames[i] = strtok(NULL, " ,");
        scores[i] = atof(strtok(NULL, " ,"));

        //Max of 20 characters
        if(strlen(firstnames[i]) > length)
        {
            /* partial copy (only 20 chars): */
            strncpy(firstnames[i], firstnames[i], length);
            firstnames[i][length] = '\0';   /* null character manually added */
        }
        //Max of 20 characters
        if(strlen(lastnames[i]) > length)
        {
            /* partial copy (only 20 chars): */
            strncpy(lastnames[i], lastnames[i], length);
            lastnames[i][length] = '\0';   /* null character manually added */
        }
    }

    /*  Infinite Loop to Run Program    */
    while(!exit)
    {
        puts("");
        printMenu();
        scanf("%d", &command);
        /*  Switch structure to execute user commands   */
        switch (command)
        {
        case 0:
            exit = true;
            puts("Good Bye!\n");
            break;
        case 1:
            printRecords(number, firstnames, lastnames, scores);
            break;
        case 2:
            addRecord(&number, &firstnames, &lastnames, &scores, input, buffer, length);
            break;
        case 3:
            deleteRecords(&number, &firstnames, &lastnames, &scores);
            break;
        case 4:
            searchForStudents(number, firstnames, lastnames, scores);
            break;
        case 5:
            sortByScore(number, firstnames, lastnames, scores);
            break;
        case 6:
            sortByLastName(number, firstnames, lastnames, scores);
            break;
        case 7:
            computeMedianScore(number, firstnames, lastnames, scores);
            break;
        default:
            break;
        }
    }
    return 0;
}

void printMenu()
{
    puts("Enter a command to continue...\n");
    puts("1) Print records\t(Enter 1)");
    puts("2) Add a new record\t(Enter 2)");
    puts("3) Delete record(s)\t(Enter 3)");
    puts("4) Search by last name\t(Enter 4)");
    puts("5) Sort by score\t(Enter 5)");
    puts("6) Sort by last name\t(Enter 6)");
    puts("7) Find median score\t(Enter 7)");
    puts("0) Exit the program\t(Enter 0)");
    puts("");
}

void printRecords(int number, char **firstnames, char **lastnames, double *scores)
{
    puts("Student Records: ");
    for(int i=0; i<number; i++)
    {
        printf("%d. First Name: %s\t Last Name: %s\t Score: %f\n", i+1, firstnames[i], lastnames[i], scores[i]);
    }
}

void addRecord(int *number, char ***firstnames, char ***lastnames, double **scores, char *input, int buffer, int length)
{
    *number += 1;
    /*  Resizing size of arrays to add record  */
    *firstnames = (char**)realloc(*firstnames,*number*sizeof(char*));
    *lastnames = (char**)realloc(*lastnames, *number*sizeof(char*));
    *scores = (double*)realloc(*scores, *number*sizeof(double));
    /*  Take user input  */
    input = (char*)malloc(buffer*sizeof(char));
    //Program seems to register a keystroke from Enter as 2 keystrokes/2 newline characters.
    fgets(input, buffer, stdin);   //So this is an extra gets() to catch the extra newline character. It serves no other purpose.
    puts("Please enter the record of the student with following format: FirstName LastName Score");
    printf("%d. ", *number);
    fgets(input, buffer, stdin);

    /*  Parsing the data in each input to their respective arrays   */
    (*firstnames)[*number-1] = strtok(input," ,");
    (*lastnames)[*number-1] = strtok(NULL, " ,");
    (*scores)[*number-1] = atof(strtok(NULL, " ,"));

    //Max of 20 characters
    if(strlen((*firstnames)[*number-1]) > length)
    {
        /* partial copy (only 20 chars): */
        strncpy((*firstnames)[*number-1], (*firstnames)[*number-1], length);
        (*firstnames)[*number-1][length] = '\0';   /* null character manually added */
    }
    //Max of 20 characters
    if(strlen((*lastnames)[*number-1]) > length)
    {
    /* partial copy (only 20 chars): */
    strncpy((*lastnames)[*number-1], (*lastnames)[*number-1], length);
    (*lastnames)[*number-1][length] = '\0';   /* null character manually added */
    }
    puts("Record added. ");
}

bool findLastName(char *lastname, int number, char **lastnames, int **indexes, int *count)
{
    *count = 0;
    for(int i=0; i<number; i++)
    {
        if(strcmp(lastname, lastnames[i]) == 0) *count+=1;
    }
    if(*count == 0) return false;
    else
    {
        *indexes = (int*)malloc(*count*sizeof(int));
        *count = 0;
        for(int i=0; i<number; i++)
        {
            if(strcmp(lastname, lastnames[i]) == 0)
            {
                (*indexes)[*count] = i;
                *count+=1;
            }
        }
        return true;
    }
}

void searchForStudents(int number, char **firstnames, char **lastnames, double *scores)
{
    int *indexes, count;
    bool found;
    char *lastname = (char*)malloc(21*sizeof(char));
    printf("Enter the last name of the student(s) you are searching for: ");
    scanf ("%20s",lastname);
    found = findLastName(lastname, number, lastnames, &indexes, &count);
    if(!found) printf("The student(s) %s was not found.\n", lastname);
    else
    {
        printf("The student(s) %s was found.\n", lastname);
        puts("Student Records: ");
        for(int i=0; i<count; i++)
        {
            printf("%d. First Name: %s\t Last Name: %s\t Score: %f\n", i+1, firstnames[indexes[i]], lastnames[indexes[i]], scores[indexes[i]]);
        }
        free(indexes);
    }
    free(lastname);
}

void swapRecords(int a, int b, char **firstnames, char **lastnames, double *scores)
{
    char *tempfirst;
    char *templast;
    double tempscore;

    //Saving record A
    tempfirst = firstnames[a];
    templast = lastnames[a];
    tempscore = scores[a];

    //Copying record B to record A
    firstnames[a] = firstnames[b];
    lastnames[a] = lastnames[b];
    scores[a] = scores[b];

    //Transfering record A to record B
    firstnames[b] = tempfirst;
    lastnames[b] = templast;
    scores[b] = tempscore;
}

void deleteRecords(int *number, char ***firstnames, char ***lastnames, double **scores)
{
    int *indexes, count;
    bool found;
    char *lastname = (char*)malloc(21*sizeof(char));
    printf("Enter the last name of the student(s) you want to delete the record(s) for: ");
    scanf ("%20s",lastname);
    found = findLastName(lastname, *number, *lastnames, &indexes, &count);
    if(!found) printf("The student(s) %s was not found.\n", lastname);
    else
    {
        printf("The student(s) %s was found.\n", lastname);
        /*  Records to be deleted moved to the end  */
        for(int i=(count-1); i>=0; i--)
        {
            for(int j=indexes[i]; j<(*number-1); j++)
            {
                swapRecords(j, (j+1), *firstnames, *lastnames, *scores);
            }

        }
        free(indexes);
        /*  Free the memory storing the names   */
        //  Note: The memory block that firstnames[i] points to also contains the lastname (the block of size buffer from the allocated input memory).
        for(int i=(*number-1); i>=(*number-count); i--)
            free((*firstnames)[i]);
        /*  Resize the arrays containing the records, deleting the records  */
        *number -= count;
        *firstnames = (char**)realloc(*firstnames,*number*sizeof(char*));
        *lastnames = (char**)realloc(*lastnames, *number*sizeof(char*));
        *scores = (double*)realloc(*scores, *number*sizeof(double));
        printf("The record(s) for the student(s) %s was deleted.\n", lastname);
    }
    free(lastname);
}

void sortByLastName(int number, char **firstnames, char **lastnames, double *scores)
{
    bool swap = true;
    //Bubble Sort
    while(swap == true)
    {
        swap = false;
        for(int i=0; i<(number-1); i++)
        {
            if ((strcmp(lastnames[i], lastnames[i+1]) > 0) || ((strcmp(lastnames[i], lastnames[i+1]) == 0) && (strcmp(firstnames[i], firstnames[i+1]) > 0)))
            {
                swapRecords(i, i+1, firstnames, lastnames, scores);
                swap = true;
            }
        }
    }
    puts("Record(s) were sorted by last name.");
    printRecords(number, firstnames, lastnames, scores);
}

void sortByScore(int number, char **firstnames, char **lastnames, double *scores)
{
    bool swap = true;
    //Bubble Sort
    while(swap == true)
    {
        swap = false;
        for(int i=0; i<(number-1); i++)
        {
            if (scores[i] < scores[i+1])
            {
                swapRecords(i, i+1, firstnames, lastnames, scores);
                swap = true;
            }
        }
    }
    puts("Record(s) were sorted by score.");
    printRecords(number, firstnames, lastnames, scores);
}

void computeMedianScore(int number, char **firstnames, char **lastnames, double *scores)
{
    double median;
    int counter = 0;
    sortByScore(number, firstnames, lastnames, scores);
    if(number%2==1)
        median = scores[(number-1)/2];
    else
        median = (scores[number/2] + scores[(number/2)-1]) /2;
    printf("The calculated median score is %f.\n", median);
    for(int i=0; i<number; i++)
    {
        if(scores[i]>median) counter++;
    }
    printf("There are %d student(s) above the median score of %f", counter, median);
}
