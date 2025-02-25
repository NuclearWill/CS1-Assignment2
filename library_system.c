#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_NAME 50

// Class Declarations

typedef struct node_s{
    node_t* nextNode;

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

// Main function
int main(int argc, char** argv){

    // make linked list
    node_t* head;

    // open input file
    FILE* input;

    input = fopen("test_input1.txt", "r");

    if(input == NULL){
        printf("ERROR: Input file not found. Ending prematurely\n");
        return 1;
    }

    do {
        switch(){
            case 1:
                printf("Case 1 detected\n");
                break;
            case 2:
                printf("Case 2 detected\n");
                break;
            case 3:
                printf("Case 3 detected\n");
                break;
            case 4:
                printf("Case 4 detected\n");
                break;
            case 5:
                printf("Case 5 detected\n");
                break;
            default:
                printf("ERROR: file command not recognized. Ending prematurely\n");
                return 1;
                break;
        }
    } while(1);

    return 0;
}

//  functions

// Hint: To read the book title, author's first name, and author's last name,  
// you can use:  
// fscanf(file, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);  
// Alternatively, you can use fgets() to read the entire line and then parse it.
