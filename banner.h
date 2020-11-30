#define BANNERSPEED 50

void    getBanner(char *, char);
void	DisplayBannerRow(int, int, char);
void delayTime(int seconds);
void SetColorForText(char*, int);

// The following Array stores the Binary Values for the Characters. Each Character has 7 rows with variable width.
// First element holds the Width of the Character and the rest the Binary Values.

int ArrAlpha[95][8] = {
{8, 0, 0, 0, 0, 0, 0, 0},               // SPACE
{3, 6, 6, 6, 6, 6, 0, 6},               // !
{8, 238, 238, 68, 0, 0, 0, 0},          // "
{8, 56, 40, 254, 40, 254, 40, 56},      // #
{8, 124, 146, 144, 124, 18, 146, 124},  // $
{8, 226, 164, 232, 16, 46, 74, 142},    // %
{8, 48, 72, 48, 112, 138, 132, 122},    // &
{2, 2, 2, 2, 0, 0, 0, 0},               // '
{6, 14, 16, 32, 32, 32, 16, 14},        // (
{6, 56, 4, 2, 2, 2, 4, 56},             // )
{8, 130, 68, 40, 254, 40, 68, 130},     // *
{8, 16, 16, 16, 254, 16, 16, 16},       // +
{6, 0, 0, 0, 56, 14, 4, 8},             // , 
{8, 0, 0, 0, 254, 0, 0, 0},             // -
{3, 0, 0, 0, 0, 0, 0, 6},               // .
{8, 2, 4, 8, 16, 32, 64, 128},          // /
{8, 56, 68, 162, 146, 138, 68, 56},     // 0
{6, 8, 24, 40, 8, 8, 8, 62},            // 1
{8, 124, 130, 2, 124, 128, 128, 254},   // 2
{8, 124, 130, 2, 124, 2, 130, 124},     // 3
{8, 128, 132, 132, 254, 4, 4, 4},       // 4
{8, 254, 128, 128, 124, 2, 130, 124},   // 5
{8, 124, 130, 128, 252, 130, 130, 124}, // 6
{8, 254, 132, 8, 16, 32, 32, 32},       // 7
{8, 124, 130, 130, 124, 130, 130, 124}, // 8
{8, 124, 130, 130, 126, 2, 130, 124},   // 9
{3, 0, 2, 2, 0, 2, 2, 0},               // :
{6, 0, 0, 56, 0, 28, 8, 16},            // ;
{5, 2, 4, 8, 16, 8, 4, 2},              // <
{6, 0, 0, 62, 0, 62, 0, 0},             // =
{5, 16, 8, 4, 2, 4, 8, 16},             // >
{6, 28, 34, 2, 4, 8, 0, 8},             // ?
{8, 124, 2, 114, 138, 178, 66, 62},     // @
{8, 16, 40, 68, 254, 130, 130, 130},    // A
{8, 252, 130, 130, 252, 130, 130, 252}, // B
{8, 124, 130, 128, 128, 128, 130, 124}, // C
{8, 252, 66, 66, 66, 66, 66, 252},      // D
{8, 252, 130, 128, 248, 128, 130, 252}, // E
{8, 252, 130, 128, 248, 128, 128, 128}, // F
{8, 252, 130, 128, 158, 130, 130, 124}, // G
{8, 130, 130, 130, 254, 130, 130, 130}, // H
{6, 62, 8, 8, 8, 8, 8, 62},             // I
{8, 254, 16, 16, 16, 16, 144, 96},      // J
{8, 130, 132, 136, 240, 136, 132, 130}, // K
{8, 128, 128, 128, 128, 128, 128, 254}, // L
{8, 130, 198, 170, 146, 130, 130, 130}, // M
{8, 130, 194, 162, 146, 138, 134, 130}, // N
{8, 124, 130, 130, 130, 130, 130, 124}, // O
{8, 252, 130, 130, 252, 128, 128, 128}, // P
{8, 120, 132, 132, 164, 148, 156, 126}, // Q
{8, 252, 130, 130, 252, 136, 132, 130}, // R
{8, 124, 130, 128, 124, 2, 130, 124},   // S
{8, 254, 16, 16, 16, 16, 16, 16},       // T
{8, 130, 130, 130, 130, 130, 130, 124}, // U
{8, 130, 130, 130, 130, 130, 68, 16},   // V
{8, 130, 130, 146, 146, 146, 146, 108}, // W
{8, 130, 68, 40, 16, 40, 68, 130},      // X
{8, 130, 68, 40, 16, 16, 16, 16},       // Y
{8, 254, 132, 8, 16, 32, 66, 254},      // Z
{6, 30, 32, 32, 32, 32, 32, 30},        // [
{8, 128, 64, 32, 16, 8, 4, 2},          // BACKSLASH
{8, 60, 2, 2, 2, 2, 2, 60},             // ]
{7, 24, 36, 66, 0, 0, 0, 0},            // ^
{7, 0, 0, 0, 0, 0, 0, 126},             // _
{4, 14, 6, 2, 0, 0, 0, 0},              // `
{8, 0, 120, 132, 4, 124, 132, 126},     // a
{7, 0, 64, 64, 64, 124, 66, 124},       // b
{7, 0, 60, 66, 64, 64, 66, 60},         // c
{7, 0, 2, 2, 62, 66, 66, 60},           // d
{7, 0, 60, 66, 66, 124, 64, 62},        // e
{7, 0, 14, 16, 124, 16, 16, 16},        // f
{7, 0, 60, 66, 66, 62, 2, 126},         // g
{8, 0, 128, 128, 184, 196, 130, 130},   // h
{4, 0, 4, 0, 4, 4, 4, 14},              // i
{5, 0, 2, 0, 2, 2, 2, 28},              // j
{5, 0, 16, 18, 20, 30, 18, 18},         // k
{4, 0, 12, 4, 4, 4, 4, 14},             // l
{8, 0, 124, 146, 146, 146, 130, 130},   // m
{7, 0, 124, 34, 34, 34, 34, 34},        // n
{7, 0, 24, 36, 66, 66, 36, 24},         // o
{7, 0, 60, 66, 66, 124, 64, 64},        // p
{7, 0, 48, 72, 72, 56, 10, 12},         // q
{7, 0, 92, 34, 32, 32, 32, 32},         // r
{7, 0, 60, 66, 60, 2, 66, 60},          // s
{5, 0, 8, 28, 8, 8, 10, 12},            // t
{8, 0, 66, 66, 66, 66, 66, 60},         // u
{6, 0, 34, 34, 34, 34, 20, 8},          // v
{8, 0, 130, 130, 146, 146, 170, 68},    // w
{7, 0, 66, 36, 24, 24, 36, 66},         // x
{6, 0, 34, 34, 30, 2, 2, 60},           // y
{7, 0, 126, 4, 8, 16, 32, 126},         // z
{5, 14, 8, 8, 24, 8, 8, 14},            // {
{2, 2, 2, 2, 0, 2, 2, 2},               // |
{5, 28, 4, 4, 6, 4, 4, 28},             // }
{7, 96, 82, 12, 0, 0, 0, 0}             // ~
}; 

void	getBanner(char	*AlphaStr, char DispChar) {
	int	i, Len, Row, AlphaIndex, Width, Num;	

	Len = strlen(AlphaStr);
	for (Row=0; Row<7; Row++) {
		for (i=0; i<Len; i++) {
			AlphaIndex = (int) AlphaStr[i] - 32;
			Width = ArrAlpha[AlphaIndex][0];
			Num = ArrAlpha[AlphaIndex][Row+1];
			DisplayBannerRow(Width, Num, DispChar);
		}

        delayTime(BANNERSPEED);

		printf("\n");
	}
}

void DisplayBannerRow(int Width, int Num, char DispChar) {
	char	BinaryStr[12] = "000000000000" ;
	int	Reminder, i;

	i = Width-1;
	while (Num != 0) {
		Reminder = Num % 2;
		BinaryStr[i] = '0'+ Reminder;
		i--;
		Num = Num/2;
	}
	
	for (i=0; i<Width; i++) {
		if(BinaryStr[i] == '0')
			printf("  ");
		else
			printf("|%c", DispChar);
	
	}
}

void delayTime(int ms) {

    clock_t start_time = clock();
    while (clock() < start_time + ms)
        ;
}

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
    printf("%s", OutputStr);
    SetConsoleTextAttribute(hConsole, saved_attributes);    
}