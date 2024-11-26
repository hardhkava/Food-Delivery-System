#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "restaurantfuncs.h"

void mainpage();

char loggedinRest[50] = "";

void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


void loginPage(){
    char user[50], pwd[25];
    //system("cls");
    printf("\t\t\t\t\t\t\t\t\t======================================================================\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t------LOGIN PAGE FOR RESTAURANTS------\n");

    char choice[10];
    printf("Enter login if you want to Login, or exit if you want to Exit: ");
    scanf("%s", choice);
    toLowerCase(choice); 

    if (strcmp(choice, "login") == 0) {
        int attempts = 0; 
        int loggedin = 0; 

        while (attempts < 3 && !loggedin) {
            printf("Enter your restaurant username: ");
            scanf("%s", user);

            printf("Enter password for user %s: ", user);
            scanf("%s", pwd);

            FILE *fptr = fopen("restaurants.txt", "r");
            if (fptr == NULL) {
                printf("file not found...\n");
                exit(1);
            }

            char rName[50], rUser[50], rPwd[50], rAddress[50], rOwner[50], rPhone[11];
            float rBalance;

            while(fscanf(fptr, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%f\n", rName, rUser, rPwd, rAddress, rOwner, rPhone, &rBalance) != EOF) {
                if(strcmp(user, rUser) == 0 && strcmp(pwd, rPwd) == 0){
                    strcpy(loggedinRest, rName);
                    
                    printf("Logged in successfully as %s...\n", user);
                    loggedin = 1; 
                    fclose(fptr);
                    mainpage();
                    return;
                }
            }

            fclose(fptr);

            if (!loggedin) {
                attempts++;
                if (attempts < 3) {
                    printf("Wrong username or password... try again\n");
                } else {
                    printf("): Access Denied :(\n");
                    system("main.exe");
                }
            }
        }
    }

    else if(strcmp(choice, "exit") == 0){
        system("main.exe");
    }
    else{
        printf("Please enter valid choice.\n");
    }
}

void mainpage(){
        system("cls");
        printf("\t\t\t\t\t\t\t\t\t######################################################\n\n\n");
        printf("Select an option: \n\n");
        printf("1. View restaurant menu\n");
        printf("2. Add/Remove a food from menu\n");
        printf("3. View restaurant profile\n");
        printf("4. Logout\n");

        int choice;
        scanf("%i", &choice);

        switch(choice){
            case 1:{
                viewMenu(loggedinRest);
                break; 
            }
            case 2:{
                system("cls");
                char choice1[50];
                printf("Add or Remove food?: ");
                scanf("%s", choice1);
                toLowerCase(choice1);

                if(strcmp(choice1, "add") == 0){
                    char food[50], vegStatus[50];
                    float price;

                    while(getchar() != '\n');
                    printf("Name of food item: ");
                    fgets(food, sizeof(food), stdin);
                    food[strcspn(food, "\n")] = '\0';

                    printf("Veg or Nonveg?(no special character): ");
                    scanf("%49s", vegStatus);
                    toLowerCase(vegStatus);

                    printf("What price do you want to sell it for: ");
                    scanf("%f", &price);

                    addFood(loggedinRest, food, vegStatus, price);
                }
                else if(strcmp(choice1, "remove") == 0){
                    char food[50];
                    while(getchar() != '\n');

                    printf("Which food do you want to remove: ");
                    fgets(food, sizeof(food), stdin);
                    food[strcspn(food, "\n")] = '\0';

                    removeFood(loggedinRest, food);
                }
                else{
                    printf("Enter a valid choice...\n");
                }
                break;
            }

            case 3:{
                system("cls");
                viewProfile(loggedinRest);
                break;
            }

            case 4:{
                loggedinRest[0] = '\0';
                printf("Logged out...\n");
                printf("press any key to go back...\n");
                while(getchar() != '\n');
                getchar();
                return;
            }


            default:{
                printf("Enter a valid number...");
                break;
            }
        }
        mainpage();
    }



int main(){
    loadRestaurants();

    insertRest("mcdonalds", "mcd", "123", "neeladri", "narendramodi", "9265791288", 1000);
    insertRest("Burger King", "bk", "789", "neeladri", "narendramodi", "9265791288", 1000);
    
    loginPage();

    system("main.exe");

    freeRestaurants();

    return 0;
}