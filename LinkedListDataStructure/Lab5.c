#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Student
{
    char *firstname;
    char *lastname;
    double score;
    char *zipcode;
};

struct Node
{
    struct Student student;
    struct Node *next;
};

void printMenu();
void addRecord(struct Node **head, int number, int buffer, int length);
void printStudent(struct Node *this, int number);
void printRecords(struct Node *head);
void deleteRecords(struct Node **head);
void searchZipCode(struct Node *head);
void searchScoreRange(struct Node *head);
void calculateMedianScore(struct Node *head);

int main()
{
    struct Node *head = NULL;
    int number, length = 20, buffer = 100, command;
    bool exit = false;
    char catch[100];

    /*  Adding intial records   */
    printf("\nPlease indicate number of records you want to enter (min 5): ");
    scanf("%d", &number);
    
    //Program seems to register a keystroke from Enter as 2 keystrokes/2 newline characters.
    fgets(catch, buffer, stdin);   //So this is an extra gets() to catch the extra newline character. It serves no other purpose.
    puts("\nPlease input records of students (enter a new line after each record), with following format: FirstName LastName Score ZipCode");
    for(int i=0; i<number; i++)
    {
        addRecord(&head, i+1, buffer, length);
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
            printRecords(head);
            break;
        case 2:
            //Program seems to register a keystroke from Enter as 2 keystrokes/2 newline characters.
            fgets(catch, buffer, stdin);   //So this is an extra gets() to catch the extra newline character. It serves no other purpose.
            puts("Please enter record of student with following format: FirstName LastName Score ZipCode");
            addRecord(&head, 1, buffer, length);
            puts("Record added. ");
            break;
        case 3:
            deleteRecords(&head);
            break;
        case 4:
            searchZipCode(head);
            break;
        case 5:
            searchScoreRange(head);
            break;
        case 6:
            calculateMedianScore(head);
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
    puts("4) Search by zip code\t(Enter 4)");
    puts("5) Search score range\t(Enter 5)");
    puts("6) Find median score\t(Enter 6)");
    puts("0) Exit the program\t(Enter 0)");
    puts("");
}

void addRecord(struct Node **head, int number, int buffer, int length)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));

    /*  Take user input  */
    char *input = (char*)malloc(buffer*sizeof(char));
    printf("%d. ", number);
    fgets(input, buffer, stdin);

    /*  Parsing the data into temporary Node structure   */
    temp->student.firstname = strtok(input," ,");
    temp->student.lastname = strtok(NULL, " ,");
    temp->student.score = atof(strtok(NULL, " ,"));
    temp->student.zipcode = strtok(NULL, " ,");

    //Max of 20 characters
    if(strlen(temp->student.firstname) > length)
    {
        /* partial copy (only 20 chars): */
        strncpy(temp->student.firstname, temp->student.firstname, length);
        (temp->student.firstname)[length] = '\0';   /* null character manually added */
    }
    //Max of 20 characters
    if(strlen(temp->student.lastname) > length)
    {
        /* partial copy (only 20 chars): */
        strncpy(temp->student.lastname, temp->student.lastname, length);
        (temp->student.lastname)[length] = '\0';   /* null character manually added */
    }

    /*  Adding temp Node to the back of the Link-List   */
    struct Node *runner = *head;
    //If Link-List is empty, set temp as head
    if(runner == NULL)
    {
        *head = temp;
        (*head)->next = NULL;
        return;
    }
    //Else, move to the end of the Link-List and add temp
    while(runner->next != NULL)
    {
        runner = runner->next;
    }
    runner->next = temp;
    temp->next = NULL;
}

void printStudent(struct Node *this, int number)
{
    printf("%d. First Name: %s\t Last Name: %s\t Score: %f\t Zip Code: %s", number, this->student.firstname, this->student.lastname, this->student.score, this->student.zipcode);
}

void printRecords(struct Node *head)
{
    struct Node *runner = head;
    int number = 1;
    puts("Student Records: ");
    while(runner!=NULL)
    {
        printStudent(runner, number);
        runner = runner->next;
        number++;
    }
}

void deleteRecords(struct Node **head)
{
    struct Node *temp, *runner;
    bool found = false;
    /*  Input Last Name  */
    char *lastname = (char*)malloc(21*sizeof(char));
    printf("Enter the last name of the student(s) you want to delete the record(s) for: ");
    scanf("%20s",lastname);
    if(*head!=NULL)
    {  
        /*  While head has last name, delete and move new head  */
        while(strcmp(lastname, (*head)->student.lastname) == 0)
        {
            found = true;
            temp = *head;
            *head = (*head)->next;
            free(temp->student.firstname);
            free(temp);
        }
        /*  Move through the rest of the Link-List and delete records with last name  */
        if(*head!=NULL)
        {
            runner = *head;
            while(runner->next!=NULL)
            {
                if(strcmp(lastname, runner->next->student.lastname) == 0)
                {
                    found = true;
                    temp = runner->next;
                    runner->next = temp->next;
                    free(temp->student.firstname);
                    free(temp);
                }
                else
                {
                    runner = runner->next;
                }
            }
        }
    }
    if(found) printf("The record(s) for the student(s) %s was deleted.\n", lastname);
    else printf("The record(s) for the student(s) %s was not found.\n", lastname);
    free(lastname);
}

void searchZipCode(struct Node *head)
{
    struct Node *runner = head;
    int number = 1;
    bool found = false;
    /*  Input Last Name  */
    char *zipcode = (char*)malloc(20*sizeof(char));
    //Program seems to register a keystroke from Enter as 2 keystrokes/2 newline characters.
    fgets(zipcode, 20, stdin);   //So this is an extra gets() to catch the extra newline character. It serves no other purpose.
    printf("Enter the zip code of the student(s) you want to search the record(s) for: ");
    fgets(zipcode, 20, stdin);

    puts("Student Records: ");
    while(runner!=NULL)
    {
        if(strcmp(zipcode, runner->student.zipcode) == 0)
        {
            found = true;
            printStudent(runner, number);
            number++;
        }
        runner = runner->next;
    }
    if(!found) printf("The record(s) for the zip code %s was not found.\n", zipcode);
    free(zipcode);
}

void searchScoreRange(struct Node *head)
{
    struct Node *runner = head;
    int max, min, number = 1;
    bool found = false;
    /*  Input Score Range  */
    printf("Enter the max of the score range you want to search the record(s) for: ");
    scanf("%d", &max);
    printf("Enter the min of the score range you want to search the record(s) for: ");
    scanf("%d", &min);

    puts("Student Records: ");
    while(runner!=NULL)
    {
        if((runner->student.score<=max)&&(runner->student.score>=min))
        {
            found = true;
            printStudent(runner, number);
            number++;
        }
        runner = runner->next;
    }
    if(!found) printf("The record(s) for the score range %d to &d was not found.\n", min, max);
}

void calculateMedianScore(struct Node *head)
{
    struct Node *runner = head;
    double *scores = NULL;
    int number = 0;
    /*  Copying the scores  */
    while(runner!=NULL)
    {
        number++;
        scores = (double*)realloc(scores, number*sizeof(double));
        scores[number-1] = runner->student.score;
        runner = runner->next;
    }
    /*  Sorting the scores  */
    bool swap = true;
    double temp;
    //Bubble Sort
    while(swap == true)
    {
        swap = false;
        for(int i=0; i<(number-1); i++)
        {
            if (scores[i] < scores[i+1])
            {
                //Swap
                temp = scores[i];
                scores[i] = scores[i+1];
                scores[i+1] = temp;
                swap = true;
            }
        }
    }
    /*  Calculating the Median  */
    double median;
    int counter = 0;
    if(number%2==1)
        median = scores[(number-1)/2];
    else
        median = (scores[number/2] + scores[(number/2)-1]) /2;
    printf("The calculated median score is %f.\n", median);
    for(int i=0; i<number; i++)
    {
        if(scores[i]>median) counter++;
    }
    printf("There are %d student(s) above the median score of %f.", counter, median);
    free(scores);
}
