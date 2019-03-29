#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

void *printmes(void *ptr);
char fileNumber[1] = "1";
char search[100];
char *ms;
int main()
{
int fileCount;
printf("File  #?: "); scanf("%d",&fileCount);
printf("Word  ?: "); scanf("%s",search); 
pthread_t th[fileCount];
int iret[fileCount];
int i;
char x;
//printf("%d\n",fileCount); 
for(i=0;i<fileCount;i++)
{
	pthread_create(&th[i], NULL, printmes, (void*) ms);
	sleep(0.2);
}
void* status;
for(i=0;i<fileCount;i++)
{
	pthread_join(th[i],&status);
	iret[i] = (int)status;
}
for(i=0;i<fileCount;i++)
{
	if(iret[i] == 0)
		printf("InputThread%d.txt -> false\n",i+1);
	else
		printf("InputThread%d.txt -> true\n",i+1);
}
exit(0);
}
void *printmes( void *ptr )
{
	char str1[30] = "inputThread";
	char str2[4] = ".txt";
	char buff[1000];
	int isFound = 0;
	strcat(str1,fileNumber);
	fileNumber[0]++;
	strcat(str1,str2);
	FILE *fp;
	fp = fopen(str1,"r");
	fgets(buff, 1000, (FILE*)fp);
  	int i,j;
	for(i=0;i<strlen(buff) - strlen(search);i++)
	{
		for(j=0;j<strlen(search);j++)
		{
			if(buff[i] != search[j])
				break;
			else if(j == strlen(search) - 1)
			{
				isFound = 1;
				break;
			}
			i++;
		}
		if(isFound)
			break;
	}
	return (void*) isFound;
}
