#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct cart {
    char food[50];
    float price;
    struct cart *next;
};

struct customer {
    char name[50];
    char username[50];
    char password[50];
    float balance;
    char phoneno[11];
    struct cart *carthead;
};

struct node {
    struct customer c;
    struct node *link;
};

void registerc(struct node **ptrhead);
void loadl(struct node **ptrhead);
void login(struct node *head);
void afterloggingin(struct node *head, char username[50], char password[50]);
void addbalance(struct node *head, char username[50], char password[50]);
void order(struct node *head, char username[50], char password[50]);
void addToCart(struct node *head,struct customer *cust, char foodName[], float price);
void viewCart(struct node *head,struct customer *cust);
void viewProfile(struct node *head, char username[50], char password[50]);

#endif