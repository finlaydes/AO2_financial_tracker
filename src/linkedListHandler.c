#include "linkedListHandler.h"
#include "fileHandler.h"

// global head pointer for the linked list
TransactionNode *head = NULL;

// function for creating a new transaction node
TransactionNode *create_transaction_node(const char *description, double amount, const char *status) {
    TransactionNode *new_node = (TransactionNode *)malloc(sizeof(TransactionNode));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    strcpy(new_node->description, description);
    new_node->amount = amount;
    strcpy(new_node->status, status);
    new_node->next = NULL;
    
    return new_node;
}

//function to count total transactions
int count_transactions(void) {
    int count = 0;
    TransactionNode *current = head;
    while (current != NULL) {
        count = count + 1;
        current = current->next;
    }
    return count;
}

//function to insert a transaction node at a specific position
void insert_node_at_position(TransactionNode *new_node, int position) {
    if (new_node == NULL) {
        return;
    }

    if (position == 1) {
        new_node->next = head;
        head = new_node;
        return;
    }else{
        TransactionNode *current = head;
        int count = 1;
        while (current != NULL && count < position - 1) {
            current = current->next;
            count = count + 1;
        }
        if (current != NULL) {
        new_node->next = current->next;
        current->next = new_node;
        }
    }
}

//function to add income
void add_income(void) {
    printf("\n--- Add Income ---\n");
    
    char description[100];
    double amount;
    int position;
    int total = count_transactions();
    
    printf("Description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;
    
    printf("Amount: ");
    scanf("%lf", &amount);
    getchar();//clear newline from input buffer, this took me ages to figure out
    
    if (amount <= 0) {
        printf("Error: Income amount must be positive!\n");
        return;
    }
    
    if (total > 0) {
        print_transactions();
        printf("\nEnter position to insert (1-%d or %d to add at end): ", total + 1, total + 1);
        scanf("%d", &position);
        getchar();
        
        if (position < 1 || position > total + 1) {
            printf("Error: Invalid position!\n");
            return;
        }
    } else {
        position = 1;
    }

    char *status;
    if (position == total + 1) {
        status = "new";
    } else {
        status = "+++ i";
    }
    
    TransactionNode *new_node = create_transaction_node(description, amount, status);
    if (new_node != NULL) {
        insert_node_at_position(new_node, position);
        printf("Income added successfully\n");
    }
}

//function to add expense
void add_expense(void) {
    printf("\n--- Add Expense ---\n");
    
    char description[100];
    double amount;
    int position;
    int total = count_transactions();
    
    printf("Description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;
    
    printf("Amount: ");
    scanf("%lf", &amount);
    getchar(); 
    
    if (amount <= 0) {
        printf("Error: Expense amount must be positive!\n");
        return;
    }
    
    if (total > 0) {
        print_transactions();
        printf("\nEnter position to insert (1-%d): ", total + 1);
        scanf("%d", &position);
        getchar();
        
        if (position < 1 || position > total + 1) {
            printf("Error: Invalid position!\n");
            return;
        }
    } else {
        position = 1;
    }
    
    char *status;
    if (position == total + 1) {
        status = "new";
    } else {
        status = "--- d";
    }
    
    amount = -amount;
    
    TransactionNode *new_node = create_transaction_node(description, amount, status);
    if (new_node != NULL) {
        insert_node_at_position(new_node, position);
        printf("Expense added successfully\n");
    }
}

void delete_transaction(void) {
    if (head == NULL) {
        printf("\nNo transactions to delete\n");
        return;
    }
    
    print_transactions();
    
    printf("\nEnter transaction number to delete: ");
    int index;
    scanf("%d", &index);
    getchar(); 
    
    if (index < 1) {
        printf("Error: Invalid transaction number\n");
        return;
    }
    
    //find and delete the node
    if (index == 1) {
        TransactionNode *temp = head;
        head = head->next;
        free(temp);
        printf("Transaction deleted successfully!\n");
        return;
    }
    
    TransactionNode *current = head;
    TransactionNode *previous = NULL;
    int count = 1;
    
    while (current != NULL && count < index) {
        previous = current;
        current = current->next;
        count = count + 1;
    }
    
    if (current == NULL) {
        printf("Error: Invalid transaction number\n");
        return;
    }
    
    previous->next = current->next;
    free(current);
    printf("Transaction deleted successfully!\n");
}

//function to print transactions
void print_transactions(void) {
    if (head == NULL) {
        printf("\nNo transactions to display\n");
        return;
    }
    
    printf("\n--- All Transactions ---\n");
    printf("%-30s | %-10s | %-10s\n", "Description", "Amount", "Status");
    printf("---------------------------------------------------\n");
    
    TransactionNode *current = head;
    double total_money = 0;
    int count = 1;

    while (current != NULL) {
        printf("%d. %-30s | $%-9.2f | %s\n",
               count,
               current->description,
               current->amount,
               current->status);
        total_money += current->amount;
        current = current->next;
        count = count + 1;
    }
    printf("---------------------------------------------------\n");
}