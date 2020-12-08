// Main .c file of Codiac(Mini Project)

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

    do {
        system("cls");
        
        // setting color for intro banner
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        // printing banner
        printf("\n");                  
        getBanner("WELCOME TO", '|');
        printf("\n");
        getBanner("  CODIAC", '|');

        SetConsoleTextAttribute(hConsole, saved_attributes);

        // delaying time for getting effect of real-time application
        delayTime(1500);    

        printf("\n\n\n");
        printf("\t                                                    %c", 218);
        for (int i = 0; i < 39; i++) {
            printf("%c",196);
        }
        printf("%c\n",191);
        printf("\t                                                    %c%c                                     %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c            1. REGISTER              %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c                                     %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c            2. LOGIN                 %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c                                     %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c            3. EXIT CODIAC           %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c%c                                     %c%c\n", 179, 179, 179, 179);
        printf("\t                                                    %c",192);
        for (int i = 0; i < 39; i++) {
            printf("%c",196);
        }
        printf("%c",217);

        SetColorForText("\n\tEnter your choice: ", 2);
        scanf("%d", &choice);

        // message box for checking if user wants to exit or not
        if (choice == 3) {
            int CheckForExit = MessageBox(NULL, TEXT("Are you sure you want to Exit?"), TEXT("Choose the Wrong Choice?"), MB_YESNO);
            if (CheckForExit == 7) { // if no, choice = 4 is set
                choice = 4;
            }
        } else { // message box displayed for checking if user wants to go back or not
            int retVal = MessageBox(NULL, TEXT("Do you want to go back?"), TEXT("Choose the Wrong Choice?"), MB_YESNO);
            if (retVal == 6) { // if yes, choice = 4 is set
                choice = 4;
            } 
        }

        switch (choice) {
            case 1: // register
                loadUsers();
                registerUser();
                break;
            case 2:; // login
                loadUsers();
                int ret = loginUser();
                if (ret == 2) {
                    system("cls");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    printf("\n");
                    getBanner("HELLO ADMIN", '|');
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                    printf("\n");
                    showAdminScreen();
                } else if (ret == 1) {
                    showNewSelectionScreen();
                }
                break;
            case 3: // exit
                system("cls");
                SetColorForText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tGoodbye!\n", 2);
                SetColorForText("\n\t\t\t\t\t\t\t\t\t      See You Soon!\n", 2);
                delayTime(3000);
                system("cls");
                break;
            case 4: // dummy case for handling message boxes
                system("cls");
                break;
            default: 
                SetColorForText("\n\tInvalid Entry! Please Choose Either 1, 2 or 3\n", 4);
                delayTime(2000);
                break;
        }
    } while (choice != 3);
    
    return 0;
}