struct MainQuiz {
    char concept[20];
    char ques[150];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char result[50];
    struct MainQuiz *NEXT;
};
struct MainQuiz *HEADMQ = NULL;

int takeMainQuiz(int);
void loadMainQuizFromFile();
void insertMainQuiz(char[], char[], char[], char[], char[], char[], char[]);
int displayMainQuizQuestions(char[], int);
void writeScoreToUserFile(char[], int);

int takeMainQuiz(int totalScore) {
    int choice, result, testTaken=0;
    loadMainQuizFromFile();

    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    
    printf("\n\n\n\t\t\t\t\t\t\t     Choose A Topic To Take A Quiz On! \n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

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

    SetConsoleTextAttribute(hConsole, saved_attributes);

    printf("\n\tEnter Your Choice: ");
    scanf("%d", &choice);

    system("cls");

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
        default:
            break;
    }

    if (testTaken){

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

        printf("\n\t\t\t\tThank You For Taking The Quiz :) \n\t\t\t\tRedirecting You Back To The Main Menu!\n\n");
        
        SetConsoleTextAttribute(hConsole, saved_attributes);
        
        delayTime(2000);
    }

    return result;
}


void loadMainQuizFromFile() {
    FILE *fptr = fopen("mainQuizData.txt", "r");
    char buffer[500];
    int i;

    HEADMQ = NULL;
    
    printf("Loading Data.....\n");
    while (fgets(buffer, 700, fptr) != NULL) {
        char concepts[20], question[150], optionA[50], optionB[50], optionC[50], optionD[50], result[50];

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

        insertMainQuiz(concepts, question, optionA, optionB, optionC, optionD, result);

        conc = strtok(NULL, "|");
    }
}

void insertMainQuiz(char conc[20], char ques[50], char optA[20], char optB[20], char optC[20], char optD[20], char res[20]) {
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


int displayMainQuizQuestions(char concept[10], int totalScore) {
    struct MainQuiz *node = HEADMQ;
    int i = 1;

    while (node != NULL) {
        char optionChosen[20];
        if (strcmp(node->concept, concept) == 0) {
            do {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
                WORD saved_attributes;

                GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                saved_attributes = consoleInfo.wAttributes;

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("\n\nQuestion %d: %s\n", i, node->ques);

                SetConsoleTextAttribute(hConsole, saved_attributes);

                printf("Option A: %s\n", node->optionA);
                printf("Option B: %s\n", node->optionB);
                printf("Option C: %s\n", node->optionC);
                printf("Option D: %s\n", node->optionD);

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("Your Answer: ");

                SetConsoleTextAttribute(hConsole, saved_attributes);

                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                scanf("%s", optionChosen);

                SetConsoleTextAttribute(hConsole, saved_attributes);

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
                        printf("Invalid Response! Please choose either Option A, B, C or D\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        break;
                }
            } while (strncmp(optionChosen, node->result, 1) != 0 && strncmp(optionChosen, node->result, 1) != -1 && strncmp(optionChosen, node->result, 1) != -2 && strncmp(optionChosen, node->result, 1) != -3 && strncmp(optionChosen, node->result, 1) != 1 && strncmp(optionChosen, node->result, 1) != 2 && strncmp(optionChosen, node->result, 1) != 3);
        }
        node = node->NEXT;
    }
    return totalScore;
}