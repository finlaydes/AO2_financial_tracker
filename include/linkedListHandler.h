#ifndef LINKED_LIST_HANDLER_H
#define LINKED_LIST_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TransactionNode {
    char description[100];
    double amount;
    char status[20];
    struct TransactionNode *next;
} TransactionNode;

extern TransactionNode *head;

TransactionNode *create_transaction_node(const char *description, double amount, const char *status);
int count_transactions(void);
void insert_node_at_position(TransactionNode *new_node, int position);
void print_transactions(void);
void delete_transaction(void);
void add_income(void);
void add_expense(void);

#endif
