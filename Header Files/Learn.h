// Learn Module

// including Quiz Module
#include "Quiz.h"

// Structure (Linked List) for storing the Concepts data
struct Data {
    char concept[20];
    char topic[30];
    char info[480];
    struct Data *NEXT;
};
struct Data *HEADL = NULL;

// function declarations
void learn();
void loadConcepts();
void insert(char[], char[], char[]);

char* chooseTopic(char*, int);
void displayTopics(char*);
void displayInfo(char*, char*);

// function for allowing user to choose the concept they want to learn
void learn() {
    int choice;
    char *conc;
    loadConcepts();
    loadQuizFromFile();

    do {
        system("cls");

        SetColorForText("\n\n\t\t\t\t\t\t\t\tChoose A Concept To Learn!\n", 2);

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
        
        SetColorForText("\n\tEnter your choice: ", 2);
        scanf("%d", &choice);

        // after taking users choice, we display relevant topics of the chosen concepts
        switch (choice) {
            case 1:;
                conc = "C";
                displayTopics(conc);
                break;
            case 2:;
                conc = "Python";
                displayTopics(conc);
                break;
            case 3:
                conc = "OOPs";
                displayTopics(conc);
                break;
            case 4:
                break;
            default:
                SetColorForText("\n\tINVALID ENTRY!", 4);
                delayTime(500);
                break;
        }
    } while (choice != 4);
}

// function for loading Learning data from the database
void loadConcepts() {
    FILE *fptr = fopen("Data Files/data.txt", "r");
    char buffer[500];
    int i;

    printf("Loading Data.....\n");
    // First, we read line by line from the file
    while (fgets(buffer, 500, fptr) != NULL) {
        char concepts[20], topics[30], information[480];

        // we have used "|" as the delimiter and based on that we split the data in the line into concept name, topic and info
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

        // Then, we insert into Data linked list
        insert(concepts, topics, information);

        // This is for reading from the next line
        conc = strtok(NULL, "|");
    }
}

// function for inserting the new data into Data Linked List
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


// function for displaying topics in a concept
void displayTopics(char *concept) {
    int choice;
    char prevTopic[30];

    do {
        system("cls");
        printf("\n\n");
        printf("                                        %c", 218);
        for (int i = 0; i < 70; i++) {
            printf("%c",196);
        }
        printf("%c\n\n",191);
        
        struct Data *node = HEADL;
        int i = 1;
        prevTopic[0] = '\0';
        while (node != NULL) {
            if (strcmp(concept, node->concept) == 0 && strcmp(prevTopic, node->topic) != 0) {
                printf("                                        |%-23s%2d.    %-22s%18s\n\n"," ", i++, node->topic,"|");
                strcpy(prevTopic, node->topic);
            }
            node = node->NEXT;
        }

        SetColorForText("                                                            Enter -1 to GO BACK to Concepts\n\n", 2);

        printf("                                        %c",192);
        for (int i = 0; i < 70; i++) {
            printf("%c",196);
        }
        printf("%c",217);


        SetColorForText("\n\tEnter your choice: ", 2);
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        // after choosing the option for topic, we send to 'chooseTopic' function to get the topic name
        char *topic = chooseTopic(concept, choice);
        if (strcmp(topic, "") != 0) {
            displayInfo(concept, topic); // then, we display information related to that topic
        } else {
            SetColorForText("\n\tINVALID ENTRY!", 4);
            delayTime(500);
        }

    } while (choice != -1);
}


// function for displaying information of given concept and given topic
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

        SetColorForText("\n\t\t\t\t\t\t\t\tWhat do you want to do? ", 2);
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        system("cls");
        switch (choice) {
            // choice for displaying information on topic chosen
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
                        delayTime(100);
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
            
            // choice for displaying mini-assessment
            case 2:
                printf("\n");
                for (int i = 0; i < 170; i++) {
                   printf("%c",196);
                }
                printf("\n");

                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("                                                          Let's Test Your Knowledge!\n");
                printf("                                                   ----------------------------------------\n");

                SetConsoleTextAttribute(hConsole, saved_attributes);

                displayQuestions(concept, topic);
                break;

            default:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("Invalid Choice. Please Choose Either -1, 1 or 2.\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                break;
        }

    } while (choice != -1);
}


// function for getting topic related to given concept and option chosen
char* chooseTopic(char* concept, int choice) {
    char *topic;
    // for topics in 'C'
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
                tempTopic = "";
                strcpy(topic, tempTopic);
                break;
        }
    }

    // for topics in 'Python'
    if (strcmp(concept, "Python") == 0) {
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
                tempTopic = "Lists";
                strcpy(topic, tempTopic);
                break;
            case 8:
                tempTopic = "Tuples";
                strcpy(topic, tempTopic);
                break;
            case 9:
                tempTopic = "Strings";
                strcpy(topic, tempTopic);
                break;
            case 10:
                tempTopic = "Dictionary";
                strcpy(topic, tempTopic);
                break;
            case 11:
                tempTopic = "Functions";
                strcpy(topic, tempTopic);
                break;
            case 12:
                tempTopic = "Modules";
                strcpy(topic, tempTopic);
                break;
            case 13:
                tempTopic = "File I/O";
                strcpy(topic, tempTopic);
                break;
            case 14:
                tempTopic = "Exceptions";
                strcpy(topic, tempTopic);
                break;
            default:
                tempTopic = "";
                strcpy(topic, tempTopic);
                break;
        }

        // for topics in 'OOPs'
        if (strcmp(concept, "OOPs") == 0) {
            char *tempTopic;
            switch (choice) {
                case 1:
                    tempTopic = "Introduction";
                    strcpy(topic, tempTopic);
                    break;
                case 2:
                    tempTopic = "Objects";
                    strcpy(topic, tempTopic);
                    break;
                case 3:
                    tempTopic = "Classes";
                    strcpy(topic, tempTopic);
                    break;
                case 4:
                    tempTopic = "Inheritance";
                    strcpy(topic, tempTopic);
                    break;
                case 5:
                    tempTopic = "Polymorphism";
                    strcpy(topic, tempTopic);
                    break;
                case 6:
                    tempTopic = "Abstraction";
                    strcpy(topic, tempTopic);
                    break;
                case 7:
                    tempTopic = "Encaspulation";
                    strcpy(topic, tempTopic);
                    break;
                default:
                    tempTopic = "";
                    strcpy(topic, tempTopic);
                    break;
            }
        }
    }
    return topic;
}