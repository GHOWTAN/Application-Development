//#define DEBUG 
#define COMM

#define FS 16000  //sample rate
typedef struct{
	char ChunkID[4]; // "RIFF"
	int ChunkSize; 	
	char Format[4]; //"wave"
	char Subchunk1ID[4]; //"fmt "
	int Subchunk1Size;
	short int AudioFormat; //only two bytes
	short int NumChannels; //2bytes
	int SampleRate;
	int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
}WAVHeader;
// function prototypes
void displayWAVData(short int*);
void showID(char *);
void displayWAVHdr(WAVHeader h);
void fillID(char *, char *);
void createTestTone(int);

