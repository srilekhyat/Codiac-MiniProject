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

void takeMainQuiz();
void loadMainQuizFromFile();
void insertMainQuiz(char[], char[], char[], char[], char[], char[], char[]);
int displayMainQuizQuestions(char[]);

void takeMainQuiz() {
    int choice, result;

    do {
        printf("\t1. C\n");
        printf("\t2. Python\n");
        printf("\t3. OOPs\n");
        printf("\t4. EXIT\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:;
                char *concept = "C";
                result = displayMainQuizQuestions(concept);
                break;
            
            default:
                break;
        }
    } while (choice != 4);
}


void loadMainQuizFromFile() {
    FILE *fptr = fopen("mainQuizData.txt", "r");
    char buffer[500];
    int i;

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


int displayMainQuizQuestions(char concept[10]) {
    struct MainQuiz *node = HEADMQ;
    int totalScore = 0, i = 1;
    
    while (node != NULL) {
        char optionChosen[20];
        if (strcmp(node->concept, concept) == 0) {
            printf("\n\nQuestion %d: %s\n", i, node->ques);
            printf("Option A: %s\n", node->optionA);
            printf("Option B: %s\n", node->optionB);
            printf("Option C: %s\n", node->optionC);
            printf("Option D: %s\n", node->optionD);

            printf("Your Answer: ");
            scanf("%s", optionChosen);

            int result = strncmp(optionChosen, node->result, 1);

            if (result == 0) {
                totalScore++;
            }
        }
        node = node->NEXT;
    }
    return totalScore;
}