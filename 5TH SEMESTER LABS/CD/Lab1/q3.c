#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char ch;
    fp1=fopen("sample.txt","r");
    fp2=fopen("sample1.txt","r");
    fp3=fopen("merged.txt","w");
    if(fp1==NULL || fp2==NULL || fp3==NULL){
        printf("File does not exist\n");
        return 0;
    }
    b:
	while((ch=fgetc(fp1))!='\n'||EOF){
        fputc(ch,fp3);
	goto a;
	
    }

    a:
	while((ch=fgetc(fp2))!='\n'||EOF){
        fputc(ch,fp3);
    	goto b;
    }
       
    return 0;
 

}
