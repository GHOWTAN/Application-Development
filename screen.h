//#define RED 31
//#define YELLOW 33

enum{BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
#define bg(c) (c+10) //define a macro function

#define BAR "\u2590"

//function prototypes 

void displayBar(int,int);
void gotoxy(int row, int col);
void clearScreen(void);
void resetColors(void);
void changeForeground(int);
void changeBackground(int);
void displayStringXY(char *s,int fg, int bg,int row,int col);
