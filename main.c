#include <stdio.h>
#include <stdlib.h>

int main(){
    system("cls");

    printf("\t\t\t\t\t\t\t\t\t\t*******************************************************************************\t\t\t\t\t\t\t\t\n");

    printf("Who tf are you? Press the respective number.\n");
    printf("1. Customer\n");
    printf("2. Delivery Guy\n");
    printf("3. Restaurant Owner\n");
    printf("4. Admin\n");


    int choice;
    scanf("%i", &choice);

    switch(choice)
    {
        case 1: 
            system("./customer");
            break;
        case 2:
            system("./deliveryperson");
            break;
        case 3:
            system("./restOwner");
            break;
        case 4:
            system("./admin");
            break;
        default:
            printf("Please enter a valid number.\n");
    }


    return 0;
}