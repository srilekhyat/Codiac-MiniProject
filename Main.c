#include <stdio.h>
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

    printf("\n\t=========================================\n");
    printf("\t||    1. REGISTER                      ||\n");
    printf("\t||    2. LOGIN                         ||\n");
    printf("\t||    3. DISPLAY USERS                 ||\n");
    printf("\t||    4. EXIT                          ||\n");
    printf("\t=========================================\n");

    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                registerUser();
                break;
            case 2: 
                loginUser();
                showNewSelectionScreen();
                break;
            case 3: 
                showUsersList();
                break;
            case 4: 
                printf("\nExiting the program!\n");
                break;
            default: 
                printf("Invalid Entry!\n");
                break;
        }
    } while (choice != 4);
    
    return 0;
}