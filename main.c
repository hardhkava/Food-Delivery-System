#include <stdio.h>
#include <stdlib.h>
#include "center_logo.c"

int main(){
    system("clear");
    logo();
    center_text("***********************************************************************\n\n\n");

    printf("What's your role?\n");
    printf("1. Customer\n");
    printf("2. Delivery Guy\n");
    printf("3. Restaurant Owner\n");
    printf("4. Admin\n");
    printf("5. Exit\n");


    int choice;
    scanf("%i", &choice);

    switch(choice)
    {
        case 1: 
            system("./customer");
            break;
        case 2:
            system("./delivery");
            break;
        case 3:
            system("./restaurant");
            break;
        case 4:
            system("./admin");
            break;
        case 5:
            exit(0);
        default:
            printf("Please enter a valid number.\n");
    }


    return 0;
}
