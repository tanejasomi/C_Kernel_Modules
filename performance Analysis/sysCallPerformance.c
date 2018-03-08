#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
/*
@author: SomyaTaneja
Program measure and analyze time take to write large files
using two different output routine: 1) UNIX write system
and standard IO library routine fwrite.
compile: gcc -o sysCallPerformance sysCallPerformance.c
execute: ./sysCallPerformance 
*/
unsigned long stime, etime, lapsetime;
struct timeval tv;
FILE *fp;

unsigned long get_time();
/*
create, open and write files using UNIX "write"
*/
void caltime_write(char fname[20], char *str1){
   for(int i =0; i <10; i++){
	snprintf(fname,sizeof(fname),"%s%d%s","/tmp/7 ",i,".txt");
	int fd =open(fname,O_WRONLY | O_CREAT, 0644);
	write(fd,str1,strlen(str1));
	close(fd);
	}
}
/*
create, open and  write files using IO "fwrite"
*/
void caltime_fwrite(char fname[20],char *str1){

   for(int i=0;i<10;i++){
	int n = 10;
	snprintf(fname, sizeof(fname), "%s%d%s","/tmp/7 ",n,".txt");
	 fp = fopen(fname,"w");
	fwrite(str1, sizeof(char), sizeof(str1),fp);
	fflush(fp);
	n++;

   }

}
/*
calculate time taken /byte and /write operation
*/
void print_time_taken(unsigned long starttime,unsigned long endtime,int no_of_bytes){
	unsigned long time_per_write;
	unsigned long time_per_byte;
	lapsetime = endtime-starttime;
	printf("Time taken to create 10 files: %ld \n",lapsetime);
	time_per_write = lapsetime/10;
	time_per_byte = lapsetime/no_of_bytes;
	printf("Time taken per write: %ld microseconds \n",time_per_write);
        printf("Time taken per byte: %ld microseconds \n",time_per_byte);

}
/*
measure time to write large file size (2,16,128,1K,8K
and 64K)bytes using write and fwrite
*/

int main(int argc, char argv[]){
 int input_size[] = {2, 16,128, 1024, 8192,65536};
 char inputArr[] = "A";
 for(int i =0; i<6; i++){
   char outArr[65536];
   strcpy(outArr,inputArr);
   for(int j=0; j<input_size[i]-1;j++){
	strcat(outArr,inputArr);
   }
   printf("\n%ld bytes :\n ",strlen(outArr));
   char *str1 = outArr;
   char fname[20];
   memset(fname,0,20);
   fname[0] = 0;
  /*time taken by write operation*/
   printf("Time taken by write operation\n");
   stime = get_time();
   caltime_write(fname,str1);
   etime = get_time();
   print_time_taken(stime,etime,input_size[i]);
   
  /*time taken by fwrite operation */
   printf("Time taken by fwrite operation\n");
   stime = get_time();
   caltime_fwrite(fname,str1);
   etime=get_time();
   print_time_taken(stime,etime,input_size[i]);

 }

}

/*
method to return time taken in micro seconds
*/
unsigned long get_time(){
 gettimeofday(&tv,NULL);
 unsigned long ms_time = 1000000 *tv.tv_sec + tv.tv_usec;
 return ms_time; 
}


