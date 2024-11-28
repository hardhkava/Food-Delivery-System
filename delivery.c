#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "welcome.c"
#include <ctype.h>
#include "center_logo.c"
struct logindelivery{
    char username[50];
    char password[50];
    char name[50];
    int age;
    char phone[11];
    struct logindelivery *node;
    

};
struct orders_completed{
    char username[50];
    char name[50];
    int order_id;
    char orderitems[200];
    char restaurant[50];
    int amount;
    struct order_completed *onode;
};
struct orders{
    int order_id;
    char items[200];
    char restaurant[50];
    int amount;
    struct orders *node;
};
struct logindelivery *head=NULL;
struct logindelivery *current=NULL;
struct logindelivery *temp_current=NULL;
struct orders *headorder=NULL;
struct orders *ordercurrent=NULL;
struct order_completed *headcomplete=NULL;
struct order_completed *headcurrent=NULL;


void new_user(){
	system("clear");
    logo();
        struct logindelivery *Node;
        char user[50];
        char pass[50];
        char name[50];
        int age;
        char phone[11];
        Node=malloc(sizeof(struct logindelivery));
        printf("Enter your username: \n");
        fgets(user,50,stdin);
        user[strcspn(user,"\n")]='\0';

        printf("Enter your password: \n");
        fgets(pass,50,stdin);
        pass[strcspn(pass,"\n")]='\0';

        printf("Enter your name: \n");
        fgets(name,50,stdin);
        name[strcspn(name,"\n")]='\0';

        printf("Enter your age: \n");
        scanf("%d", &age);
        getchar();

        while (1) {
        printf("Owner's phone number: ");
        fgets(phone, 11, stdin);
        phone[strcspn(phone, "\n")] = '\0';
        if (strlen(phone)!=10){
            printf("Invalid Input\n");}
        else{break;}}

        FILE *fp;
        fp=fopen("deliveryworkers.txt","a");
        fprintf(fp, "%s,%s,\"%s\",%d,%s\n", user, pass, name, age, phone);
        fclose(fp);
        strcpy(Node->password,pass);
        strcpy(Node->username,user);
        strcpy(Node->name,name);
        strcpy(Node->phone,phone);
 
        Node->age=age;
        Node->node=NULL;
        if (head==NULL){
            head=Node;
            current=Node;
        }
        else{
            current->node=Node;
            current=Node;
        }
        printf("User crieated successfully.\n");
}



void load(){
        char user[50];
        char pass[50];
        char name[50];
        int age;
        char address[300];
        char phone[11];
    FILE *fp;
    fp=fopen("deliveryworkers.txt","r");
    struct logindelivery *temp1;
    temp1=head;
 
  while (fscanf(fp, "%49[^,],%49[^,],\"%49[^\"]\",%d,%s\n", user, pass, name, &age, phone) == 5) {
        temp1=malloc(sizeof(struct logindelivery));
        strcpy(temp1->password,pass);
        strcpy(temp1->username,user);
        strcpy(temp1->name,name);
        strcpy(temp1->phone,phone);
        temp1->age=age;
        temp1->node=NULL; 
        if (head==NULL){
            head=temp1;
            current=temp1;
        }
        else{
            current->node=temp1;
            current=temp1;
        }

  }      printf("File loaded successfully.\n");
        fclose(fp);
}

int login() {
    while (1) {
	system("clear");
    logo();
        int in1;
        printf("Press 1 for New User\n");
        printf("Press 2 for Existing User\n");
        scanf("%d", &in1);
        getchar();

        if (in1 == 1) {
            new_user();
        } 
        else if (in1 == 2) {
            char username[50];
            char password[50];
            printf("Enter Username: \n");
            fgets(username, 50, stdin);
            username[strcspn(username, "\n")] = '\0';

            printf("Enter Password: \n");
            fgets(password, 50, stdin);
            password[strcspn(password, "\n")] = '\0';

            struct logindelivery *local_temp = head;
            int flag = 0;
            while (local_temp != NULL && flag == 0) {
                if (strcmp(local_temp->username, username) == 0 && strcmp(local_temp->password, password) == 0) {
                    flag = 1;
                    temp_current = local_temp;
		    system("clear"); 
            logo();
                    printf("         LOGIN SUCCESSFUL            \n");
                    return 1;
                }
                local_temp = local_temp->node;
            }

            if (flag == 0) {
                printf("Invalid Username/Password.\n");
                temp_current = NULL;
            }
        } 
        else {
            printf("Invalid input.\n");
        }
    }
}

void avail_orders() {
	system("clear");
    logo();
    printf("AVAILABLE ORDERS\n");
    int order_id, amount;
    char items[200], restaurant[50],cust_name[50];
    FILE *fp = fopen("orders.txt", "r");
    if (!fp) {
        printf("Error: Unable to open 'orders.txt'. No orders available.\n");
        return;
    }

    while (fscanf(fp, "\"%199[^\"]\",\"%49[^\"]\",\"%49[^\"]\",%d,%d\n", items, restaurant, cust_name, &order_id, &amount) == 5) {
        printf("Order ID: %d\n", order_id);
        printf("Items: %s\n", items);
        printf("Restaurant: %s\n", restaurant);
        printf("Amount: %d\n", amount);
        printf("Customer Name: %s\n", cust_name);
    }
    fclose(fp);

    printf("All available orders printed.\n");
    printf("Do You Want to go Back? (y/n): ");
    char ch;
    scanf(" %c", &ch);
    getchar();         

    if (ch == 'y' || ch == 'Y') {
        return; 
    } else {
        printf("Exiting program...\n");
        exit(0); 
    }
}

void view_orders_withoutyn() {
	printf("AVAILABLE ORDERS\n");
    int order_id, amount;
    char items[200], restaurant[50], cust_name[50];
    FILE *fp = fopen("orders.txt", "r");
    if (!fp) {
        printf("Error: Unable to open 'orders.txt'. No orders available.\n");
        return;
    }

    while (fscanf(fp, "\"%199[^\"]\",\"%49[^\"]\",\"%49[^\"]\",%d,%d\n", items, restaurant,cust_name, &order_id, &amount) == 5) {
        printf("Order ID: %d\n", order_id);
        printf("Items: %s\n", items);
        printf("Restaurant: %s\n", restaurant);
        printf("Amount: %d\n", amount);
        printf("Customer Name: %s\n", cust_name);
    }
    fclose(fp);

    printf("All available orders printed.\n");

}
void choose_order() {
	view_orders_withoutyn();
 
    printf("Enter the Order ID: \n");

    int id, order_found = 0;
    scanf("%d", &id);
    getchar();

    int order_id, amount;
    char items[200], restaurant[50],cust_name[50];

    FILE *fp = fopen("orders.txt", "r");
    if (!fp) {
        printf("Error: Unable to open 'orders.txt'. No orders available.\n");
        return;
    }

    FILE *fp1 = fopen("temp_orders.txt", "w");
    if (!fp1) {
        printf("Error: Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    FILE *fp2 = fopen("completed.txt", "a");
    if (!fp2) {
        printf("Error: Unable to open 'completed.txt'.\n");
        fclose(fp);
        fclose(fp1);
        return;
    }

    while (fscanf(fp, "\"%199[^\"]\",\"%49[^\"]\",\"%49[^\"]\",%d,%d\n", items, restaurant, cust_name, &order_id, &amount) == 5) {
        if (order_id == id) {
            fprintf(fp2, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%d\n",
                    temp_current->name, temp_current->username, items, restaurant, order_id, amount);
            printf("Order ID %d accepted successfully.\n", id);
            order_found = 1;
        } else {
            fprintf(fp1, "\"%s\",\"%s\",\"%s\",%d,%d\n", items, restaurant, cust_name, order_id, amount);
        }
    }

    fclose(fp);
    fclose(fp2);
    fclose(fp1);

    if (remove("orders.txt") != 0) {
        printf("Error: Unable to delete 'orders.txt'.\n");
    } else if (rename("temp_orders.txt", "orders.txt") != 0) {
        printf("Error: Unable to rename 'temp_orders.txt' to 'orders.txt'.\n");
    }

    if (!order_found) {
        printf("Order ID %d not found. Please try again.\n", id);
    } else {
        printf("Order list updated successfully.\n");
    }
    printf("Do You Want to go Back? (y/n):\n");
    char ch;
    scanf(" %c", &ch); 
    getchar();         

    if (ch == 'y' || ch == 'Y') {
        return;
    }
    else {
        printf("Exiting program...\n");
        exit(0);
    }

}

void accepted_orders(){
	
    char username[50];
    char name[50];
    int order_id;
    char orderitems[200];
    char restaurant[50];
    int amount;
    struct orders_completed *temp3;
    FILE *fp4=fopen("completed.txt", "r");
    while (fscanf(fp4, "\"%49[^\"]\",\"%49[^\"]\",\"%199[^\"]\",\"%49[^\"]\",%d,%d\n", name, username, orderitems, restaurant, &order_id, &amount) == 6){
        if (strcmp(username,temp_current->username)==0){
            printf("Delivered by: %s, Order ID: %d, Items: %s, Restaurant: %s, Amount: %d\n",name,order_id,orderitems,restaurant,amount );
        }
    }
    printf("Do You Want to go Back? (y/n):\n");
    char ch;
    scanf(" %c", &ch); // Space before %c to consume any leftover newline character
    getchar();         // Clear input buffer

    if (ch == 'y' || ch == 'Y') {
        return; // Return to the main menu
    }
    else {
        printf("Exiting program...\n");
        exit(0);
    }

    fclose(fp4);
}

void view_profileyn() {
	            printf("Username: %s\n",temp_current->username);
                printf("Password: %s\n",temp_current->password);
                printf("Name: %s\n",temp_current->name);
                printf("Age: %d\n",temp_current->age);
                printf("Phone No.: %s\n", temp_current->phone);
                printf("Do You Want to go Back? (y/n): ");
    char ch;
    scanf(" %c", &ch); 
    getchar();         

    if (ch == 'y' || ch == 'Y') {
        return; 
    }
    else {
        printf("Exiting program...\n");
        exit(0);
    }
}
int main(){
    load();

int z = login();
while (z==1){
	    system("clear");
        logo();
            int f;
	    print_centered("**************************\n");
            printf("Press the required key\n1.View orders\n2.View Profile\n3.Accept Orders\n4.Accepted Orders\n5.Exit\n");
            scanf("%d",&f);
            if (f==1){avail_orders();};
            if (f==2){
		    system("clear");
            logo();
		    view_profileyn();}
            if (f==3){system("clear"); 
            logo();
		    choose_order();}
            if (f==4){system("clear");
            logo();
		    accepted_orders();}
		if(f==5){
			exit(0);
		} 
	    } 
return 0;
}

