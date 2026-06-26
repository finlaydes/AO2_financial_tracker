#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListHandler.h"
#include "fileHandler.h"

//function to save contents of the linked list to file and free all memory
void cleanup(void) {
    TransactionNode *current = head;
    while (current != NULL) {
        strcpy(current->status, "saved");
        current = current->next;
    }
    
    save_transactions();
    
    current = head;
    while (current != NULL) {
        TransactionNode *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

double get_total_money(void) {
    double total = 0.0;
    TransactionNode *current = head;

    while (current != NULL) {
        total += current->amount;
        current = current->next;
    }

    return total;
}

//function to display menu
void display_menu(void) {
    double balance = get_total_money();

    printf("\n--- Personal Finance Tracker Menu ---\n");
    printf("1. Add Income\n");
    printf("2. Add Expense\n");
    printf("3. Delete\n");
    printf("4. Print\n");
    printf("5. Exit\n");
    printf("--------------------------------------\n");
    printf("Current balance: $%.2f\n", balance);
    if (balance < 0.0) {
        printf("Budget status: Over budget\n");
    } else{
        printf("Budget status: Within budget\n");
    }
    printf("Select an option (1-5): ");
}

//main function
int main(void){
    char resumePreviousSession[256];
    char choice[10];
    
    printf("Welcome to your Personal Finance Tracker!\n");
    printf("Would you like to resume your previous session? (y/n): ");

    fgets(resumePreviousSession, sizeof(resumePreviousSession), stdin);
    
    if (resumePreviousSession[0] == 'y' || resumePreviousSession[0] == 'Y') {
        printf("Resuming from last session...\n");
        load_transactions();
    } else {
        printf("Starting a new session...\n");
    }

    //main menu loop
    while (1) {
        display_menu();
        fgets(choice, sizeof(choice), stdin);
        
        switch(choice[0]) {
            case '1':
                add_income();
                break;
            case '2':
                add_expense();
                break;
            case '3':
                delete_transaction();
                break;
            case '4':
                print_transactions();
                break;
            case '5':
                cleanup();
                printf("Done. Exiting program.\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
    exit(0);
}
