#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct restaurant{
    char name[50], user[50], pwd[50];
    char address[50], owner_name[50], phone[11];
    float balance;

    struct food *foodHead;
    struct restaurant *next;
}; struct restaurant *restHead;

struct food{    
    char name[50], vegStatus[50];
    float price;
    struct food *next;
};

void loadMenu(struct restaurant *);


void insertRest(char name[], char user[], char pwd[], char address[], char owner[], char phone[], float balance){
    struct restaurant *newrest;
    newrest = (struct restaurant *)malloc(sizeof(struct restaurant));
    strcpy(newrest->name, name);
    strcpy(newrest->user, user);
    strcpy(newrest->pwd, pwd);
    strcpy(newrest->address, address);
    strcpy(newrest->owner_name, owner);
    strcpy(newrest->phone, phone);
    newrest->balance = balance;

    newrest->foodHead = NULL;

    if(restHead == NULL){
        newrest->next = NULL;
        restHead = newrest;
    }
    else{
        newrest->next = restHead;
        restHead = newrest;
    }

    FILE *fptr = fopen("restaurants.txt", "a");
    fprintf(fptr, "%s\n%s\n%s\n%s\n%s\n%s\n%f\n", newrest->name, newrest->user, newrest->pwd, newrest->address, newrest->owner_name, newrest->phone, newrest->balance);

    fclose(fptr);
}

void deleteRestaurant(char restName[]){
    struct restaurant *travp = restHead;
    struct restaurant *prevptr = NULL;
    while((travp != NULL) && (strcmp(travp->name, restName) != 0)){
        prevptr = travp;
        travp = travp->next;
    }

    if(travp == NULL){
        printf("restaurant not found...\n");
        return;
    }

    struct food *foodptr = travp->foodHead;
    while(foodptr != NULL){
        struct food *tempfood = foodptr;
        foodptr = foodptr->next;
        free(tempfood);
    }

    if(prevptr == NULL){
        restHead = travp->next;
    }
    else{
        prevptr->next = travp->next;
    }
    free(travp);

    char fileName[50];
    sprintf(fileName, "%s_menu.txt", restName);
    if(remove(fileName) == 0){
        printf("Menu file deleted\n");
    }
    else{
        printf("Menu not found.\n");
    }
    printf("Restaurant %s deleted.\n", restName);
    
}


void addFood(char restName[], char foodName[], char vegStatus[], float price){
    struct restaurant *travp = restHead;
    struct food *newFood;
    
    newFood = (struct food *)malloc(sizeof(struct food));               //adding new food node
    strcpy(newFood->name, foodName);
    strcpy(newFood->vegStatus, vegStatus);
    newFood->price = price;
    newFood->next = NULL;

    while((travp != NULL) && (strcmp(travp->name, restName) != 0)){
        travp = travp->next;                                            //now traverse pointer is required restaurant
    }
    if(travp == NULL){ 
        printf("Restaurant not present.\n");
        return;
    }
    if(travp->foodHead == NULL){                                        //If the food linked list is empty
        travp->foodHead = newFood;
    }
    else{                                                               // If Food linked list is already there
        newFood->next = travp->foodHead;
        travp->foodHead = newFood;
    }

    char fileName[50];
    sprintf(fileName, "%s_menu.txt", restName);
    FILE *fptr = fopen(fileName, "a");
    
    fprintf(fptr, "%s\n%s\n%.2f\n", foodName, vegStatus, price);
    printf("food added to menu succesfully.\n");

    while(getchar() != '\n');
    printf("press any key to go back...\n");
    getchar();
    
    fclose(fptr);
}

void removeFood(char restName[], char foodName[]){
    struct restaurant *travp = restHead;

    while((travp != NULL) && (strcmp(travp->name, restName) != 0)){
        travp = travp->next;
    }
    if(travp == NULL){
        while(getchar() != '\n');
        printf("Restaurant not found...\nPress any key to go back:");
        getchar();
        return;
    }

    if(travp->foodHead == NULL){
        while(getchar() != '\n');
        printf("there's no food in the menu...\nPress Any Key to go back:");
        getchar();
        return;
    }

    else{
        struct food *foodtravp = travp->foodHead;
        struct food *prevfoodp = NULL;

        while((foodtravp != NULL) && (strcmp(foodtravp->name, foodName) != 0)){
            prevfoodp = foodtravp;
            foodtravp = foodtravp->next;
        }

        if(foodtravp == NULL) {
            printf("Food item not found...\nPress Any key to go back:");
            getchar();
            return;
        }

        if(prevfoodp == NULL){
            travp->foodHead = foodtravp->next;
        }
        else{
            prevfoodp->next = foodtravp->next;
        }

        free(foodtravp);

        FILE *ogMenuPtr, *tempMenuPtr;


        char fileName[50], tempFile[50], fName[50], fVegStatus[50];
        float fPrice;

        sprintf(fileName, "%s_menu.txt", restName);
        sprintf(tempFile, "tempMenu.txt");

        ogMenuPtr = fopen(fileName, "r");
        tempMenuPtr = fopen(tempFile, "w");

        if (!ogMenuPtr || !tempMenuPtr) {
            printf("Error updating menu files...\n");
            return;
        }

        while (fscanf(ogMenuPtr, "%[^\n]\n%[^\n]\n%f\n", fName, fVegStatus, &fPrice) != EOF) {
            if (strcmp(fName, foodName) == 0) {
                continue;
            }
            fprintf(tempMenuPtr, "%s\n%s\n%.2f\n", fName, fVegStatus, fPrice);
        }

        fclose(ogMenuPtr);
        fclose(tempMenuPtr);

        remove(fileName);
        rename(tempFile, fileName);
    }
}


void viewMenu(char restName[]){
    char fileName[100];
    sprintf(fileName, "%s_menu.txt", restName);

    FILE *menuptr = fopen(fileName, "r");

    if (menuptr == NULL) {
        printf("menu file for %s not found...\n", restName);
        printf("press any key to go back...");
        while(getchar() != '\n');
        getchar();
        return;
    }

    printf("\t\t\t\t\t=========== %s MENU ===========\n\n", restName);

    char foodName[25], vegStatus[10];
    float price;
    int i = 1;

    while (fscanf(menuptr, "%[^\n]\n%[^\n]\n%f\n", foodName, vegStatus, &price) != EOF) {
        printf("%d. %s, %s\tPrice: %.2f\n", i, foodName, vegStatus, price);
        i++;
    }

    fclose(menuptr);
    printf("\nPress any key to go back...");
    while(getchar() != '\n');
    getchar();
    return;
}


void viewProfile(char restName[]){
    struct restaurant *travp = restHead;

    while((travp != NULL) && (strcmp(travp->name, restName) != 0)){
        travp = travp->next;
    }

    if(travp == NULL){
        printf("restaurant not found...\n");
        printf("press any key to go back...\n");
        while(getchar() != '\n');
        getchar();
        return;
    }

    printf("======%s PROFILE======\n", restName);
    printf("Name: %s\n", travp->owner_name);
    printf("Phone No: %s\n", travp->phone);
    printf("Address: %s\n", travp->address);
    
    if(travp->balance > 1000.00){
        printf("Balance: %.2f(damn thats a lot of money)\n", travp->balance);
    } else {
        printf("Balance: %.2f\n", travp->balance);
    }

    printf("press any key to go back...");
    while(getchar() != '\n');
    getchar();
    return;
}


void loadRestaurants(){
    FILE *fptr = fopen("restaurants.txt", "r");

    if(fptr == NULL){
        printf("no restaurants available...\n");
        return;
    }

    char rName[50], rUser[50], rPwd[50];
    char rAddress[50], rOwner[50], rPhone[11];
    float rBalance;

    while(fscanf(fptr, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%f\n", rName, rUser, rPwd, rAddress, rOwner, rPhone, &rBalance) != EOF){
        struct restaurant *newrest;
        newrest = (struct restaurant *)malloc(sizeof(struct restaurant));

        strcpy(newrest->name, rName);
        strcpy(newrest->user, rUser);
        strcpy(newrest->pwd, rPwd);
        strcpy(newrest->address, rAddress);
        strcpy(newrest->owner_name, rOwner);
        strcpy(newrest->phone, rPhone);
        newrest->balance = rBalance;

        newrest->foodHead = NULL;
        newrest->next = restHead;
        restHead = newrest;

        loadMenu(newrest);
    }

    fclose(fptr);
}

void loadMenu(struct restaurant *rest){
    char fileName[100];
    sprintf(fileName, "%s_menu.txt", rest->name);

    FILE *menuptr = fopen(fileName, "r");
    if(menuptr == NULL){
        printf("Menu not found...\n");
        return;
    }

    char foodName[50], vegStatus[50];
    float price;

    while(fscanf(menuptr, "%[^\n]\n%[^\n]\n%f\n", foodName, vegStatus, &price) != EOF){
        struct food *newfood;
        newfood = (struct food *)malloc(sizeof(struct food));

        strcpy(newfood->name, foodName);
        strcpy(newfood->vegStatus, vegStatus);
        newfood->price = price;

        newfood->next = rest->foodHead;
        rest->foodHead = newfood;
    }

    fclose(menuptr);
}

void freeRestaurants() {
    struct restaurant *rest = restHead;
    while (rest != NULL) {
        struct food *food = rest->foodHead;
        while (food != NULL) {
            struct food *tempFood = food;
            food = food->next;
            free(tempFood);
        }
        struct restaurant *tempRest = rest;
        rest = rest->next;
        free(tempRest);
    }
    restHead = NULL;
}
