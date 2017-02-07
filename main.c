#include "screen.h"
#include "sound.h"
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){  //take command line argument
	FILE *sf; //sound file handler
	WAVHeader mywav;	//make an instance of wave header
	short int samples[FS]; //array of samples of 1 second
	int ret;


	for(;;){ //forever loop
		ret = system("arecord -r16000 -f S16_LE -c1 -d1 -q test.wav");
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT||WTERMSIG(ret)==SIGQUIT)) break;
		sf = fopen("test.wav","rb");
		if(sf!=NULL){ //IF FILE IS OPENED SUCCESSFULLY
			clearScreen(); //clear screen to display one sec of data
			fread(&mywav,sizeof(mywav),1,sf);
			displayWAVHdr(mywav);
			fread(samples, sizeof(short int), 16000, sf);  // read samples
			displayWAVData(samples);
			fclose(sf); 
		}
	} // end for loop
#ifdef DEBUG		//conditional compiling
	createTestTone(500);		//test new function
#endif
}
