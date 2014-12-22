#include "err.h"
#include "defines.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int server_qid = 0;
int report_qid = 0;

void exit_server()
{
    if (msgctl(server_qid, IPC_RMID, 0) == -1)
        syserr("msgctl RMID");
    if (msgctl(report_qid, IPC_RMID, 0) == -1)
        syserr("msgctl RMID");
    exit(0);
}

void setup_signal_handling()
{
    if (signal(SIGINT, exit_server) == SIG_ERR)
        syserr("signal");
}

void create_queues()
{
    const int flags = 0666 | IPC_CREAT | IPC_EXCL;
    if ((server_qid = msgget(SERVER_QUEUE_KEY, flags)) == -1)
        syserr("msgget");
    if ((report_qid  = msgget(REPORT_QUEUE_KEY, flags)) == -1)
        syserr("msgget");
}

void receive(Message* message_)
{
    if (msgrcv(server_qid, message_, sizeof(Data), 0, 0) <= 0)
        syserr("msgrcv");
}

/* void test() */
/* { */
/*     printf("sizeof(Results) = %d\n", sizeof(Results)); */
/*     printf("sizeof(Query) = %d\n", sizeof(Query)); */
/*     printf("sizeof(Data) = %d\n", sizeof(Data)); */
/*     printf("sizeof(Message) = %d\n", sizeof(Message)); */
/* } */

int main(int args, char** argv)
{
    Message message = {0};
    setup_signal_handling();
    create_queues();

    receive(&message);

    exit_server();
    return 0;
}
