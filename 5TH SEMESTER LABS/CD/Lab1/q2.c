/*2. To reverse the file contents and store in another file. Also display the size of file using file handling function.*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
 FILE *fp1;
 FILE *fp2;
 int countSize;
 int i = 0;
 int ch;
 fp1 = fopen("sample.txt", "r");
 fp2 = fopen("reversesample.txt", "w");
 if (fp1 == NULL)
 {
 printf("File does not exist ! \n");
 return 0;
 }
 fseek(fp1, 0, SEEK_END);
 countSize = ftell(fp1);
 while (i < countSize)
 {
 i++;
 fseek(fp1, -i, SEEK_END);
 printf("%c", fgetc(fp1));
 }
 printf("\n");
 printf("The size of the file is = %dB\n", countSize);
 fclose(fp1);
 fp1 = fopen("sample.txt", "r");
 fseek(fp1,0,SEEK_END);
 while ((ch = fgetc(fp1)) != EOF)
 { fseek(fp1,-i,SEEK_END);
 fputc(ch, fp2);
 }
 fclose(fp1);
 fclose(fp2);
 return 0;
}
