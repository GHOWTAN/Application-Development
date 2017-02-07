#include <stdio.h>
#include "screen.h"
//function definitions

//this function displays a vertical bar on the i-th column
//of the screen, the height of vertical bar is h/3, where
// h is the decibel value of 200 samples
void displayBar(int h, int col){
	int i;
	for(i = 0; i<h/3; i++){ //the first version
		gotoxy(30-i, col);  //sound volumn over 70 db make different color
		if(h>50) changeForeground(RED);
		else changeForeground(BLUE);
		printf("%s", BAR);
	}		//for()
}			//function

void gotoxy(int row, int col){
	printf("\033[%d;%dH", row, col);
	fflush(stdout);
}

void clearScreen(void){
	printf("\033[2J");
	fflush(stdout);
}
void resetColors(void){
	printf("\033[0m");
	fflush(stdout);
}

void changeForeground(int fg){
	printf("\033[1;%dm",fg);
	fflush(stdout);
}

void changeBackground(int bg){
	printf("\033[1;%dm",bg);
	fflush(stdout);
}

void displayStringXY( char *s, int fg, int bg, int row, int col){
	gotoxy(row,col);
	changeForeground(fg);
	changeBackground(bg);
	printf("%s",s);
	resetColors();
}
