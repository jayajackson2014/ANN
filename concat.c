#include<stdio.h>
#include<stdlib.h>
void main()
{
	char c,f1[10],f2[10],f3[10];
	FILE *fp,*f,*fn;
	printf("Enter name of first file: ");
	scanf("%s",f1);
	printf("Enter name of second file: ");
        scanf("%s",f2);
	printf("Enter name of new file: ");
        scanf("%s",f3);
	fp=fopen(f1,"r");
	f=fopen(f2,"r");
	fn=fopen(f3,"w");
	c = fgetc(fp);
	while(c != EOF)
	{
		fputc(c,fn);
		c = fgetc(fp);
	}
	c = fgetc(f);
        while(c != EOF) 
        {
                fputc(c,fn);
                c = fgetc(f);
        }
	printf("successfull\n");
	fclose(fp);
	fclose(f);
	fclose(fn);

}
