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
