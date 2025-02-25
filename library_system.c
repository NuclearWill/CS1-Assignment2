#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_NAME 50

// Class Declarations

typedef struct node_s{
    struct node_s* nextNode;

    // book variables
    char* bookTitle;
    char* borrowLast;
    char* borrowFirst;
} node_t;

// Function prototypes
node_t *borrowBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output);
node_t *returnBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output);
void checkBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output);
void displayBorrowedBooks(node_t *head, FILE *output);
void freeList(node_t *head, FILE *output);

void readFileCommands(FILE* input);

void displayError(FILE* file, int errorNum);

// Main function
int main(int argc, char** argv){

    // make linked list
    node_t* head;

    // open input file
    FILE* input;

    input = fopen("test_input1.txt", "r");

    // checks to see if the file exists. If it doesn't, it ouputs an error and ends the program.
    if(input == NULL){
        displayError(input, 1);
    }
    
    readFileCommands(input);
}


//  functions

void readFileCommands(FILE* input){

    // function variables
    char command = '0';

    char bookTitle[MAX_TITLE];
    char lastName[MAX_NAME];
    char firstName[MAX_NAME];

    // reads commands
    while((command = fgetc(input)) != EOF){
        switch(command){
            case '1':
                printf("Case 1 detected\n");
                fscanf(input, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);
                break;

            case '2':
                printf("Case 2 detected\n");
                break;

            case '3':
                printf("Case 3 detected\n");
                break;

            case '4':
                printf("Case 4 detected\n");
                break;

            case '5':
                printf("Case 5 detected\n");
                fclose(input);
                return;

            case '\n':
                break;

            default:
                displayError(input, 2);
        }
    } 

    displayError(input, 3);
}

void displayError(FILE* file, int errorNum){

    if(errorNum != 1) fclose(file);

    switch(errorNum){
        case 1:
            printf("ERROR: Input file not found. Ending prematurely\n");
            break;
        case 2:
            printf("ERROR: file command not recognized. Ending prematurely\n");
            break;
        case 3:
            printf("ERROR: Reached end of file without close command. Ending prematurely\n");
            break;
        case 4:
            printf("Case 4 detected\n");
            break;
        case 5:
            printf("Case 5 detected\n");
            break;
    }

    exit(errorNum);
}


// Hint: To read the book title, author's first name, and author's last name,  
// you can use:  
// fscanf(file, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);  
// Alternatively, you can use fgets() to read the entire line and then parse it.
