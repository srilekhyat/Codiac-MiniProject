// Quiz Module
// Mini-Assessment Module

// function declarations
void loadQuizFromFile();
void insertQuiz(char[], char[], char[], char[], char[], char[], char[], char[]);
void displayQuestions(char*, char*);

// Linked List Quiz structure for storing Mini-Assessment concept, topic, questions, options and answer
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

// function for loading quiz questions from database file
void loadQuizFromFile() {
    FILE *fptr = fopen("Data Files/quizData.txt", "r");
    char buffer[500];
    int i;

    printf("Loading Data.....\n");
    // First, we read line-by-line from the file
    while (fgets(buffer, 500, fptr) != NULL) {
        char concepts[10], topics[20], question[80], optionA[20], optionB[20], optionC[20], optionD[20], result[20];

        // Next, we take the concept, topic, question, option and answer from each line of the file
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

        // Then, we insert into the Linked List structure
        insertQuiz(concepts, topics, question, optionA, optionB, optionC, optionD, result);

        // This is for reading from the next line
        conc = strtok(NULL, "|");
    }
}

// function for inserting each question into the Linked List structure
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


// function for displaying the main quiz questions for the given concept and topic
void displayQuestions(char concept[10], char topic[20]) {
    struct Quiz *node = HEADQ;
    int i = 1;
    
    while (node != NULL) {
        char optionChosen[20];
        if (strcmp(node->concept, concept) == 0 && strcmp(node->topic, topic) == 0) {
            do {
                // gets the reference to the standard output device, which is the console
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo; // consoleInfo gets the console (CMD Prompt) information
                WORD saved_attributes;

                GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                saved_attributes = consoleInfo.wAttributes;
                // saved_attributes saves the original attributes of the console

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // setting text to green

                printf("\nQuestion %d: %s\n", i, node->ques);
                
                SetConsoleTextAttribute(hConsole, saved_attributes); // re-setting text to original color

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