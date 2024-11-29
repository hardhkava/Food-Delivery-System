#include <stdio.h>
#include <string.h>
#include "admin_func.c"
#include "center_logo.c"

#define admin_username "Hemakshi Jadeja"
#define admin_password "ctrl_alt_elite"

void admin_menu(){
        int n, rnum=0;
        while(1){
		logo();
		center_text("***********************************************************************\n\n\n");

		printf("Number of restaurants currently associated with HARDS: %d\n", rnum);

                printf("1. Add a restaurant\n");
                printf("2. Remove a restaurant\n");
                printf("3. Remove a delivery partner\n");
                printf("4. Logout\n");
                printf("What would you like to do? : ");
		scanf("%d", &n);

                switch (n) {
                        case 1: add_input();
				rnum += 1;
                                break;
                        case 2: remove_rest();
				rnum -= 1;
                                break;
                        case 3: remove_dp();
                                break;
                        case 4: printf("Logging out...\n");
				system("clear");
				system("./main");
                                return;
                        default:
                                printf("Invalid choice. Please try again.\n");
                }
		printf("Press enter to continue...\n");
		while (getchar() != '\n');
		system("clear");
        }
}

void login(){
        char user[100];
        char pass[100];
        int attempts = 3;

        while (attempts>0){
		system("clear");
		logo();
		center_text("***********************************************************************\n\n\n");
                printf("Enter username: ");
                fgets(user, 100, stdin);
                user[strcspn(user, "\n")] = '\0';

                if (strcmp(user, admin_username) == 0){
                        printf("Enter password: ");
                        fgets(pass, 100, stdin);
                        pass[strcspn(pass, "\n")] = '\0';

                        if (strcmp(pass, admin_password) == 0){
                                printf("Login successful! Welcome to HARDS, %s. <3\n", admin_username);
				printf("Press enter to continue...");
				while (getchar() != '\n');
                                system("clear");
                                admin_menu();
                                return;
                        }
                        else {
                                if (attempts == 1){
                                        printf("Too many failed attempts. Access denied T-T\n");
					printf("Press enter to exit...");
					while (getchar() != '\n');
                                }
                                else {
                                        printf("Incorrect password :(\n");
					printf("Press enter to try again...");
					while (getchar() != '\n');
                                }
                        }
                }
                else {
                        if (attempts == 1){
                                printf("Too many failed attempts. Access denied.\n");
				printf("Press enter to exit...");
				while (getchar() != '\n');
                        }
                        else {
                                printf("Incorrect username :(\n");
				printf("Press enter to try again...");
				while (getchar() != '\n');
                        }
                                        }
                attempts--;
        }

}

void main(){
        login();
}
