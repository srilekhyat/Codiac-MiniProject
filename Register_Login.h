#include "Learn.h"
#include "MainQuiz.h"

int registerUser();
void showUsersList();
void writeToFile();
void loadFromFile();
void deleteAllNodes();
int findUser(char *);
int checkPassword(char *);


int loginUser();
int isUserFound(char *, char *);

void editData();
void rewriteToFile();
void deleteUser();

void showNewSelectionScreen();
void showAdminScreen();

struct User {
    char firstname[30];
    char lastname[30];
    char username[30];
    char password[30];
    struct User *PREV;
    struct User *NEXT;
};
struct User *HEAD = NULL;
struct User *TAIL = NULL;
struct User *CURRENT = NULL;

int adminFlag = 0;

#define USERSIZE sizeof(struct User)
#define isAdminFlag 0

int registerUser() {
    char fname[30], lname[30], username[30], password[30], repswd[30], tempChar;
    int retVal = 0;

    scanf("%c", &tempChar);
    printf("Enter Your First Name: ");
    scanf("%s", fname);
    printf("Enter Your Last Name: ");
    scanf("%s", lname);

    do {
        printf("Choose a User Name: ");
        scanf("%s", username);
        retVal = findUser(username);
        if (retVal)
            printf("*** User Name already Exists, please choose another one ***\n");
    } while(retVal);
    do {
        printf("Enter Your Password: ");
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
    }while(!retVal);
    for(;;){
        printf("\nRe-enter Your Password: ");
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
        printf("\n");
        //scanf("%s", repswd);

        if (strcmp(password, repswd) != 0)
            printf("Password does not match!\n");
        else
            break;
    }

    struct User *userNode = (struct User*)malloc(sizeof(struct User));
    strcpy(userNode->firstname, fname);
    strcpy(userNode->lastname, lname);
    strcpy(userNode->username, username);
    strcpy(userNode->password, password);

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

void loadFromFile() {
    FILE *fp;
    struct User *tempNode, *newNode;

    deleteAllNodes();
    tempNode = (struct User*)malloc(sizeof(struct User));
    
    fp = fopen("Users.txt", "rb");
    while(fread(tempNode, USERSIZE, 1, fp) > 0){
        
        newNode = (struct User*)malloc(sizeof(struct User));

        strcpy(newNode->firstname, tempNode->firstname);
        strcpy(newNode->lastname, tempNode->lastname);
        strcpy(newNode->username, tempNode->username);
        strcpy(newNode->password, tempNode->password);
    
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
        printf("Linked List is empty!\n");
    } else {
        printf("\n                                                                      ====================================\n");
        while (node != NULL) {
            printf("                                                                                    \n#%d: %s\n", i+1, node->username);
            node = node -> NEXT;
            i++;
        }
        printf("\n                                                                       ====================================\n");
    }
}

void deleteAllNodes(){
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
            printf("Need at least 1 Character...\n");
        if (digitC == 0)
            printf("Need at least 1 Digit...\n");
        if (upperC == 0)
            printf("Need at least 1 Upper Case Character...\n");
        if (lowerC == 0)
            printf("Need at least 1 Lower Case Character...\n");
    }
    
    return 0;
}

int findUser(char *username){
    struct User *tempUser;

    tempUser = HEAD;
    while (tempUser != NULL){
        if (!strcmp(tempUser->username, username))
            return 1;
        tempUser = tempUser->NEXT;
    }
    return 0;
}

int loginUser() {
    adminFlag = isAdminFlag;
    char usrnm[30], pswd[30];
    int retVal;

    do {
        printf("\nEnter your username: ");
        scanf("%s", usrnm);
        printf("Enter your password: ");

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
        if (retVal == 0) printf("\nInvalid Credentials!\n");

    } while (retVal != 1);

    if (adminFlag == 1) {
        return 1;
    } else if (retVal == 1 && adminFlag == 0) {
        system("cls");
        getBanner("  WELCOME", '|', 200);
        printf("\n");
        getBanner("   BACK!", '|', 200);
        return 0;
    } 
}

int isUserFound(char usrnm[], char pswd[]) {
    struct User *tempUser;
    char *adminUsrnm = "admin";
    char *adminPswd = "Admin-21";
    tempUser = HEAD;
    while (tempUser != NULL) {
        if (strcmp(tempUser->username, adminUsrnm) == 0 && strcmp(tempUser->password, adminPswd) == 0) {
            adminFlag = 1;
            return 1;
        }

        if (strcmp(tempUser->username, usrnm) == 0 && strcmp(tempUser->password, pswd) == 0) {
            CURRENT = tempUser;
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
        printf("1. Keep Editing Data\n");
        printf("2. EXIT\n");

        printf("\nEnter your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:;
            char user[50];
            showUsersList();

            printf("Enter User whose Data you want to Edit: ");
            scanf("%s", user);

            while (node != NULL) {
                int editChoice;
                if (strcmp(node->username, user) == 0) {
                    do {
                        printf("1. Password\n");
                        printf("2. First Name\n");
                        printf("3. Last Name\n");
                        printf("4. EXIT\n");

                        printf("\nEnter your choice: ");
                        scanf("%d", &editChoice);

                        if (editChoice == 4)
                            break;
                        
                        switch (editChoice) {
                            case 1:;
                                char newPassword[50];
                                printf("Enter New Password: ");
                                scanf("%s", newPassword);
                                
                                strcpy(node->password, newPassword);
                                printf("Password Changed!\n");
                                break;
                            case 2:;
                                char newFname[50];
                                printf("Enter New First Name: ");
                                scanf("%s", newFname);
                                
                                strcpy(node->firstname, newFname);
                                printf("First Name Changed!\n");
                                break;
                            case 3:;
                                char newLname[50];
                                printf("Enter New Last Name: ");
                                scanf("%s", newLname);
                                
                                strcpy(node->lastname, newLname);
                                printf("Last Name Changed!\n");
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
    showUsersList();
    char username[50];
    int choice;
    while (1) {
        printf("\nEnter 1 to Continue\n");
        printf("Enter -1 to Go Back!\n");

        printf("What do you want to do? ");
        scanf("%d", &choice);

        if (choice == -1)
            break;

        printf("\nEnter The Username of The User You Want to Delete: ");
        scanf("%s", username);

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
    }
    rewriteToFile();
}

void rewriteToFile() {
    FILE *fptr = fopen("Users.txt", "wb");
    struct User *node = HEAD;

    while (node != NULL) {
        fseek(fptr, 0, SEEK_END);
        fwrite(node, USERSIZE, 1, fptr);
        node = node->NEXT;
    }

}

void showNewSelectionScreen() {
    int choice;

    do {
        delayTime(1500);
        system("cls");
        printf("\n\n\t\t\t\t\t\t\t              What do you want to do?\n");

        printf("\t\t\t\t\t\t\t========================================================\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               1. LEARN                             ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               2. TAKE A QUIZ                       ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               3. LOOK AT THE LEADERBOARD           ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               4. LOGOUT                            ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t========================================================\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learn();
                break;
            case 2:;
                if (CURRENT != NULL) {
                    takeMainQuiz();
                }
                break;
            case 3: 
                break;
            case 4:
                printf("Logging out....");
                delayTime(500);
                break;
            default: printf("INVALID ENTRY!\n");
                break;
        }
    } while (choice != 4);
}

void showAdminScreen() {
    int choice; 
    do {
        delayTime(1500);
        system("cls");

        printf("\n\n\t\t\t\t\t\t\t              What do you want to do?\n");

        printf("\t\t\t\t\t\t\t========================================================\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               1. EDIT USER DETAILS                 ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               2. DELETE USER                       ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               3. VIEW ALL USERS                    ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               4. LOOK AT THE LEADERBOARD           ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t||               5. LOGOUT                            ||\n");
        printf("\t\t\t\t\t\t\t||                                                    ||\n");
        printf("\t\t\t\t\t\t\t========================================================\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                break;
            case 4:
                break;
            case 5:
                printf("Logging out....");
                delayTime(500);
                break;
            default: printf("INVALID ENTRY!\n");
                break;
        }
        printf("\n\n **Want to Continue? Press any key**");
        getch();
    } while (choice != 5);
}