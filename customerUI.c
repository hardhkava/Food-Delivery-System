#include "customerfuncs.h"
#include "center_logo.c"

char loggedinUser[50];
char loggedinPwd[50];
char selectedRest[50];

void afterloggingin(struct node *head, char username[50], char password[50]);

void registerc(struct node **ptrhead) {
    system("clear");
    logo();

    struct node *new = malloc(sizeof(struct node));
    new->link = NULL;
    printf("Enter customer name: ");
    fgets(new->c.name, sizeof(new->c.name), stdin);
    new->c.name[strcspn(new->c.name, "\n")] = '\0';  
    printf("Enter username: ");
    fgets(new->c.username, sizeof(new->c.username), stdin);
    new->c.username[strcspn(new->c.username, "\n")] = '\0';  
    printf("Enter password: ");
    fgets(new->c.password, sizeof(new->c.password), stdin);
    new->c.password[strcspn(new->c.password, "\n")] = '\0';  
    printf("Enter phone number: ");
    fgets(new->c.phoneno, sizeof(new->c.phoneno), stdin);
    new->c.phoneno[strcspn(new->c.phoneno, "\n")] = '\0'; 
    new->c.balance = 0;
    new->c.carthead = NULL;

    if (*ptrhead == NULL) {
        *ptrhead = new;
    } else {
        struct node *temp = *ptrhead;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = new;
    }

    FILE *fp = fopen("customers.txt", "a");
    fprintf(fp, "%s,%s,%s,%s,%.2f\n", new->c.name, new->c.username, new->c.password, new->c.phoneno, new->c.balance);
    fclose(fp);
    printf("Registration successful. Returning to main menu.\n");
    printf("Press enter to go back...");
    while(getchar() != '\n');
    getchar();
    system("clear");
}

void loadl(struct node **ptrhead) {
    FILE *fp = fopen("customers.txt", "r");
    if (fp == NULL) return;

    char name[50], username[50], password[50], phoneno[11];
    float balance;
    struct node *new, *temp;

    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%f", name, username, password, phoneno, &balance) == 5) {
        new = malloc(sizeof(struct node));
        strncpy(new->c.name, name, sizeof(new->c.name));
        strncpy(new->c.username, username, sizeof(new->c.username));
        strncpy(new->c.password, password, sizeof(new->c.password));
        strncpy(new->c.phoneno, phoneno, sizeof(new->c.phoneno));
        new->c.balance = balance;
        new->c.carthead = NULL;
        new->link = NULL;

        if (*ptrhead == NULL) {
            *ptrhead = new;
        } else {
            temp = *ptrhead;
            while (temp->link != NULL) {
                temp = temp->link;
            }
            temp->link = new;
        }
    }
    fclose(fp);
}

void login(struct node *head) {
    system("clear");
    char username[50], password[50];
    int attempts = 0, logged_in = 0;

    while (attempts < 3 && !logged_in) {
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0'; 
        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';  
        struct node *temp = head;
        while (temp != NULL) {
            if (strcmp(temp->c.username, username) == 0 && strcmp(temp->c.password, password) == 0) {
                printf("Login successful.\n");
                logged_in = 1;
                strcpy(loggedinUser, username);
                strcpy(loggedinPwd, password);
                afterloggingin(head, username, password);
                break;
            }
            temp = temp->link;
        }

        if (!logged_in) {
            attempts++;
            printf("Login failed. Attempt %d of 3\n", attempts);
        }
    }

    if (!logged_in) {
        printf("Maximum attempts reached. Returning to main menu.\n");
        printf("Press enter to go back...");
        getchar();
        system("clear");
        return;
    }
}

void afterloggingin(struct node *head, char username[50], char password[50]) {
    system("clear");
    logo();
    printf("1. Order\n");
    printf("2. View Profile\n");
    printf("3. Add Balance\n");
    printf("4. View Cart\n");
    printf("5. Logout");
    int c;
    scanf("%d", &c);
    getchar();

    struct node *temp = head;
    struct customer *loggedInCustomer = NULL;

     while (temp != NULL) {
        if (strcmp(temp->c.username, username) == 0 && strcmp(temp->c.password, password) == 0) {
            loggedInCustomer = &temp->c;
            break;
        }
        temp = temp->link;
    }

    switch (c) {
        case 1:
            order(head, username, password);
            break;
        case 2:
            viewProfile(head, username, password);  
            break;
        case 3:
            addbalance(head, username, password);
            break;
        case 4:
            viewCart(head, loggedInCustomer);
        case 5:
            for(int i=0;i<strlen(loggedinUser);i++)
            {
                loggedinUser[i] = 0;
            }
            for(int i=0;i<strlen(loggedinPwd);i++)
            {
                loggedinPwd[i] = 0;
            }

            printf("Logging out...\n");
            printf("Press enter to go back...");
            while(getchar() != '\n');
            getchar();
            system("./main");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            printf("Press any key to go back.");
            getchar();
            break;
    }
}

void addbalance(struct node *head, char username[50], char password[50]) {
    float amount;
    int found = 0;
    printf("Enter the amount to add: ");
    scanf("%f", &amount);
    if(amount > 10000){
        printf("Maximum limit exceeded. Credit an amount less than 10,000.");
        printf("Press enter to go back...");
        while(getchar() != '\n');
        getchar();
        return;
    }
    getchar();

    struct node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->c.username, loggedinUser) == 0 && strcmp(temp->c.password, loggedinPwd) == 0) {
            temp->c.balance += amount;
            found = 1;
            break;
        }
        temp = temp->link;
    }

    if (!found) {
        printf("User not found.\n");
        return;
    }

    FILE *fp = fopen("customers.txt", "w");
    temp = head;
    while (temp != NULL) {
        fprintf(fp, "%s,%s,%s,%s,%.2f\n", temp->c.name, temp->c.username, temp->c.password, temp->c.phoneno, temp->c.balance);
        temp = temp->link;
    }
    fclose(fp);
    printf("Balance updated successfully.\n");
    printf("Press any key to go back.");
    getchar();
    afterloggingin(head, loggedinUser, loggedinPwd);
    return;
}
void addToCart(struct node *head, struct customer *cust, char foodName[], float price) {
    struct cart *newCart = (struct cart *)malloc(sizeof(struct cart));

    strcpy(newCart->food, foodName);
    newCart->price = price;
    newCart->next = NULL;

    if (cust->carthead == NULL) {
        cust->carthead = newCart;
    } else {
        struct cart *travp = cust->carthead;
        while (travp->next != NULL) {
            travp = travp->next;
        }

        travp->next = newCart;
    }

    printf("%s added to cart successfully.\n", foodName);
    printf("Press enter to continue...");
    while(getchar() != '\n');
    getchar();
    afterloggingin(head, loggedinUser, loggedinPwd);
}

void viewCart(struct node *head, struct customer *cust) {
    struct node *custtravp = head;
    while(custtravp->c.name != cust->name){
        custtravp = custtravp->link;
    }

    if (cust->carthead == NULL) {
        printf("Your cart is empty.\n");
        printf("Press any key to go back.");
        getchar();
        afterloggingin(head, loggedinUser, loggedinUser);
        return;
    }
    struct cart *travp = cust->carthead;
    
    char str2[100];
    sprintf(str2, "%s Cart:\n\n", cust->name);
    center_text(str2);

    int i = 1;
    float totalPrice = 0.0;
    while (travp != NULL) {
        char str1[100];
        sprintf(str1,"%d. %-30s Price: %6.2f\n", i, travp->food, travp->price);
        center_text(str1);
        totalPrice += travp->price;
        i++;
        travp = travp->next;
    }
    char str3[100];
    sprintf(str3, "Total of cart: %.2f", totalPrice);
    center_text(str3);

    printf("\nPress 1 to checkout or 2 to go back: ");
    int choice;
    scanf("%i", &choice);
    getchar();

    if (choice == 1) {
        if (cust->balance < totalPrice) {
            printf("You don't have enough money to order T_T");
            printf("\nPress enter to go back.");
            getchar();
            afterloggingin(head, loggedinUser, loggedinUser);
            return;
        } else {
            cust->balance -= totalPrice;
            FILE *fptr = fopen("orders.txt", "a");
            if (fptr == NULL) {
                printf("Can't open orders file");
                printf("\nPress enter to go back.");
                getchar();
                afterloggingin(head, loggedinUser, loggedinPwd);
                return;
            }

            int orderID = 1;
            char temp[100];
            FILE *tempptr = fopen("orders.txt", "r");

            if (tempptr != NULL) {
                while (fgets(temp, sizeof(temp), tempptr)) {
                    orderID++;
                }
                fclose(tempptr);
            }

            while (cust->carthead != NULL) {
                struct cart *tempcart = cust->carthead;
                int z=(int)tempcart->price;
                fprintf(fptr, "\"%s\",\"%s\",\"%s\",%d,%d\n", tempcart->food, selectedRest,cust->name, orderID, z);
                cust->carthead = cust->carthead->next;
                free(tempcart);
                orderID++;
            }

            fclose(fptr);
            printf("Cart ordered. Press any key to go back.");
            getchar();
            afterloggingin(head, loggedinUser, loggedinUser);
            return;
        }
    } else if (choice == 2) {
        printf("Press any key to go back.");
        getchar();
        afterloggingin(head, loggedinUser, loggedinUser);
    } else {
        printf("Not a valid choice.\n");
        printf("Press any key to go back.");
        getchar();
        afterloggingin(head, loggedinUser, loggedinUser);
    }
}

void order(struct node *head, char username[50], char password[50]) {
    system("clear");
    logo();
    FILE *restFile = fopen("restaurants.txt", "r");
    if (restFile == NULL) {
        printf("Could not open the restaurant file.\n");
        return;
    }

    printf("Select a restaurant:\n");
    char restName[50];
    int i = 1;
    int lineNum = 1;

    while (fgets(restName, sizeof(restName), restFile)) {
        if (lineNum % 6 == 1) {
            restName[strcspn(restName, "\n")] = '\0';
            printf("%d. %s\n", i++, restName);
        }
        lineNum++;
    }
    fclose(restFile);

    int choice;
    printf("\nEnter serial number of the restaurant you want to order from: ");
    scanf("%d", &choice);
    getchar();

    restFile = fopen("restaurants.txt", "r");
    if (restFile == NULL) {
        printf("Could not open the restaurant file.\n");
        return;
    }

    int selectedRestaurantLine = (choice - 1) * 6 + 1;
    lineNum = 1;
    while (fgets(restName, sizeof(restName), restFile)) {
        if (lineNum == selectedRestaurantLine) {
            restName[strcspn(restName, "\n")] = '\0';
            break;
        }
        lineNum++;
    }
    fclose(restFile);

    strcpy(selectedRest, restName);

    char menuFile[100];
    sprintf(menuFile, "%s_menu.txt", restName);
    FILE *menuFilePtr = fopen(menuFile, "r");
    if (menuFilePtr == NULL) {
        printf("Could not load the menu for %s.\n", restName);
        afterloggingin(head, loggedinUser, loggedinPwd);
    }

    char foodName[25], vegStatus[10], restNameDisplay[100];
    float price;
    int j = 1;
    sprintf(restNameDisplay,"=========== %s Menu ===========\n\n", restName);
    center_text(restNameDisplay);

    while (fscanf(menuFilePtr, "%[^\n]\n%[^\n]\n%f\n", foodName, vegStatus, &price) != EOF) {
        char menuLine[100];
        sprintf(menuLine,"\t%d. %-30s %-10s Price: %.2f\n", j++, foodName, vegStatus, price);
        center_text(menuLine);
    }
    fclose(menuFilePtr);

    printf("\nEnter serial number of the food item you want to order: ");
    int foodChoice;
    scanf("%d", &foodChoice);
    getchar();

    menuFilePtr = fopen(menuFile, "r");
    for (int k = 1; k <= foodChoice; k++) {
        fscanf(menuFilePtr, "%[^\n]\n%[^\n]\n%f\n", foodName, vegStatus, &price);
    }
    fclose(menuFilePtr);

    // Find the logged-in customer
    struct node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->c.username, loggedinUser) == 0 && strcmp(temp->c.password, loggedinPwd) == 0) {
            break;
        }
        temp = temp->link;
    }

    if (temp == NULL) {
        printf("Error: Logged-in user not found.\n");
        return;
    }

    // Add the food item to the logged-in customer's cart
    addToCart(head, &temp->c, foodName, price);
}


void viewProfile(struct node *head, char username[50], char password[50]) {
    system("clear");
    logo();
    struct node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->c.username, username) == 0 && strcmp(temp->c.password, password) == 0) {
            printf("Profile Details:\n");
            printf("Name: %s\n", temp->c.name);
            printf("Username: %s\n", temp->c.username);
            printf("Password: %s\n", temp->c.password);
            printf("Balance: %.2f\n", temp->c.balance);
            break;
        }
        temp = temp->link;
    }
    printf("\nPress any key to go back.");
    getchar();
    afterloggingin(head, loggedinUser, loggedinPwd);
}

int main() {
    system("clear");
    logo();
    struct node *head = NULL;
    int choice;
    loadl(&head);

    while (1) {
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                login(head);
                break;
            case 2:
                registerc(&head);
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                break;
        }
    }
    return 0;
}
