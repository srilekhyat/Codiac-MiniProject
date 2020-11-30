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
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        printf("\n");
        getBanner("WELCOME TO", '|');
        printf("\n");
        getBanner("  CODIAC", '|');

        SetConsoleTextAttribute(hConsole, saved_attributes);

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

        switch (choice) {
            case 1: 
                loadUsers();
                registerUser();
                break;
            case 2:;
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
            case 3: 
                system("cls");
                SetColorForText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tGoodbye!\n", 2);
                SetColorForText("\n\t\t\t\t\t\t\t\t\t      See You Soon!\n", 2);
                delayTime(3000);
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