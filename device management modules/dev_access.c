#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include<sys/time.h>
/**
OSD Assignment 5
@author Somya Taneja(gd2987)
Program to access some character device file.
Command to compile code:
gcc -O2 -Wall -Wextra dev_access.c -o dev_access
Command to run code:
sudo ./dev_access 0/1/2
**/

#ifndef MAX
  #define MAX 99999
#endif

#ifndef MINMAX
  #define MINMAX 9999
#endif



void mouseFunctionality();
void psuedoReadWriteFunction();
void readTicketFunction();
int main(int argc, char* argv[]){

//	struct timeval start, end;
//	long timelapsed =0;

	int input = -1;
	
	if (argc != 2){
		printf(" Invalid Number of arguments");
		return -1;
	}
	sscanf(argv[1],"%d",&input);

	switch(input){
		case 0:
			mouseFunctionality();
			break;
		case 1:
			psuedoReadWriteFunction();
			break;
		case 2:
			readTicketFunction();			
//printf(" \n 2 is pressed \n");
			break;
		default:
			printf("Unrecognized parameter! Input could only be 0,1,2");
			break;

	}


}
void mouseFunctionality(){
	printf("\n0 is pressed\n");
	char buffer[1];
	int readInput = -1;

	readInput = open("/dev/input/mouse0",O_RDONLY);
	if(readInput< 0){
		printf("Error: File open error /dev/input/mouse0");
		exit(-1);
	}
	while(1){
		if(read(readInput,buffer,1)<0){
			printf("Error: Read file error %d \n", readInput);
			exit(-1);

		}
		else{
			printf("\n  %d ",buffer[0]);
		}
	}

}


void psuedoReadWriteFunction(){
	printf("\n1 is pressed\n");
	struct timeval start, end;
	long timelapsed =0;
	int readInput,writeO = -1;
	int last_read,flag =0;
	int count = 0;
	char* k_buffer;
	int isError = 0;
	
	gettimeofday(&start,NULL);
	readInput = open("/dev/urandom", O_RDONLY);
	writeO = open("/dev/null",O_WRONLY);
	if(readInput< 0){
		printf("Error: Failed to open file /dev/urandom");
		exit(-1);

	}
	if(writeO < 0){
		printf("Error: Failed to open file /dev/null");
		exit(-1);
	}

	k_buffer = malloc(MINMAX *sizeof (char));
	while (count < 0){
		if(flag ==0){
			last_read = read(readInput,k_buffer,MINMAX);
			flag++;
		}
		else{
			last_read = read(readInput,k_buffer,MAX - last_read);
		}

		if(last_read < 0){
			printf("Error: Error while writing file /dev/null");
			isError = 1;
			last_read = 0;
		}
		else{
			count= count +last_read;
			if(write(writeO, k_buffer,last_read)!=last_read){
				printf("Error: Failed to write file /dev/null \n");
				isError =1;
			}

		}
	}
	close(readInput);
	close(writeO);
	//If error exit with error code -1 else calculate and print time lapsed
	if(isError == 0){
		gettimeofday(&end, NULL);
		timelapsed = (end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec*1000000 + start.tv_usec);	
		printf("Time lapsed %ld\n", timelapsed);
	}
	else{
		exit(-1);
	}
}

void readTicketFunction(){
	printf("\n 2 is pressed");
	int readInput = -1;
	int i,readRetVal = 0;
	int ticket[1];

	readInput = open("/dev/ticket0", O_RDONLY);
	if(readInput<0){
		printf("\nError: Failed to open file /dev/ticket0 \n");
		exit(-1);
	}

	for(i = 0; i< 10; i++){
		readRetVal = read(readInput, ticket, 4);
		if(readRetVal !=4){
			printf("Error: Failed to read file /dev/tiket0 return code %d",readRetVal);
			continue;
		}

		printf("%d \n", ticket[0]);
		sleep(1);

	}
	close(readInput);
}


















