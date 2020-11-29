#include "Quiz.h"

struct Data {
    char concept[20];
    char topic[30];
    char info[480];
    struct Data *NEXT;
};
struct Data *HEADL = NULL;

void learn();
void loadConcepts();
void insert(char[], char[], char[]);
void display();
char* chooseTopic(char*, int);
void displayTopics(char*);
void displayInfo(char*, char*);
void delayTimeLearn(int);

void learn() {
    int choice;
    char *conc;
    loadConcepts();
    loadQuizFromFile();

    do {
        system("cls");

        printf("\n\n\t\t\t\t\t\t\t\tChoose A Topic To Learn!\n");

        printf("\n\n\t\t\t\t\t\t%c", 218);
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
        
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:;
                conc = "C";
                displayTopics(conc);
                break;
            case 2:;
                conc = "Python";
                displayTopics(conc);
                break;
            default:
                break;
        }
    } while (choice != 4);
}

void loadConcepts() {
    FILE *fptr = fopen("data.txt", "r");
    char buffer[500];
    int i;

    printf("Loading Data.....\n");
    while (fgets(buffer, 500, fptr) != NULL) {
        char concepts[20], topics[30], information[480];

        char *conc = strtok(buffer, "|");
        char *topic = strtok(NULL, "|");
        char *info = strtok(NULL, "|");

        strcpy(concepts, conc);
        strcpy(topics, topic);
        strcpy(information, info);

        for (i = 0; information[i] != '\0'; i++) {
            if (information[i] == '\\' && information[i+1] == 't') {
                information[i] = ' ';
                information[i+1] = '\t';
            }

            if (information[i] == '\\' && information[i+1] == 'n') {
                information[i] = ' ';
                information[i+1] = '\n';
            }
        }

        insert(concepts, topics, information);

        conc = strtok(NULL, "|");
    }
}

void insert(char conc[20], char top[30], char information[480]) {
    struct Data *newData = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newData->concept, conc);
    strcpy(newData->topic, top);
    strcpy(newData->info, information);

    if (HEADL == NULL ) {
        newData->NEXT = NULL;
        HEADL = newData;
        return;
    }
 
    struct Data *temp = HEADL;
    while (temp->NEXT != NULL) {
        temp = temp->NEXT;
    }
    temp->NEXT = newData;
    newData->NEXT = NULL;
}

void display() {
    if (HEADL == NULL) {
        printf("Empty! :(\n");
        return;
    }

    struct Data *temp = HEADL;
    while (temp != NULL) {
        printf("%s | %s | %s\n", temp->concept, temp->topic, temp->info);
        temp = temp->NEXT;
    }
}

void displayTopics(char *concept) {
    int choice;
    char prevTopic[30];

    do {
        system("cls");
        printf("\n\n");
        
        printf("                                        =======================================================================\n\n");
        struct Data *node = HEADL;
        int i = 1;
        prevTopic[0] = '\0';
        while (node != NULL) {
            if (strcmp(concept, node->concept) == 0 && strcmp(prevTopic, node->topic) != 0) {
                printf("                                        |%-23s%2d.    %-22s%18s\n\n"," ", i++, node->topic,"|");
                //printf("                                                                 %d.    %s\n\n", i++, node->topic);
                strcpy(prevTopic, node->topic);
            }
            node = node->NEXT;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        printf("                                                            Enter -1 to GO BACK to Concepts\n");
        
        SetConsoleTextAttribute(hConsole, saved_attributes);

        printf("                                        =======================================================================\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        if (choice == -1) {
            break;
        }
        char *topic = chooseTopic(concept, choice);
        displayInfo(concept, topic);

    } while (choice != -1);
}

void displayInfo(char *concept, char *topic) {
    int choice;
    system("cls");
    do {    
        printf("\n\n\t\t\t\t\t\t%c", 218);
        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n", 191);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c             Enter 1 To Continue To Information             %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c             Enter 2 To Test Your Knowledge                 %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c             Enter -1 To Go Back                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c                                                            %c\n", 179 ,179);
        printf("\t\t\t\t\t\t%c", 192);

        for (int i = 0; i < 60; i++) {
            printf("%c",196);
        }
        printf("%c\n",217);

        printf("\n\t\t\t\t\t\t\t\tWhat do you want to do? ");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        system("cls");
        switch (choice) {
            case 1:;
                struct Data *node = HEADL;
                int iter = 0;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
                WORD saved_attributes;

                GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                saved_attributes = consoleInfo.wAttributes;

                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

                printf("\n");
                for (int i = 0; i < 170; i++) {
                   printf("%c",196);
                }
                printf("\n");

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("\n                                                                        %s\n", topic);
                printf("                                                         ");
                for (int i = 0; i < 40; i++) {
                    printf("%c",196);
                }                                                            
                printf("\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                while (node != NULL) {
                    if (strcmp(concept, node->concept) == 0 && strcmp(topic, node->topic) == 0) {
                        delayTimeLearn(100);
                        printf("%s", node->info);
                    }
                    node = node->NEXT;
                }

                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

                printf("\n");
                for (int i = 0; i < 170; i++) {
                   printf("%c",196);
                }
                printf("\n");

                SetConsoleTextAttribute(hConsole, saved_attributes);
                
                break;
            
            case 2:
                printf("\n ==========================================================================================================================================================================\n");
                printf("                                                          Let's Test Your Knowledge!\n");
                printf("                                                   ----------------------------------------\n");
                displayQuestions(concept, topic);
                break;

            default:
                printf("Invalid Choice. Please Choose Either -1, 1 or 2.\n");
                break;
        }

    } while (choice != -1);
}

char* chooseTopic(char* concept, int choice) {
    char *topic;
    if (strcmp(concept, "C") == 0) {
        char *tempTopic;
        switch (choice) {
            case 1:
                tempTopic = "Introduction";
                strcpy(topic, tempTopic);
                break;
            case 2:
                tempTopic = "Input";
                strcpy(topic, tempTopic);
                break;
            case 3:
                tempTopic = "Output";
                strcpy(topic, tempTopic);
                break;
            case 4:
                tempTopic = "Operators";
                strcpy(topic, tempTopic);
                break;
            case 5:
                tempTopic = "Conditional Statements";
                strcpy(topic, tempTopic);
                break;
            case 6:
                tempTopic = "Iterative Statements";
                strcpy(topic, tempTopic);
                break;
            case 7:
                tempTopic = "Arrays";
                strcpy(topic, tempTopic);
                break;
            case 8:
                tempTopic = "Strings";
                strcpy(topic, tempTopic);
                break;
            case 9:
                tempTopic = "Functions";
                strcpy(topic, tempTopic);
                break;
            case 10:
                tempTopic = "Recursion";
                strcpy(topic, tempTopic);
                break;
            case 11:
                tempTopic = "Pointers";
                strcpy(topic, tempTopic);
                break;
            case 12:
                tempTopic = "Structures & Unions";
                strcpy(topic, tempTopic);
                break;
            case 13:
                tempTopic = "File Handling";
                strcpy(topic, tempTopic);
                break;
            default:
                break;
        }
    }
    return topic;
}

void delayTimeLearn(int ms) {

    clock_t start_time = clock();
    while (clock() < start_time + ms)
        ;
}