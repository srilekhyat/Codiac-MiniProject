#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "banner.h"
#include "Register_Login.h"

int main() {
    int choice;

    printf("Loading User Table...\n");
    delayTime(500);
    loadFromFile();

    do {
        system("cls");
        
        getBanner("WELCOME TO", '|', 200);
        printf("\n");
        getBanner("  CODIAC", '|', 200);

        delayTime(2000);

        printf("\n\n");
        printf("\n\t                                                    =========================================\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||      1. REGISTER                    ||\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||      2. LOGIN                       ||\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||      3. EXIT                        ||\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    =========================================\n\n");
    
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                registerUser();
                break;
            case 2:;
                int isAdmin = loginUser();
                if (isAdmin == 1) {
                    showAdminScreen();
                } else {
                    showNewSelectionScreen();
                }
                break;
            case 3: 
                printf("\nExiting the program!\n");
                break;
            default: 
                printf("Invalid Entry!\n");
                break;
        }
    } while (choice != 3);
    
    return 0;
}