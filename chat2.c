/* chat2.c */ 
#include <sys/types.h> 
#include <mqueue.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#define BUFSIZE 16 
#define QNAME_R "/1_queue" 
#define QNAME_W "/2_queue" 
#define PRIORITY 1 
char recv_data[BUFSIZE]; 
int main() 
{    pid_t pid;
    mqd_t qd; 
    struct mq_attr q_attr, old_q_attr; 
    int prio; 
    char buf[BUFSIZE]; 
    q_attr.mq_maxmsg =10;       /* max messagenumber in queue */ 
    q_attr.mq_msgsize = BUFSIZE; /* max message size*/ 
    pid = fork(); 
    if (pid ==0) //child 
    {
        if ((qd = mq_open(QNAME_R, O_RDONLY | O_NONBLOCK, 0600, NULL)) 
==-1) 
        { 
            perror("mq_open failed"); 
            exit(1); 
        } 
        q_attr.mq_flags =0; /* release O_NONBLOCK */ 
        if (mq_setattr(qd, &q_attr, NULL)) 
        { 
            perror("mq_setattr failed"); 
            exit(1); 
        } 
        if (mq_getattr(qd, &old_q_attr)) 
        { 
            perror("mq_getattr failed"); 
            exit(1); 
        } 
        if (!(old_q_attr.mq_flags & O_NONBLOCK)) 
            printf("O_NONBLOCK not set\n"); 
        while (1) 
        { 
            mq_receive(qd, recv_data, BUFSIZE, &prio); 
            printf("%60s", recv_data); 
        }
if (mq_close(qd) ==-1) 
        { 
            perror("mq_close failed"); 
            exit(1); 
        } 
        if (mq_unlink(QNAME_R) ==-1) 
        { 
            perror("mq_unlink failed"); 
            exit(1); 
        } 
    } 
    else if (pid >0) //parent 
    {
        if ((qd = mq_open(QNAME_W, O_CREAT | O_WRONLY, 0600, &q_attr)) 
==-1) 
        { 
            perror("mq_open failed"); 
            exit(1); 
        } 
        char input[BUFSIZE]; 
        while (1) 
        { 
            fgets(input, BUFSIZE, stdin);
    //input[BUFSIZE-1] = '\0'; 
            if (input[0] !=0) 
            { 
                if (mq_send(qd, input, BUFSIZE, PRIORITY) ==-1) 
                { 
                    perror("mq_send failed"); 
                    exit(1); 
                } 
                printf("\n"); 
            } 
            memset(input, 0, BUFSIZE); 
        } 
        if (mq_close(qd) ==-1) 
        { 
            perror("mq_close failed"); 
            exit(1); 
        } 
    } 
    else //failed 
    { 
        printf("fork failed\n"); 
    } 
}
