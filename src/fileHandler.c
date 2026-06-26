#include <stdio.h>
#include <string.h>
#include "fileHandler.h"
#include "linkedListHandler.h"

#define LOG_FILE "/workspaces/AO2_financial_tracker/logs/transaction_log.txt"

void save_transactions(void) {
    FILE *file = fopen(LOG_FILE, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing\n");
        return;
    }
    
    TransactionNode *current = head;
    while (current != NULL) {
        fprintf(file, "%s|%.2f|%s\n", current->description, current->amount, current->status);
        current = current->next;
    }
    
    fclose(file);
    printf("Transactions saved successfully!\n");
}

void load_transactions(void) {
    FILE *file = fopen(LOG_FILE, "r");
    if (file == NULL) {
        printf("No previous transactions found. Starting program.\n");
        return;
    }
    
    char line[300];
    char description[100], status[20];
    double amount;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        
        //scans each line for anything fitting the format of some text|some number|some text
        if (sscanf(line, "%99[^|]|%lf|%19[^|]", description, &amount, status) == 3) {
            TransactionNode *new_node = create_transaction_node(description, amount, status);
            if (new_node != NULL) {
                insert_node_at_position(new_node, count_transactions() + 1);
            }
        }
    }
    
    fclose(file);
    printf("Previous transactions loaded.\n");
}