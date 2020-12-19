// MainQuiz Module

// Linked List structure for storing Main Quiz questions, options and result
struct MainQuiz {
    char concept[20];
    char ques[250];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char result[50];
    struct MainQuiz *NEXT;
};
struct MainQuiz *HEADMQ = NULL;

// function declarations
int takeMainQuiz(int);
void loadMainQuizFromFile();
void insertMainQuiz(char[], char[], char[], char[], char[], char[], char[]);
int displayMainQuizQuestions(char[], int);
void writeScoreToUserFile(char[], int);


// function for choosing concept in which to take the Main Quiz
int takeMainQuiz(int totalScore) {
    int choice, result, testTaken=0;

    // load quiz questions from database
    loadMainQuizFromFile();

    system("cls");

    SetColorForText("\n\n\n\t\t\t\t\t\t\t     Choose A Topic To Take A Quiz On! \n", 2);

    printf("\n\n\t\t\t\t\t\t%c", 218);
    for (int i = 0; i < 60; i++) {
        printf("%c",196);
    }
    printf("%c\n", 191);
    printf("\t\t\t\t\t\t%c%c                                                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                      1. C                                %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                                                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                      2. PYTHON                           %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                                                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                      3. OOPs                             %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                                                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                      4. GO BACK                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c%c                                                          %c%c\n", 179 ,179, 179, 179);
    printf("\t\t\t\t\t\t%c", 192);

    for (int i = 0; i < 60; i++) {
        printf("%c",196);
    }
    printf("%c\n",217);

    SetColorForText("\n\tEnter Your Choice: ", 2);

    scanf("%d", &choice);

    system("cls");

    // based on choice chosen, we display the questions and store the result
    switch (choice) {
        case 1:;
            result = displayMainQuizQuestions("C", totalScore);
            testTaken = 1;
            break;
        case 2:;
            result = displayMainQuizQuestions("Python", totalScore);
            testTaken = 1;
            break;
        case 3:;
            result = displayMainQuizQuestions("OOPS", totalScore);
            testTaken = 1;
            break;
        case 4:
            break;
        default:
            SetColorForText("\n\tINVALID ENTRY!", 4);
            delayTime(500);
            break;
    }

    if (testTaken){
        printf("\t\t\t\t\t\t\t\tYou Scored: %d Points!\n", (result-totalScore));
        SetColorForText("\n\t\t\t\t\t\t\t\tThank You For Taking The Quiz :) \n\t\t\t\t\t\t\t\tRedirecting You Back To The Main Menu!\n\n", 1);
        delayTime(2500);
    }

    // result contains the point scored by the user
    return result;
}


// function for loading main quiz questions, options and result from database
void loadMainQuizFromFile() {
    FILE *fptr = fopen("Data Files/mainQuizData.txt", "r");
    char buffer[500];
    int i;

    HEADMQ = NULL;
    
    printf("Loading Data.....\n");

    // First, we read line by line from the file
    while (fgets(buffer, 700, fptr) != NULL) {
        char concepts[20], question[250], optionA[50], optionB[50], optionC[50], optionD[50], result[50];
        
        // we have used "|" as the delimiter and based on that we split the data in the line into 
        // concept name, question, the four options and result

        char *conc = strtok(buffer, "|");
        char *ques = strtok(NULL, "|");
        char *optA = strtok(NULL, "|");
        char *optB = strtok(NULL, "|");
        char *optC = strtok(NULL, "|");
        char *optD = strtok(NULL, "|");
        char *res = strtok(NULL, "|");

        strcpy(concepts, conc);
        strcpy(question, ques);
        strcpy(optionA, optA);
        strcpy(optionB, optB);
        strcpy(optionC, optC);
        strcpy(optionD, optD);
        strcpy(result, res);

        for (i = 0; question[i] != '\0'; i++) {
            if (question[i] == '\\' && question[i+1] == 't') {
                question[i] = ' ';
                question[i+1] = '\t';
            }
            if (question[i] == '\\' && question[i+1] == 'n') {
                question[i] = ' ';
                question[i+1] = '\n';
            }   
        }

        // Then, we insert into the linked list structure
        insertMainQuiz(concepts, question, optionA, optionB, optionC, optionD, result);

        // This is for reading from the next line
        conc = strtok(NULL, "|");
    }
}


// function for inserting new data into 'MainQuiz' linked list
void insertMainQuiz(char conc[20], char ques[250], char optA[20], char optB[20], char optC[20], char optD[20], char res[20]) {
    struct MainQuiz *newData = (struct MainQuiz*)malloc(sizeof(struct MainQuiz));
    strcpy(newData->concept, conc);
    strcpy(newData->ques, ques);
    strcpy(newData->optionA, optA);
    strcpy(newData->optionB, optB);
    strcpy(newData->optionC, optC);
    strcpy(newData->optionD, optD);
    strcpy(newData->result, res);

    if (HEADMQ == NULL) {
        newData->NEXT = NULL;
        HEADMQ = newData;
        return;
    }
 
    struct MainQuiz *temp = HEADMQ;
    while (temp->NEXT != NULL) {
        temp = temp->NEXT;
    }
    temp->NEXT = newData;
    newData->NEXT = NULL;
}

// function for displaying questions of the MainQuiz
int displayMainQuizQuestions(char concept[10], int totalScore) {
    // totalScore is the present score of the user
    struct MainQuiz *node = HEADMQ;
    int i = 1;

    while (node != NULL) {
        char optionChosen[20];
        if (strcmp(node->concept, concept) == 0) {
            do {
                // gets the reference to the standard output device, which is the console
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo; // consoleInfo gets the console (CMD Prompt) information
                WORD saved_attributes;

                GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                saved_attributes = consoleInfo.wAttributes;
                // saved_attributes saves the original attributes of the console

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // setting text to green
                printf("\n\n\tQuestion %d: %s\n", i, node->ques);

                SetConsoleTextAttribute(hConsole, saved_attributes); // re-setting text to original color

                printf("\tOption A: %s\n", node->optionA);
                printf("\tOption B: %s\n", node->optionB);
                printf("\tOption C: %s\n", node->optionC);
                printf("\tOption D: %s\n", node->optionD);

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("\tYour Answer: ");

                SetConsoleTextAttribute(hConsole, saved_attributes);

                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                scanf("%s", optionChosen);

                SetConsoleTextAttribute(hConsole, saved_attributes);

                // we keep adding a point when the option chosen is correct
                int result = strncmp(optionChosen, node->result, 1);
                switch (result) {
                    case 0: 
                        totalScore++;
                        i++;
                        break;
                    case -1:
                    case -2:
                    case -3:
                    case 1:
                    case 2:
                    case 3:
                        i++;
                        break;
                    default:
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        printf("\tInvalid Response! Please choose either Option A, B, C or D\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        break;
                }
            } while (strncmp(optionChosen, node->result, 1) != 0 && strncmp(optionChosen, node->result, 1) != -1 && strncmp(optionChosen, node->result, 1) != -2 && strncmp(optionChosen, node->result, 1) != -3 && strncmp(optionChosen, node->result, 1) != 1 && strncmp(optionChosen, node->result, 1) != 2 && strncmp(optionChosen, node->result, 1) != 3);
        }
        node = node->NEXT;
    }

    // return the new score
    return totalScore;
}