int registerUser();
void showUsersList();
void writeToFile();
void loadFromFile();
void deleteAllNodes();
int findUser(char *);
int checkPassword(char *);

void loginUser();
int isUserFound(char *, char *);
void showNewSelectionScreen();

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

#define USERSIZE sizeof(struct User)

int registerUser() {
    char fname[30], lname[30], username[30], password[30], repswd[30], tempChar;
    int retVal = 0;

    scanf("%c", &tempChar);
    printf("Enter Your First Name: ");
    scanf("%s", fname);
    printf("Enter Your Last Name: ");
    scanf("%s", lname);

    do{
        printf("Choose a User Name: ");
        scanf("%s", username);
        retVal = findUser(username);
        if (retVal)
            printf("*** User Name already Exists, please choose another one ***\n");
    }while(retVal);
    do{
        printf("Enter Your Password: ");
        scanf("%s", password);
        retVal = checkPassword(password);
    }while(!retVal);
    for(;;){
        printf("Re-enter Your Password: ");
        scanf("%s", repswd);

        if (strcmp(password, repswd) != 0)
            printf("%s:%s - Password does not match!\n", password, repswd);
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
        printf("\n====================================\n");
        while (node != NULL) {
            printf("\t#%d: %s\n", i+1, node->username);
            node = node -> NEXT;
            i++;
        }
        printf("\n====================================\n");
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

void loginUser() {
    char usrnm[30], pswd[30];
    int retVal;

    do {
        printf("\nEnter your username: ");
        scanf("%s", usrnm);
        printf("Enter your password: ");
        scanf("%s", pswd);
        retVal = isUserFound(usrnm, pswd);
        printf("Invalid Credentials!\n");

    } while (retVal != 1);

    if (retVal == 1) {
        system("cls");
        getBanner("WELCOME TO", '|', 200);
        printf("\n");
        getBanner("  CODIAC", '|', 200);
    } 
}

int isUserFound(char usrnm[], char pswd[]) {
    struct User *tempUser;
    tempUser = HEAD;
    while (tempUser != NULL) {
        if (strcmp(tempUser->username, usrnm) == 0 && strcmp(tempUser->password, pswd) == 0) {
            return 1;
        }
        tempUser = tempUser->NEXT;
    }

    return 0;

}

void showNewSelectionScreen() {
    int choice;

    printf("\n\n\t\t\t\t\t\t\t              What do you want to do?\n");

    printf("\t\t\t\t\t\t\t========================================================\n");
    printf("\t\t\t\t\t\t\t||                                                    ||\n");
    printf("\t\t\t\t\t\t\t||               1. LEARN                             ||\n");
    printf("\t\t\t\t\t\t\t||                                                    ||\n");
    printf("\t\t\t\t\t\t\t||               2. TAKE A QUIZ                       ||\n");
    printf("\t\t\t\t\t\t\t||                                                    ||\n");
    printf("\t\t\t\t\t\t\t||               3. EXIT                              ||\n");
    printf("\t\t\t\t\t\t\t||                                                    ||\n");
    printf("\t\t\t\t\t\t\t========================================================\n\n");

    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3: printf("\nEXITING THE PROGRAM!\n");
                break;
            default: printf("INVALID ENTRY!\n");
                break;
        }
    } while (choice != 3);
}