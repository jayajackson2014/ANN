#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
void main()
{
	//char str[10];
	int pid,key,shmid;
	pid=fork();
	key=ftok("shmfile",65);
	shmid = shmget(key,1024,0666|IPC_CREAT);
	char *str=(char*)shmat(shmid,(void*)0,0);
	
	if(pid==0)
	{
		printf("\nInside the child process");
		printf("\nwriting");
		printf("\nEnter the string to write");
		scanf("%s",str);
		
		printf("\nchild writes in shared memory %S",str);
		shmdt(str);
	}
	else if(pid>0)
	{
		
		char *str1=(char*)shmat(shmid,(void*)0,0);
		

		while(strlen(str1)==0);
		printf("\ninside the parent process:");
		printf("\nreading\n");
		printf("\ndata read from shared memory is %s",str1);
		shmdt(str1);
		shmctl(shmid,IPC_RMID,NULL);
	}
}
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message
{
long messagetype;
char text[10];
}; 
int main()
{
int key = ftok("progfile",65);
int msqid = msgget(key,0666 | IPC_CREAT);
int parentpid = getpid();
int childpid = fork();
if(childpid < 0) 
	{
        printf("fork failed\n");
        return 1;
	} 
else if(childpid == 0)
        {
	printf("in child process\n");
        struct message sndmsg; 
        printf(" enter the input message\n"); 
        scanf("%s", sndmsg.text); 
        sndmsg.messagetype = 1; 
        if(msgsnd(msqid, &sndmsg, sizeof(sndmsg.text), 0) < 0 ) 
        {
            printf("error sending message\n");
        } else
        {
            printf("sent message from child process, msg: %s\n",sndmsg.text);
        }

    }
else
        {
        wait(NULL); 
	printf("in parent process\n");
        struct message rcvmsg; 
        rcvmsg.messagetype = 1; 
        if(msgrcv(msqid, &rcvmsg, sizeof(rcvmsg.text), 1, 0) < 0) 
        {
            printf("error recieving message\n");
        } else
        {
        printf("recieved message in parent process, msg : %s\n", rcvmsg.text);
        }
        }
return 0;
}
