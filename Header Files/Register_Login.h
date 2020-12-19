// Register and Login Module

// Including Learn and MainQuiz Modules
#include "Learn.h"
#include "MainQuiz.h"

// function declarations
int registerUser();
int loginUser();

int findUser(char *);
int checkUserCredentials(char *, char *);
int validatePassword(char *);

void displayLeaderBoard();

void editData();
void deleteUser();
int showUsersList();

void updateUserScore(char[], int);
void sortAllUsers();

void loadUsers();
void deleteAllNodes();
void addUserToDatabase();
void rewriteToDatabase();

void showUserSelectionScreen();
void showAdminScreen();

// Linked List for storing User Data
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

// function for registering a user
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
        // Checking whether username already exists or not
        retVal = findUser(username);
        if (retVal)
            SetColorForText("\t***User Name already Exists, please choose another one ***\n", 4);
    } while(retVal);

    // hiding characters entered by user for password 
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
        
        // we check whether password meets certain requirements
        retVal = validatePassword(password);
    } while(!retVal);

    // we ask the user to keep re-entering his/her password until ze types the correct password
    // done for validation
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

    // adding new user created to linked list
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

    // adding user data to database (file)
    addUserToDatabase();
}


// function for USER login
int loginUser() {
    char usrnm[30], pswd[30];
    int retVal, IsUserExists;

    do {
        SetColorForText("\n\tEnter your username: ", 2);
        scanf("%s", usrnm);
        SetColorForText("\tEnter your password: ", 2);

        // password entry is kept private
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

        // first we check whether the user exists in the database
        IsUserExists = findUser(usrnm);

        // the user exists or is trying to login as the ADMIN
        if (IsUserExists || strcmp(usrnm, "admin") == 0) {
            // we check whether the password matches
            retVal = checkUserCredentials(usrnm, pswd);
            if (retVal == 0) SetColorForText("\n\tInvalid Credentials!\n", 4);
        } else {
            SetColorForText("\n\tUser Not Found!\n", 4);
        }

    } while (retVal != 1 && retVal != 2);

    // if ADMIN login, we return 2
    if (retVal == 2) {
        return 2;
    } else if (retVal == 1) { // else if USER login, we return 1
        return 1;
    } 
}


// function for finding whether a user with same username exists in the database
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


// function for checking credentials on user login
int checkUserCredentials(char usrnm[], char pswd[]) {
    struct User *tempUser;

    char adminUsername[50], adminPassword[50];
    char *adminUsrnm = "admin";
    char *adminPswd = "Admin-21";

    strcpy(adminUsername, adminUsrnm);
    strcpy(adminPassword, adminPswd);   

    // if ADMIN login, return 2
    if (strcmp(adminUsername, usrnm) == 0 && strcmp(adminPassword, pswd) == 0) {
        return 2;
    }

    tempUser = HEAD;

    while (tempUser != NULL) {
        if (strcmp(tempUser->username, usrnm) == 0 && strcmp(tempUser->password, pswd) == 0) {
            CURRUSER = tempUser;
            // Return 1, if credentials match
            return 1;
        }
        tempUser = tempUser->NEXT;
    }

    // Return 0, if credentials do not match
    return 0;
}


// function for checking whether the password meets the following requirements:
// 1. Must contain 8 characters
// 2. Must contain atlease 1 digit
// 3. Must contain atleast 1 uppercase letter
// 4. Must contain atleast 1 lowercase letter 
int validatePassword(char *passwd) {
    int charC = 0, digitC = 0;
    int upperC = 0, lowerC = 0;
    int i;

    for (i=0; passwd[i] != '\0'; i++) {
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
    else {
        if (charC <= 8)
            SetColorForText("\n\n\tNeed at least 8 Characters...", 4);
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


// function for displaying the points leader board
void displayLeaderBoard() {

    // First, we sort the users present in the linked list
    sortAllUsers();
    struct User *node = HEAD;

    // if no users exist, we exit the function
    if (node == NULL) {
        SetColorForText("\n\n\t\t\t\t\t\t\tSeems Like There Aren't Any Users :( \n", 4);
        return;
    }

    // Else, we display the leaderboard
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


// function for editing user details (ADMIN)
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

        // we give the option for the ADMIN to go back
        SetColorForText("\n\tEnter your Choice: ", 2);
        scanf("%d", &choice);

        system("cls");
        switch (choice) {
            // if ADMIN decides to edit
            case 1:;
                char user[50];
                // we first check whether users exist
                int UsersFound = showUsersList();
                if (!UsersFound) {
                    // if number of users in the system = 0, we exit
                    return;  
                }

                SetColorForText("\tEnter User whose Data you want to Edit: ", 2);
                scanf("%s", user);
                
                // Take the username of the user ADMIN wants to edit and cross-check whether entered input is a registered user
                int retVal = findUser(user);
                // if user exists
                if (retVal) {
                    // First, we iterate through each node in the linked list
                    while (node != NULL) {
                        int editChoice;
                        // Next, we user matches, ADMIN chooses what to edit
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
                                    // for changing password
                                    case 1:;
                                        printf("\n\tYour Original Password is: %s\n", node->password);
                                        char newPassword[50];
                                        printf("\tEnter New Password: ");
                                        scanf("%s", newPassword);
                                        
                                        strcpy(node->password, newPassword);
                                        SetColorForText("\tPassword Changed Successfully!\n", 1);
                                        delayTime(2000);
                                        break;
                                    // for changing first name
                                    case 2:;
                                        printf("\n\tYour Original First Name is: %s\n", node->firstname);
                                        char newFname[50];
                                        printf("\tEnter New First Name: ");
                                        scanf("%s", newFname);
                                        
                                        strcpy(node->firstname, newFname);
                                        SetColorForText("\tFirst Name Changed Successfully!\n", 1);
                                        delayTime(2000);
                                        break;
                                    // for changing last name
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
                // if user not found, error is displayed
                } else {
                    SetColorForText("\n\tUser Not Found! Please Enter A Valid Username!\n", 4);
                    delayTime(500);
                }

                break;
            
            default:
                break;
        }
    } while (choice != 2);
}


// function for ADMIN to delete a user
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
        // we show the users list
        int UsersFound = showUsersList();
        
        // if no users exist, we exit the function
        if (!UsersFound) {
            return;
        }
        SetColorForText("\n\tEnter The Username of The User You Want to Delete: ", 2);
        scanf("%s", username);
        
        // we check whether user to be deleted exists in the database
        int retVal = findUser(username);

        // if user exists, we delete them
        if (retVal) {
            SetColorForText("\n\tUser Has Been Deleted Successfully\n", 4);
            delayTime(500);

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
        
        // else, we ask for a valid username
        } else {
            SetColorForText("\n\tUser Not Found! Please Enter A Valid Username!\n", 4);
            delayTime(500);
            system("cls");
        }
    }

    // after deleting the user, we write the changed data to the database
    rewriteToDatabase();
}


// function for displaying all the users (ADMIN)
int showUsersList() {
    system("cls");
    // starting from the HEAD position, we iterate through our User linked list and display all the users
    struct User *node = HEAD;
    int i = 0;
    if (node == NULL) {
        SetColorForText("\n\n\t\t\t\t\t\t\tSeems Like There Aren't Any Users :( \n", 4);
        return 0;
    } else {
        
        printf("\t\t\t\t\t\t%c", 192);
        for (int i = 0; i < 70; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

            printf("\n\t\t%c", 218);
        for (int i = 0; i < 120; i++) {
            printf("%c", 196);
        }
        printf("%c\n", 191);

        printf("\t\t%c\t\t\t\t\t\t ", 179);
        SetColorForText("U S E R  T A B L E", 2);
        printf("\t\t\t\t\t\t\t %c\n", 179);

        printf("\t\t%c", 192);
        for (int i = 0; i < 120; i++) {
            printf("%c", 196);
        }
        printf("%c\n", 217);

        printf("\t\t%c\t\t", 179);
        SetColorForText("Name", 6);
        printf("\t\t%c\t\t", 179);
        SetColorForText("User Name", 6);
        printf("\t\t%c\t", 179);
        SetColorForText("Password", 6);
        printf("\t    %c\t   ", 179);
        SetColorForText("Score", 6);
        printf("\t %c", 179);

        printf("\n\t\t%c", 192);
        for (int i = 0; i < 120; i++) {
            printf("%c", 196);
        }
        printf("%c\n", 217);

        while (node != NULL) {
            char NameStr[60];
            strcpy(NameStr, node->firstname);
            strcat(NameStr, " ");
            strcat(NameStr, node->lastname);
            printf("\t\t%c\t%-24s%c\t\t%-24s%c\t%-20s%c\t   %-14d%c\n", 179, NameStr, 179, node->username, 179, node->password, 179, node->totalScore, 179);
            node = node -> NEXT;
        }

        printf("\t\t%c", 192);
        for (int i = 0; i < 120; i++) {
            printf("%c", 196);
        }
        printf("%c\n", 217);
        
    }
    return 1;
}


// function for updating the score of the user
void updateUserScore(char username[50], int Score) {
    struct User *node = HEAD;

    while (node != NULL) {
        if (strcmp(node->username, username) == 0) {
            node->totalScore = Score;
            // after setting the score, we rewrite changed data to database
            rewriteToDatabase();
            return;
        }
        node = node->NEXT;
    }
}


// function for sorting all users based on points scored
// done for developing the ranking system (leader board)
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

    // Then, we rewrite changed linked list to file database
    rewriteToDatabase();
}


// function for loading user data to linked list
void loadUsers() {
    FILE *fp;
    struct User *tempNode, *newNode;

    delayTime(500);

    // First, we delete all the nodes
    deleteAllNodes();
    // this is a node for temporarily storing the data from the file
    tempNode = (struct User*)malloc(sizeof(struct User));
    
    fp = fopen("Data Files/Users.txt", "rb");
    // Next, we read from the file such that we read each structure/record one at a time.
    while(fread(tempNode, USERSIZE, 1, fp) > 0){
        
        newNode = (struct User*)malloc(sizeof(struct User));

        // copying data to new node
        strcpy(newNode->firstname, tempNode->firstname);
        strcpy(newNode->lastname, tempNode->lastname);
        strcpy(newNode->username, tempNode->username);
        strcpy(newNode->password, tempNode->password);
        newNode->totalScore = tempNode->totalScore;

        // adding data from database to linked list
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


// function for deleting all nodes in the linked list
void deleteAllNodes() {
    // this function is utilized for wiping out old data 
    // present in memory and adding new data present 
    // in the database (file)
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


// function for writing linked list in memory to file database
void rewriteToDatabase() {
    FILE *fptr = fopen("Data Files/Users.txt", "wb");
    struct User *node = HEAD;

    while (node != NULL) {
        fwrite(node, USERSIZE, 1, fptr);
        node = node->NEXT;
    }
    fclose(fptr);
}


// function for adding new user to database (file)
void addUserToDatabase() {
    if (TAIL == NULL) {
        printf("User Table is empty!\n");
    } else {
        FILE *fp;
        // adding user data to file in binary form for user privacy
        fp = fopen("Data Files/Users.txt", "ab");
        // we seek till EOF and add to database
        fseek(fp, 0, SEEK_END);
        fwrite(TAIL, USERSIZE, 1, fp);
        fclose(fp);
    }
}


// function for displaying User options after login
void showUserSelectionScreen() {
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
                    updateUserScore(CURRUSER->username, newScore);
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


// function for displaying ADMIN options after ADMIN login
void showAdminScreen() {
    int choice; 
    do {
        delayTime(500);
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
        printf("%c\n\n",217);

        SetColorForText("\tEnter your choice: ", 2);
        scanf("%d", &choice);

        system("cls");
        
        switch (choice) {
            case 1: 
                editData();
                rewriteToDatabase();
                break;
            case 2:
                deleteUser();
                rewriteToDatabase();
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