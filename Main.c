#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "banner.h"
#include "Register_Login.h"

int main() {
    int choice;

    printf("Loading User Table...\n");
    delayTime(500);
    loadFromFile();
    loadMainQuizFromFile();

    do {
        system("cls");
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        getBanner("WELCOME TO", '|', 200);
        printf("\n");
        getBanner("  CODIAC", '|', 200);

        SetConsoleTextAttribute(hConsole, saved_attributes);

        delayTime(2000);

        printf("\n\n");
        printf("\n\t                                                    =========================================\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||            1. REGISTER              ||\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||            2. LOGIN                 ||\n");
        printf("\t                                                    ||                                     ||\n");
        printf("\t                                                    ||            3. EXIT CODIAC           ||\n");
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
                    system("cls");
                    getBanner("HELLO ADMIN", '|', 200);
                    printf("\n");
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