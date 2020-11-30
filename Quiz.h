void loadQuizFromFile();
void insertQuiz(char[], char[], char[], char[], char[], char[], char[], char[]);
void displayQuestions(char*, char*);

struct Quiz {
    char concept[10];
    char topic[20];
    char ques[80];
    char optA[20];
    char optB[20];
    char optC[20];
    char optD[20];
    char res[20];
    struct Quiz *NEXT;
};
struct Quiz *HEADQ = NULL;

void loadQuizFromFile() {
    FILE *fptr = fopen("quizData.txt", "r");
    char buffer[500];
    int i;

    printf("Loading Data.....\n");
    while (fgets(buffer, 500, fptr) != NULL) {
        char concepts[10], topics[20], question[80], optionA[20], optionB[20], optionC[20], optionD[20], result[20];

        char *conc = strtok(buffer, "|");
        char *topic = strtok(NULL, "|");
        char *ques = strtok(NULL, "|");
        char *optA = strtok(NULL, "|");
        char *optB = strtok(NULL, "|");
        char *optC = strtok(NULL, "|");
        char *optD = strtok(NULL, "|");
        char *res = strtok(NULL, "|");

        strcpy(concepts, conc);
        strcpy(topics, topic);
        strcpy(question, ques);
        strcpy(optionA, optA);
        strcpy(optionB, optB);
        strcpy(optionC, optC);
        strcpy(optionD, optD);
        strcpy(result, res);

        insertQuiz(concepts, topics, question, optionA, optionB, optionC, optionD, result);

        conc = strtok(NULL, "|");
    }
}

void insertQuiz(char conc[20], char top[20], char ques[80], char optA[20], char optB[20], char optC[20], char optD[20], char res[20]) {
    struct Quiz *newData = (struct Quiz*)malloc(sizeof(struct Quiz));
    strcpy(newData->concept, conc);
    strcpy(newData->topic, top);
    strcpy(newData->ques, ques);
    strcpy(newData->optA, optA);
    strcpy(newData->optB, optB);
    strcpy(newData->optC, optC);
    strcpy(newData->optD, optD);
    strcpy(newData->res, res);

    if (HEADQ == NULL) {
        newData->NEXT = NULL;
        HEADQ = newData;
        return;
    }
 
    struct Quiz *temp = HEADQ;
    while (temp->NEXT != NULL) {
        temp = temp->NEXT;
    }
    temp->NEXT = newData;
    newData->NEXT = NULL;
}

void displayQuestions(char concept[10], char topic[20]) {
    struct Quiz *node = HEADQ;
    int i = 1;
    
    while (node != NULL) {
        char optionChosen[20];
        if (strcmp(node->concept, concept) == 0 && strcmp(node->topic, topic) == 0) {
            do {

                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
                WORD saved_attributes;

                GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                saved_attributes = consoleInfo.wAttributes;

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("\nQuestion %d: %s\n", i, node->ques);
                
                SetConsoleTextAttribute(hConsole, saved_attributes);

                printf("Option A: %s\n", node->optA);
                printf("Option B: %s\n", node->optB);
                printf("Option C: %s\n", node->optC);
                printf("Option D: %s\n", node->optD);

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("Your Answer: ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                scanf("%s", optionChosen);
                SetConsoleTextAttribute(hConsole, saved_attributes);

                int result = strncmp(optionChosen, node->res, 1);

                switch (result) {
                    case 0: 
                        i++;
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Yay! You got it right. Keep rocking!\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        break;
                    case -1:
                    case -2:
                    case -3:
                    case 1:
                    case 2:
                    case 3:
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        printf("Oops! Looks like that's the wrong answer. Try Again!\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        break;
                    default:
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        printf("Invalid Response! Please choose either Option A, B, C or D\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        break;
                }
            } while (strncmp(optionChosen, node->res, 1) != 0);
        }
        node = node->NEXT;
    }
}