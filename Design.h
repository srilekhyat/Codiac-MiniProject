void SetColorForText(char*, int);

void SetColorForText(char *OutputStr, int ColorVal) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;  
    
    switch (ColorVal) {
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case 3:
            SetConsoleTextAttribute(hConsole, 0x0003);
            break;
        case 4:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case 5:
            SetConsoleTextAttribute(hConsole, 0x0005);
            break;
        case 6:
            SetConsoleTextAttribute(hConsole, 0x0006);
            break;
        case 7:
            SetConsoleTextAttribute(hConsole, 0x0007);
            break;
        case 8:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
            break;
        case 9:
            SetConsoleTextAttribute(hConsole, 0x0009);
            break;
        case 10:
            SetConsoleTextAttribute(hConsole, 0x0010);
            break;
        default:
            break;
    }
    printf("%s\n", OutputStr);
    SetConsoleTextAttribute(hConsole, saved_attributes);    
}