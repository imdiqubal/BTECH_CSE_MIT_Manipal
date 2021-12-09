
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

#include<time.h>
#include<unistd.h> 
#include<fcntl.h> 
#include<dirent.h>

#include<sys/stat.h> 
#include<sys/types.h> 
#include <sys/time.h>

FILE *fptr;
char dateTodayFile[50];


/*
-t--12738348
-d--dir1
    -f--file1
    -d--dir2
        -f---
*/


// function to traverse the directory
void function(char* dir, int depth){ 

	// insitializig our variables or hadnling files in LINUX
	DIR* d; struct 
	dirent* item; 
	struct stat mystat; 
	
	// check to see if directory exists
	if((d=opendir(dir))==NULL){ 
		printf("Directory isn't opening: %s\n", dir); 
 		return; 
	}

	// changing our cwd to the location mentioned int he function
 	chdir(dir); 

 	// iterating through all items in our directory
 	while((item = readdir(d))!=NULL){

 		// getting a storing permissions in mystat
		lstat(item->d_name,&mystat); 

		// checking to see if we have a file or directory
		if(S_ISDIR(mystat.st_mode)){ 

			// for files
			if(strcmp(".",item->d_name)==0 || strcmp("..",item->d_name)==0 || strncmp(item->d_name, "filestamps", 3) == 0)
				continue; 

			// for dirs by recursive call
			// printf("%*s%s/\n",depth,"",item->d_name); 
            fprintf(fptr, "-d--%s,%d\n", item->d_name, depth);

            // printf("dir name : %s", item->d_name);

            function(item->d_name,depth+4); 

		} else {
            fprintf(fptr, "-f--%s,%d\n", item->d_name, depth);
            // printf("%*s%s\n",depth,"",item->d_name);
        } 
	} 

	// going back to upper dir
	chdir("..");
	closedir(d); 
} 

void makedir(char dir[]){
    struct stat st = {0};

    strcat(dir, "/filestamps/");

    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

void fileDateToday(){
    // get date
    time_t time_raw_format;
    struct tm * ptr_time;
    char buffer[100];

    time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );

    if(strftime(buffer,100,"%Y_%m_%d__",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }

    // get time
    time_t seconds;
    struct tm *timeStruct;
    seconds = time(NULL);
    timeStruct = localtime(&seconds);

    char tempHr[10], tempMin[10], tempSec[10];
	char timestr[50];
    bzero(timestr, sizeof(timestr));

    sprintf(tempHr, "%d_", timeStruct->tm_hour);
    strcat(timestr, tempHr);
    
    sprintf(tempMin, "%d_", timeStruct->tm_min);
    strcat(timestr, tempMin);    
    sprintf(tempSec, "%d.", timeStruct->tm_sec);
    strcat(timestr, tempSec);
    strcat(timestr, "dat");

    // concaternating timestr and buffer
    strcat(buffer, timestr);
    // printf("buffer: %s, date-time : %s, concat:%s\n", buffer, timestr, buffer);


    // copying buffer to pointer
    strcpy(dateTodayFile, buffer);
}

void makeFile(char dir[], char dateTodayFile[]){
    // strcat(dir, "/filestamps");
    strcat(dir, dateTodayFile);

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen(dir,"w+");

   if(fptr == NULL)
   {
      printf("Error!\n");   
      exit(1);             
   }
}

void timestamp(){
    time_t seconds;

    seconds = time(NULL);

    fprintf(fptr, "-t--%ld,0\n", seconds);
}



// DRIVER CODE
int main(int argc, char *argv[]){

    if(argc <= 1){
        printf("The corect way of use is [executable] [directory]");
        exit(0);
    }

    // getting root file directory name
    char dir[100], dirt[100];
    strcpy(dir, argv[1]);
    strcpy(dirt, argv[1]);

    // making 'filestamps' directory if dosent exist
    makedir(dirt);

    // getting string of today's date
    fileDateToday();

    // making file in the '/filestamps' dir
    makeFile(dirt, dateTodayFile);

    // getting todays timestamp and adding to directory
    timestamp();

    // printf("\n\n");
	// Listing our cwd and depth of traversal
	function(dir,0); 

    printf("Scanning of Directory [%s] Completed!!\n\n", dir);

    // cloding file descriptor and exiting
    fclose(fptr);
	exit(0); 
}
