#include "Learn.h"
#include "MainQuiz.h"

int registerUser();
void showUsersList();
void writeToFile();
void loadUsers();
void deleteAllNodes();
int findUser(char *);
int checkPassword(char *);


int loginUser();
int isUserFound(char *, char *);
void editData();
void rewriteToFile();
void deleteUser();

void updateCurrUser(char[], int);
void sortAllUsers();
void displayLeaderBoard();

void showNewSelectionScreen();
void showAdminScreen();

struct User {
    char firstname[30];
    char lastname[30];
    char username[30];
    char password[30];
    int totalScore;
    struct User *PREV;
    struct User *NEXT;
};
struct User *HEAD = NULL;
struct User *TAIL = NULL;
struct User *CURRUSER = NULL;

#define USERSIZE sizeof(struct User)

int registerUser() {
    char fname[30], lname[30], username[30], password[30], repswd[30], tempChar;
    int retVal = 0;

    scanf("%c", &tempChar);
    SetColorForText("\n\tEnter Your First Name: ", 2);
    scanf("%s", fname);
    SetColorForText("\tEnter Your Last Name: ", 2);
    scanf("%s", lname);

    do {
        SetColorForText("\tChoose a User Name: ", 2);
        scanf("%s", username);
        retVal = findUser(username);
        if (retVal)
            SetColorForText("\t***User Name already Exists, please choose another one ***\n", 4);
    } while(retVal);
    do {
        SetColorForText("\tEnter Your Password: ", 2);
        int p = 0;
        do {
            char c = getch();
            if (c == '\n') {
                break;
            }
            printf("*");
            password[p] = c;
            p++;
        } while (password[p-1] != '\r');
        password[p-1] = '\0';
        //scanf("%s", password);
        retVal = checkPassword(password);
    } while(!retVal);
    for(;;) {
        SetColorForText("\n\tRe-enter Your Password: ", 2);
        int p = 0;
        do {
            char c = getch();
            if (c == '\n') {
                break;
            }
            printf("*");
            repswd[p] = c;
            p++;
        } while (repswd[p-1] != '\r');
        repswd[p-1] = '\0';

        if (strcmp(password, repswd) != 0)
            SetColorForText("\n\tPassword does not match!", 4);
        else
            break;
    }

    struct User *userNode = (struct User*)malloc(sizeof(struct User));
    strcpy(userNode->firstname, fname);
    strcpy(userNode->lastname, lname);
    strcpy(userNode->username, username);
    strcpy(userNode->password, password);
    userNode->totalScore = 0;

    if (HEAD == NULL) {
        userNode->PREV = NULL;
        userNode->NEXT = NULL;
        HEAD = userNode;
        TAIL = HEAD;
    } else {
        TAIL->NEXT = userNode;
        userNode->PREV = TAIL;
        userNode->NEXT = NULL;
        TAIL = userNode;
    }
    writeToFile();
}

void writeToFile() {
    if (TAIL == NULL) {
        printf("User Table is empty!\n");
    } else {
        FILE *fp;
        fp = fopen("Users.txt", "ab");
        fseek(fp, 0, SEEK_END);
        fwrite(TAIL, USERSIZE, 1, fp);
        fclose(fp);
    }
}

void loadUsers() {
    FILE *fp;
    struct User *tempNode, *newNode;

    //printf("Loading User Table...\n");
    delayTime(500);

    deleteAllNodes();
    tempNode = (struct User*)malloc(sizeof(struct User));
    
    fp = fopen("Users.txt", "rb");
    while(fread(tempNode, USERSIZE, 1, fp) > 0){
        
        newNode = (struct User*)malloc(sizeof(struct User));

        strcpy(newNode->firstname, tempNode->firstname);
        strcpy(newNode->lastname, tempNode->lastname);
        strcpy(newNode->username, tempNode->username);
        strcpy(newNode->password, tempNode->password);
        newNode->totalScore = tempNode->totalScore;
    
        if (HEAD == NULL) {
            newNode->PREV = NULL;
            newNode->NEXT = NULL;
            HEAD = newNode;
            TAIL = HEAD;
        } else {
            TAIL->NEXT = newNode;
            newNode->PREV = TAIL;
            newNode->NEXT = NULL;
            TAIL = newNode;
        }
    }
    fclose(fp);
    free(tempNode);
}

void showUsersList() {
    struct User *node = HEAD;
    int i = 0;
    if (node == NULL) {
        printf("Seems Like There Aren't Any Users :( \n");
    } else {
        
        SetColorForText("\n\n\t\t\t\t\t\t\t\t\tList Of Users:\n", 2);

        printf("\n\n\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 70; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);

        while (node != NULL) {
            printf("\t\t\t\t\t\t\t %s %s - %s - %s - %d\n", node->firstname, node->lastname, node->username, node->password, node->totalScore);
            node = node -> NEXT;
            i++;
        }
        printf("\t\t\t\t\t\t%c", 192);
        for (int i = 0; i < 70; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);
    
    }
}

void deleteAllNodes() {
    struct User *tempNode;

    if (HEAD != NULL) {
        tempNode = HEAD;
        while (tempNode != NULL){
               HEAD = tempNode->NEXT;
               free(tempNode);
               tempNode = HEAD; 
        }
        HEAD = NULL;
        TAIL = NULL;
    }
}

int checkPassword(char *passwd){
    int charC = 0, digitC = 0;
    int upperC = 0, lowerC = 0;
    int i;

    for (i=0; passwd[i] != '\0'; i++)
    {
        if (isalpha(passwd[i])){
            charC++;
            if (passwd[i] >= 'A' && passwd[i] <= 'Z')
                upperC++;
            if (passwd[i] >= 'a' && passwd[i] <= 'z')
                lowerC++;
        }
        if (isdigit(passwd[i]))
            digitC++;
    }
    if (charC > 0 && digitC > 0 && upperC > 0 && lowerC > 0)
        return 1;
    else{
        if (charC == 0)
            SetColorForText("\n\n\tNeed at least 1 Character...", 4);
        if (digitC == 0)
            SetColorForText("\n\tNeed at least 1 Digit...", 4);
        if (upperC == 0)
            SetColorForText("\n\tNeed at least 1 Upper Case Character...", 4);
        if (lowerC == 0)
            SetColorForText("\n\tNeed at least 1 Lower Case Character...", 4);
    }
    printf("\n");
    
    return 0;
}

int findUser(char *username) {
    struct User *tempUser;

    tempUser = HEAD;
    while (tempUser != NULL) {
        if (!strcmp(tempUser->username, username))
            return 1;
        tempUser = tempUser->NEXT;
    }
    return 0;
}

int loginUser() {
    char usrnm[30], pswd[30];
    int retVal;

    do {
        SetColorForText("\n\tEnter your username: ", 2);
        scanf("%s", usrnm);
        SetColorForText("\tEnter your password: ", 2);

        int p = 0;
        do {
            char c = getch();
            if (c == '\n') {
                break;
            }
            printf("*");
            pswd[p] = c;
            p++;
        } while (pswd[p-1] != '\r');
        pswd[p-1] = '\0';

        //scanf("%s", pswd);
        retVal = isUserFound(usrnm, pswd);
        if (retVal == 0) SetColorForText("\n\tInvalid Credentials!\n", 4);

    } while (retVal != 1 && retVal != 2);

    if (retVal == 2) {
        return 2;
    } else if (retVal == 1) {
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        
        printf("\n");
        getBanner("HELLO USER", '|');

        SetConsoleTextAttribute(hConsole, saved_attributes);

        return 1;
    } 
}

int isUserFound(char usrnm[], char pswd[]) {
    struct User *tempUser;

    char adminUsername[50], adminPassword[50];
    char *adminUsrnm = "admin";
    char *adminPswd = "Admin-21";

    strcpy(adminUsername, adminUsrnm);
    strcpy(adminPassword, adminPswd);

    tempUser = HEAD;

    while (tempUser != NULL) {
        if (strcmp(adminUsername, usrnm) == 0 && strcmp(adminPassword, pswd) == 0) {
            return 2;
        } else if (strcmp(tempUser->username, usrnm) == 0 && strcmp(tempUser->password, pswd) == 0) {
            CURRUSER = tempUser;
            return 1;
        }
        tempUser = tempUser->NEXT;
    }

    return 0;
}

void editData() {
    struct User *node = HEAD;
    int choice;
    do {
        system("cls");
        printf("\n\n\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                  1. KEEP EDITING                           %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                  2. GO BACK                                %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c", 192);

        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

        SetColorForText("\n\tEnter your Choice: ", 2);
        scanf("%d", &choice);

        system("cls");
        switch (choice) {
            case 1:;
                char user[50];
                showUsersList();

                SetColorForText("\tEnter User whose Data you want to Edit: ", 2);
                scanf("%s", user);

                while (node != NULL) {
                    int editChoice;
                    if (strcmp(node->username, user) == 0) {
                        do {
                            system("cls");

                            printf("\n\n\t\t\t\t\t\t%c", 218);
                            for (int i = 0; i < 60; i++) {
                                printf("%c",196);
                            }
                            printf("%c\n", 191);
                            printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                  1. Password                               %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                  2. First Name                             %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                  3. Last Name                              %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                  4. Go Back                                %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
                            printf("\t\t\t\t\t\t%c", 192);

                            for (int i = 0; i < 60; i++) {
                                printf("%c",196);
                            }
                            printf("%c\n",217);
                            
                            SetColorForText("\n\tEnter your choice: ", 2);
                            scanf("%d", &editChoice);

                            if (editChoice == 4)
                                break;
                            
                            switch (editChoice) {
                                case 1:;
                                    printf("\n\tYour Original Password is: %s\n", node->password);
                                    char newPassword[50];
                                    printf("\tEnter New Password: ");
                                    scanf("%s", newPassword);
                                    
                                    strcpy(node->password, newPassword);
                                    SetColorForText("\tPassword Changed Successfully!\n", 1);
                                    delayTime(2000);
                                    break;
                                case 2:;
                                    printf("\n\tYour Original First Name is: %s\n", node->firstname);
                                    char newFname[50];
                                    printf("\tEnter New First Name: ");
                                    scanf("%s", newFname);
                                    
                                    strcpy(node->firstname, newFname);
                                    SetColorForText("\tFirst Name Changed Successfully!\n", 1);
                                    delayTime(2000);
                                    break;
                                case 3:;
                                    printf("\n\tYour Original Last Name is: %s\n", node->lastname);
                                    char newLname[50];
                                    printf("\tEnter New Last Name: ");
                                    scanf("%s", newLname);
                                    
                                    strcpy(node->lastname, newLname);
                                    SetColorForText("\tLast Name Changed Successfully!\n", 1);
                                    delayTime(2000);
                                    break;
                                case 4:
                                    break;
                                default:
                                    break;
                            }
                        } while (editChoice != 4);
                    }
                    if (editChoice == 4) {
                        break;
                    }
                    node = node->NEXT;
                }

                break;
            
            default:
                break;
        }
    } while (choice != 2);
}

void deleteUser() {
    struct User *userNode;
    system("cls");
    char username[50];
    int choice;
    while (1) {
        printf("\n\n\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                  1. CONTINUE                               %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                  2. GO BACK                                %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c", 192);

        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

        SetColorForText("\n\t\tWhat do you want to do? ", 2);
        scanf("%d", &choice);

        if (choice == 2)
            break;
        
        system("cls");
        showUsersList();
        SetColorForText("\n\tEnter The Username of The User You Want to Delete: ", 2);
        scanf("%s", username);
        SetColorForText("\n\tUser Has Been Deleted Successfully\n", 4);

        if (strcmp(HEAD->username, username) == 0) {
            userNode = HEAD;
            HEAD = HEAD->NEXT;
            free(userNode);
            return;
        }
        if (strcmp(TAIL->username, username) == 0) {
            userNode = TAIL;
            TAIL = TAIL->PREV;
            TAIL->NEXT = NULL;
            free(userNode);
            return;
        }
        userNode = HEAD;
        while (userNode != NULL && strcmp(userNode->username, username) != 0) {
            userNode = userNode->NEXT;
        }
        userNode->PREV->NEXT = userNode->NEXT;
        userNode->NEXT->PREV = userNode->PREV;
        free(userNode);
        system("cls");
    }
    rewriteToFile();
}

void rewriteToFile() {
    FILE *fptr = fopen("Users.txt", "wb");
    struct User *node = HEAD;

    while (node != NULL) {
        fwrite(node, USERSIZE, 1, fptr);
        node = node->NEXT;
    }
    fclose(fptr);
}

void sortAllUsers() {
    struct User *nextNode;
    struct User *currnode = HEAD;

    while (currnode != NULL) {
        nextNode = currnode->NEXT;
        while (nextNode != NULL) {
            if (currnode->totalScore < nextNode->totalScore) {
                int tempInt = currnode->totalScore;
                currnode->totalScore = nextNode->totalScore;
                nextNode->totalScore = tempInt;
                
                char tempUserStr[30], tempFNStr[30], tempLNStr[30], tempPswdStr[30];

                strcpy(tempFNStr, currnode->firstname);
                strcpy(currnode->firstname, nextNode->firstname);
                strcpy(nextNode->firstname, tempFNStr);

                
                strcpy(tempLNStr, currnode->lastname);
                strcpy(currnode->lastname, nextNode->lastname);
                strcpy(nextNode->lastname, tempLNStr);

                
                strcpy(tempUserStr, currnode->username);
                strcpy(currnode->username, nextNode->username);
                strcpy(nextNode->username, tempUserStr);

                
                strcpy(tempPswdStr, currnode->password);
                strcpy(currnode->password, nextNode->password);
                strcpy(nextNode->password, tempPswdStr);
            }
            nextNode = nextNode->NEXT;
        }
        currnode = currnode->NEXT;
    }
    rewriteToFile();
}

void displayLeaderBoard() {
    sortAllUsers();
    struct User *node = HEAD;

    printf("\n\n\t\t\t\t\t%c", 218);
    for (int i = 0; i < 80; i++) {
        printf("%c",196);
    }
    
    printf("%c\n\t\t\t\t\t%c\t\t\t   ", 191, 179);
    SetColorForText(" L E A D E R B O A R D ", 2);
    printf("%-31s%c\n\t\t\t\t\t%c", " ", 179, 192);
    for (int i = 0; i < 80; i++) {
        printf("%c",196);
    }
    printf("%c\n", 217);

    printf("\t\t\t\t\t%c\t\t ", 179);
    SetColorForText("USERNAME", 6);
    printf("\t\t%c\t\t ", 179);

    SetColorForText("Score", 6); 
    printf("\t\t\t %c\n", 179);
    printf("\t\t\t\t\t%c", 192);

    for (int i = 0; i < 80; i++) {
        printf("%c",196);
    }
    printf("%c", 217);
    int i = 0;

    while (node != NULL) {
        printf("\n\t\t\t\t\t%c%15s%d. %s\t\t%c%15s   %d\t\t\t %c", 179, " ", (i+1), node->username, 179, " ", node->totalScore, 179);
        node = node -> NEXT;
        i++;
    }

    printf("\n\t\t\t\t\t%c", 192);
    for (int i = 0; i < 80; i++) {
        printf("%c",196);
    }
    printf("%c\n", 217);
    
}

void updateCurrUser(char username[50], int Score) {
    struct User *node = HEAD;

    while (node != NULL) {
        if (strcmp(node->username, username) == 0) {
            node->totalScore = Score;
            rewriteToFile();
            return;
        }
        node = node->NEXT;
    }
}

void showNewSelectionScreen() {
    int choice;

    do {
        delayTime(1000);
        system("cls");

        SetColorForText("\n\n\t\t\t\t\t\t\t              What do you want to do?\n\n", 2);

        printf("\t\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 50; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             1. LEARN A CONCEPT                 %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             2. TAKE A QUIZ                     %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             3. VIEW THE LEADERBOARD            %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             4. LOGOUT                          %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c",192);
        for (int i = 0; i < 50; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

        SetColorForText("\tEnter your choice: ", 2);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                learn();
                break;
            case 2:;
                if (CURRUSER != NULL) {
                    int newScore = takeMainQuiz(CURRUSER->totalScore);
                    updateCurrUser(CURRUSER->username, newScore);
                }
                break;
            case 3: 
                system("cls");
                displayLeaderBoard();
                SetColorForText("\n\t\t\t\t\t\t\t   <<<<< Press Any Key To Continue >>>>>\n", 2);
                getch();
                break;
            case 4:
                SetColorForText("\tLogging out....", 4);
                delayTime(500);
                break;
            default: 
                SetColorForText("\tINVALID ENTRY!\n", 4);
                break;
        }
    } while (choice != 4);
}

void showAdminScreen() {
    int choice; 
    do {
        delayTime(1500);
        system("cls");

        SetColorForText("\n\n\t\t\t\t\t\t\t              What do you want to do?\n\n", 2);

        printf("\t\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 50; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             1. EDIT USER DETAILS               %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             2. DELETE USER                     %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             3. VIEW ALL USERS                  %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             4. VIEW THE LEADERBOARD            %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c             5. LOGOUT                          %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c%c                                                %c%c\n", 179, 179, 179, 179);
        printf("\t\t\t\t\t\t\t%c",192);
        for (int i = 0; i < 50; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

        SetColorForText("\tEnter your choice: ", 2);
        scanf("%d", &choice);

        system("cls");
        
        switch (choice) {
            case 1: 
                editData();
                rewriteToFile();
                break;
            case 2:
                deleteUser();
                rewriteToFile();
                break;
            case 3: 
                showUsersList();
                SetColorForText("\n\t\t\t\t\t\t\t  <<<<< Press Any Key To Continue >>>>>\n", 2);
                getch();
                break;
            case 4: 
                displayLeaderBoard();
                SetColorForText("\n\t\t\t\t\t\t\t  <<<<< Press Any Key To Continue >>>>>\n", 2);
                getch();
                break;
            case 5:
                SetColorForText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLogging out....", 4);
                delayTime(500);
                break;
            default: printf("\tINVALID ENTRY!\n");
                break;
        }
        if (choice == 5)
            break;
    } while (choice != 5);
}