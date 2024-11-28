#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct restaurant{
    	char rest_name[50], user[50], pass[25], address[100], owner_name[50], phone[11];
    	struct food *foodHead;
    	struct restaurant *next;
}; 

struct restaurant *restHead;

int check_username(const char *username) {
        FILE *fptr = fopen("restaurants.txt", "r");
    	if (fptr == NULL) {
        	return 0; // If file doesn't exist, no usernames exist yet
    	}

    	char temp[50];
    	while (fgets(temp, sizeof(temp), fptr)) {
        	temp[strcspn(temp, "\n")] = '\0'; // Remove trailing newline
        	// Skip the restaurant name
        	fgets(temp, sizeof(temp), fptr);
        	temp[strcspn(temp, "\n")] = '\0'; // Read and clean username
        	if (strcmp(temp, username) == 0) {
            		fclose(fptr);
            		return 1; // Username found
        	}
        	// Skip the rest of the restaurant details
        	for (int i = 0; i < 4; i++) {
            		fgets(temp, sizeof(temp), fptr);
        	}
    	}

    	fclose(fptr);
    	return 0; // Username not found
}

void add_rest(char rest_name[], char user[], char pass[], char address[], char owner_name[], char phone[]){

        struct restaurant *newrest;
    	newrest = (struct restaurant *)malloc(sizeof(struct restaurant));

    	strcpy(newrest->rest_name, rest_name);
    	strcpy(newrest->user, user);
    	strcpy(newrest->pass, pass);
    	strcpy(newrest->address, address);
    	strcpy(newrest->owner_name, owner_name);
    	strcpy(newrest->phone, phone);

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
    	fprintf(fptr, "%s\n%s\n%s\n%s\n%s\n%s\n", newrest->rest_name, newrest->user, newrest->pass, newrest->address, newrest->owner_name, newrest->phone);
    	fclose(fptr);

    	printf("Restaurant '%s' added successfully.\n", newrest->rest_name);
}

void add_input(){

	char rest_name[50], user[50], pass[25], address[100], owner_name[50], phone[12];

	printf("Enter restaurant name to be added: ");
	while (getchar() != '\n');
	fgets(rest_name, 50, stdin);
        rest_name[strcspn(rest_name, "\n")] = '\0';

	while (1) {
        	printf("Username: ");
        	fgets(user, 50, stdin);
        	user[strcspn(user, "\n")] = '\0';

        	if (check_username(user)) {
            		printf("Username already exists. Please choose a different username.\n");
        	}
       		else {
        		break;
        	}
        }

	printf("Password: ");
        fgets(pass, 25, stdin);
        pass[strcspn(pass, "\n")] = '\0';
	printf("Restaurant address: ");
        fgets(address, 100, stdin);
        address[strcspn(address, "\n")] = '\0';
	printf("Name of the owner: ");
        fgets(owner_name, 50, stdin);
        owner_name[strcspn(owner_name, "\n")] = '\0';
	
	while (1) {
        	printf("Owner's phone number: ");
        	fgets(phone, 12, stdin);
        	phone[strcspn(phone, "\n")] = '\0';

        	int h = 1; 

        	if (strlen(phone) != 10) {
        		h = 0;
        	}

        	for (int i = 0; i < strlen(phone); i++) {
            		if (!isdigit(phone[i])) {
                		h = 0;
                		break;
            		}
        	}

        	if (h) {
            		break;
        	} 
		else {
            		printf("Invalid phone number. Please enter a 10-digit phone number.\n");
        	}
    	}
	add_rest(rest_name, user, pass, address, owner_name, phone);
}

void remove_rest() {
    	char rName[50], rUser[50], rPass[50];

    	printf("Enter restaurant name to be removed: ");
    	while (getchar() != '\n'); 
    	fgets(rName, sizeof(rName), stdin);
    	rName[strcspn(rName, "\n")] = '\0';

    	printf("Username: ");
    	fgets(rUser, sizeof(rUser), stdin);
    	rUser[strcspn(rUser, "\n")] = '\0'; 

    	printf("Password: ");
    	fgets(rPass, sizeof(rPass), stdin);
    	rPass[strcspn(rPass, "\n")] = '\0'; 

    	FILE *fptr = fopen("restaurants.txt", "r");
    	FILE *hem = fopen("hem.txt", "w");

    	char rest_name[50], user[50], pass[50], location[100], owner_name[50], phone[11];
    	int n = 0;

    	while (fgets(rest_name, sizeof(rest_name), fptr)) {

		if (strcmp(rest_name, "\n") == 0 || rest_name[0] == '\0') {
            		continue;
        	}

        	fgets(user, sizeof(user), fptr);
        	fgets(pass, sizeof(pass), fptr);
        	fgets(location, sizeof(location), fptr);
        	fgets(owner_name, sizeof(owner_name), fptr);
        	fgets(phone, sizeof(phone), fptr);

        	rest_name[strcspn(rest_name, "\n")] = '\0';
        	user[strcspn(user, "\n")] = '\0';
        	pass[strcspn(pass, "\n")] = '\0';
        	location[strcspn(location, "\n")] = '\0';
        	owner_name[strcspn(owner_name, "\n")] = '\0';
        	phone[strcspn(phone, "\n")] = '\0';
	
		//printf("DEBUG: Read from file: '%s', '%s', '%s'\n", rest_name, user, pass);

        	if (strcmp(rest_name, rName) == 0 && strcmp(user, rUser) == 0 && strcmp(pass, rPass) == 0) {
            		n = 1;
            		printf("Restaurant '%s' removed successfully.\n", rName);
            		continue;
        	}

        	fprintf(hem, "%s\n%s\n%s\n%s\n%s\n%s\n", rest_name, user, pass, location, owner_name, phone);
    	}

    	fclose(fptr);
    	fclose(hem);

    	if (!n) {
        	printf("Restaurant not found or invalid credentials.\n");
        	remove("hem.txt"); 
    	} else {
        	remove("restaurants.txt");
        	rename("hem.txt", "restaurants.txt");

               	char fileName[100];
        	snprintf(fileName, sizeof(fileName), "%s_menu.txt", rName);
        	if (remove(fileName) == 0) {
        	    	printf("Menu file '%s' deleted successfully.\n", fileName);
        	} else {
            		printf("Menu file '%s' not found.\n", fileName);
        	}
    	}
}

void remove_dp(){

	char dName[50], dUser[50], dPass[50];
    
	printf("Enter the name of the delivery partner to be removed: ");
    	while (getchar() != '\n'); 
    	fgets(dName, sizeof(dName), stdin);
    	dName[strcspn(dName, "\n")] = '\0';

    	printf("Username: ");
    	fgets(dUser, sizeof(dUser), stdin);
    	dUser[strcspn(dUser, "\n")] = '\0';

    	printf("Password: ");
    	fgets(dPass, sizeof(dPass), stdin);
    	dPass[strcspn(dPass, "\n")] = '\0';

	FILE *fptr = fopen("deliveryworkers.txt", "r");
    	FILE *hemjad = fopen("hemjad.txt", "w");

	char user[50], pass[50], dp_name[50], dp_phone[11];
        int age, n=0;
	
	while (fscanf(fptr, "%49[^,],%49[^,],\"%49[^\"]\",%d,%14s\n", user, pass, dp_name, &age, dp_phone) == 5) {
       
        if (strcmp(dp_name, dName) == 0 && strcmp(user, dUser) == 0 && strcmp(pass, dPass) == 0) {
            		n = 1;
            		printf("Delivery partner '%s' removed successfully.\n", dName);
                	continue; 
       	    }
        		
            		fprintf(hemjad, "%s,%s,\"%s\",%d,%s\n", user, pass, dp_name, age, dp_phone);
	    }


	fclose(fptr);
	fclose(hemjad);

	if (!n) {
        	printf("Delivery partner not found or invalid credentials.\n");
        	remove("hemjad.txt"); 
        }
       	else {
        	remove("deliverypartners.txt");
        	rename("hemjad.txt", "deliverypartners.txt");
	}
}
