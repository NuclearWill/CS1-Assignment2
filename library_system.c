/*
* Author: Peter Thomsen
* Course: CS1
* Assignment: Assignment 2
* Date: Spring 2025
*/

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

void readFileCommands(FILE* input, FILE* output, node_t* head);

void freeNode(node_t* node);

void displayError(FILE* file, int errorNum);

// Main function
int main(int argc, char** argv){

    // make linked list head
    node_t* head = NULL;

    // creates and opens input and output files
    FILE* input;
    FILE* output;

    input = fopen("library_records-1.txt", "r");
    output = fopen("output.txt", "w");

    // checks to see if the file exists. If it doesn't, it ouputs an error and ends the program.
    if(input == NULL){
        displayError(input, 1);
    }
    
    readFileCommands(input, output, head);
}


//  functions
void readFileCommands(FILE* input, FILE* output, node_t* head){

    // function variables
    char command = '0';

    char bookTitle[MAX_TITLE];
    char lastName[MAX_NAME];
    char firstName[MAX_NAME];

    // reads commands
    while((command = fgetc(input)) != EOF){
        switch(command){
            case '1':
                fscanf(input, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);
                head = borrowBook(head, bookTitle, lastName, firstName, output);
                break;

            case '2':
                fscanf(input, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);
                head = returnBook(head, bookTitle, lastName, firstName, output);
                break;

            case '3':
                fscanf(input, " \"%[^\"]\" %s %s", bookTitle, lastName, firstName);
                checkBook(head, bookTitle, lastName, firstName, output);
                break;

            case '4':
                displayBorrowedBooks(head, output);
                break;

            case '5':
                freeList(head, output);
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

node_t *borrowBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output){
    printf("Activate borrowBook Command\n");

    // creating a new node
    // allocating memory for the new node
    node_t* newNode = (node_t*) malloc(sizeof(node_t));

    //allocating memory for the book title and the borrowers first and last name
    newNode->bookTitle = (char*) malloc(sizeof(char) * MAX_TITLE);
    newNode->borrowLast = (char*) malloc(sizeof(char) * MAX_NAME);
    newNode->borrowFirst = (char*) malloc(sizeof(char) * MAX_NAME);

    //assigning the input values to the new node
    strcpy(newNode->borrowLast, lastName);
    strcpy(newNode->bookTitle, title);
    strcpy(newNode->borrowFirst, firstName);
    newNode->nextNode = NULL;


    // adding the new node at the end of the linked list
    // if the head is empty, makes the new node the head
    if(head == NULL){
        head = newNode;
    }
    // else, searches through the linked list until it finds the last node without a next node and adds the new book at the end of the list
    else{
        node_t* tempNode = head;
        while(tempNode->nextNode != NULL){
            tempNode = tempNode->nextNode;
        }
        tempNode->nextNode = newNode;
    }

    // file output
    fprintf(output, "Borrowed \"%s\" by %s, %s\n", title, lastName, firstName);

    // returns the head of the modified linked list
    return head;
}
node_t *returnBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output){
    printf("Activate returnBook Command\n");

    // cancels the command if the head is NULL
    if(head == NULL){
        printf("No books to return\n");
        return head;
    }

    // if the head is the returned book, frees the head and then makes the next node the head
    if(strcmp(head->bookTitle, title) == 0){
        printf("Head book: %s with borrower %s, %s matches book \"%s\" to be returned\n", head->bookTitle, head->borrowLast, head->borrowFirst, title);

        // temp node created to temporarily hold onto the rest of the linked list
        // still functions even if the next node after head is NULL
        node_t* tempNode = head->nextNode;

        freeNode(head);

        // makes the second node the new head node
        head = tempNode;

        return head;
    }
    // if the head isn't the returned book, tries to find the returned book through the rest of the list
    else{
        node_t* searchNode = head;
        // loops through each item in the linked list until one matches the inputted title
        do{
            if(strcmp(searchNode->nextNode->bookTitle, title) == 0){
                printf("Book: %s with borrower %s, %s matches book \"%s\" to be returned\n", searchNode->nextNode->bookTitle, searchNode->nextNode->borrowLast, searchNode->nextNode->borrowFirst, title);
                
                // creates a temporary node to save the rest of the list after the returned node
                node_t* tempNode = NULL;
                // changes the temp node to not be NULL only if there is more list after the returning node
                if(searchNode->nextNode->nextNode != NULL) 
                    tempNode = searchNode->nextNode->nextNode;
                
                freeNode(searchNode->nextNode);

                // if a next node for the destroyed node was found, saves it as the next node for the previous node
                if(tempNode != NULL)
                    searchNode->nextNode = tempNode;
                // if there was no next node, saves the next node of the previous node as NULL;
                else
                    searchNode->nextNode = NULL;

                // file output
                fprintf(output, "Returned \"%s\" by %s, %s\n", title, lastName, firstName);

                // returns the head of the modified linked list
                return head;
            }
            searchNode = searchNode->nextNode;
        }while(searchNode != NULL);
    }

    printf("Book %s not found to be returned\n", title);
    return head;
}
void checkBook(node_t *head, char *title, char *lastName, char *firstName, FILE *output){
    printf("Activate checkBook Command\n");

    if(head == NULL){
        printf("No books to check\n");
        return;
    }

    node_t* searchNode = head;
    
    do{
        if(strcmp(searchNode->bookTitle, title) == 0){
            // debug log output
            printf("Book: %s with borrower %s, %s is being borrowed\n", searchNode->bookTitle, searchNode->borrowLast, searchNode->borrowFirst);
            // file output
            fprintf(output, "\"%s\" is borrowed by %s, %s\n", title, lastName, firstName);

            return;
        }
        searchNode = searchNode->nextNode;
    }while(searchNode != NULL);

    // debug log output
    printf("Book: %s with borrower %s, %s is NOT being borrowed\n", title, lastName, firstName);
    // file output
    fprintf(output, "\"%s\" is not currently borrowed by %s, %s\n", title, lastName, firstName);

    return;
}
void displayBorrowedBooks(node_t *head, FILE *output){
    printf("Activate displayBorrowedBooks Command\n");

    // checks to see if there are even any books to display and outputs a warning if not
    if(head == NULL){
        printf("No books to display\n");
        return;
    }

    // beginning of file output list
    fprintf(output, "Borrowed Books List:\n");

    node_t* searchNode = head;
    int count = 0;
    
    // goes through the entire list until it the next node is NULL, outputting each book
    do{
        count++;

        // debug log output
        printf("Book: %s with borrower %s, %s\n", searchNode->bookTitle, searchNode->borrowLast, searchNode->borrowFirst);

        // file output
        fprintf(output, "%d. \"%s\" - %s, %s\n", count, searchNode->bookTitle, searchNode->borrowLast, searchNode->borrowFirst);

        searchNode = searchNode->nextNode;
    }while(searchNode != NULL);

    return;
}
void freeList(node_t *head, FILE *output){
    printf("Activate freeList Command\n");

    // searchNode is the node actively going through the linked list
    node_t* searchNode = head;
    // burnNode is the node that is to be freed. It is seperate so that way searchNode always is within the list so the rest can be freed
    node_t* burnNode;
    
    // goes through the entire list freeing the memory of each node as it goes until it reaches the end
    do{
        // assigns the current node to be freed
        burnNode = searchNode;

        //bumps up searchNode to the next node in the list
        searchNode = searchNode->nextNode;

        //frees burnNode
        free(burnNode);
    }while(searchNode != NULL);

    // file output
    fprintf(output, "Thank you for using the Library System!");

    return;
}

void freeNode(node_t* node){
    // frees dynamic strings attached to node
    free(node->bookTitle);
    free(node->borrowLast);
    free(node->borrowFirst);

    //frees the node itself
    free(node);

    return;
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