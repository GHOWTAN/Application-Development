#include "screen.h"  	//header file has struct definition
#include "sound.h"
#include <stdio.h>
#include <math.h>
#define PI 3.14159

#ifdef COMM
#include <curl/curl.h>
#include <string.h>

void send_dBs(double db[]){
	CURL *curl;
	CURLcode res;
	char postdata[100]="dBs=",temp[20];
	int i;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		for(i=0;i<8;i++){
			sprintf(temp, "%.2f; ",db[i]);
			strcat(postdata, temp);
		}
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cc.puv.fi/~e1500951/PHP/sound.php");
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS, postdata);
		res =curl_easy_perform(curl);
		if(res!= CURLE_OK) printf("cannot send data!");
		curl_easy_cleanup(curl);
		curl_global_cleanup();
	}
}
#endif
//function definition of displayWAVData
void displayWAVData(short int *s){
	int i,j,k; //we need nested loops
	double sum, sum_short, rms, rmsdb;
	double short_Leq[8]; //for 1 sec there are 8 pieces of short Leq ,sound level meter

	sum_short = 0;
	k = 0;
	for(i=0;i<80;i++){  				// get calculate 80 rms values
		for(j=0,sum=0; j<FS/80; j++){   //calculate sum for N sample
			sum+= (*s)*(*s);  //accumulate square to sum
			s++;// pointer goes to next sample
		}		//end for j
		rms = sqrt(sum/(FS/80));
		rmsdb = 20*log10(rms);
		sum_short += sum;
		if(i%10 == 9){    //to calculate a short_Leq    0 to 9 to 19 to 29 ,per 10
			short_Leq[k] = 20*log10(sqrt(sum_short/(FS/8)));
			k++;
			sum_short = 0;
		}
#ifdef DEBUG 		//debug mode just print out the rmsdb value
		printf("rms %d = %.f\n", i, rmsdb);
#else //display a bar on screen
		displayBar((int)rmsdb, i);
#endif
	}   //end for i
#ifdef COMM
	send_dBs(short_Leq);
#endif
}		//function end 
//this function displays the header information of a wav file
void showID(char *s){
	int i;
	for(i=0;i<4;i++) putchar(*s++);
	puts("");
}

void displayWAVHdr(WAVHeader h){		//wave header
	double duration;
	duration =(double)h.Subchunk2Size/(h.BitsPerSample/8)/h.NumChannels/h.SampleRate;
#ifdef DEBUG 		
	printf("1. Chunk ID:"); showID(h.ChunkID);
    printf("2. Chunk size: %d\n",h.ChunkSize);
	printf("3. Format:"); showID(h.Format);
	printf("4. Sunchunk1 ID:"); showID(h.Subchunk1ID);
	printf("5. Subchunk1 size: %d\n",h.Subchunk1Size);
	printf("6. Audio format: %d\n",h.AudioFormat);
    printf("7. No. of channels:%d\n",h.NumChannels);
    printf("8. Sample rate: %d\n", h.SampleRate);
    printf("9. Byte rate: %d\n", h.ByteRate);
	printf("10.Block align: %d\n",h.BlockAlign);
	printf("11.Bits per sample: %d\n",h.BitsPerSample);
	printf("12.Subchunk2 ID:"); showID(h.Subchunk2ID);
	printf("13.Subchunk2 size: %d\n", h.Subchunk2Size);
	printf("Duration %.2f seconds\n",duration);
#else	

#endif
}

void fillID(char *id,char *s){
	int i;
	for(i=0;i<4;i++){
		*id = *s;	//copy the value of s to id
		id++;		// pointer increment to the next value
		s++;
	}
}
//function definition of create test tone, the input argument specifies the frequency 
//to generate the wave file will be 5 second, sample rate16000,1 channel, 16 bits..
void createTestTone(int freq){
	FILE *fp;
	WAVHeader wh;
	int i;
	short int sample;
	fp=fopen("test.wav","wb");	//create a file to write
	if(fp!=NULL){		//FILE SUCCESS CREATED
		fillID(wh.ChunkID,"RIFF");
		fillID(wh.Format,"WAVV");
		fillID(wh.Subchunk1ID,"fmt ");

		wh.Subchunk1Size = 16;
		wh.AudioFormat=1; wh.NumChannels = 1;
		wh.SampleRate=16000;
		wh.ByteRate=16000*2;
		wh.BlockAlign=2;
		wh.BitsPerSample=16;

		fillID(wh.Subchunk2ID,"data");
		wh.Subchunk2Size = 16000*2*5; 	//5 seconds

		wh.ChunkSize = 36 + wh.Subchunk2Size;

		fwrite(&wh,sizeof(wh),1,fp);	// write the header
		for(i=0;i<16000*5;i++){
			sample=sin(2*PI*freq*i/16000)*32768; //2 rise to power 16 divided by 2
			fwrite(&sample, sizeof(sample),1,fp);
		}
		
		fclose(fp);
	}
}
