// from https://zhuanlan.zhihu.com/p/268389190
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSGKEY 123

//消息的数据结构是以一个长整型成员变量开始的结构体
struct msgstru
{
	long msgtype;
	char msgtext[2048];
};

int main()
{
	struct msgstru msgs;
	char str[256];
	int msg_type;
	int ret_value;
	int msqid;
	int pid;

	//检查消息队列是否存在
	msqid = msgget(MSGKEY, IPC_EXCL);//(键名,权限)
	if (msqid < 0)
	{
		//创建消息队列
		msqid = msgget(MSGKEY, IPC_CREAT | 0666);
		if (msqid <0)
		{
			printf("failed to create msq | errno=%d [%s]\n", errno, strerror(errno));
			exit(-1);
		}
	}

	pid = fork();//创建子进程
	if (pid > 0)
	{
		//父进程
		while (1)
		{
			printf("Parent: input message type:\n");//输入消息类型
			scanf("%d", &msg_type);
			if (msg_type == 0)
				break;

			printf("Parent: input message to be sent:\n");//输入消息信息
			scanf("%s", str);

			msgs.msgtype = msg_type;
			strcpy(msgs.msgtext, str);

			//发送消息队列(sizeof消息的长度，而不是整个结构体的长度)
			ret_value = msgsnd(msqid, &msgs, sizeof(msgs.msgtext), IPC_NOWAIT);
			if (ret_value < 0)
			{
				printf("Parent: msgsnd() write msg failed,errno=%d[%s]\n", errno, strerror(errno));
				exit(-1);
			}
		}
	}
	else if (pid == 0)
	{
		//子进程
		while (1)
		{
			msg_type = 1;//接收的消息类型为1
			msgs.msgtype = msg_type;

			//发送消息队列(sizeof消息的长度，而不是整个结构体的长度)
			ret_value = msgrcv(msqid, &msgs, sizeof(msgs.msgtext), msgs.msgtype, IPC_NOWAIT);
			if (ret_value > 0)
			{
				printf("Child: read msg:%s\n", msgs.msgtext);
			}
		}
	}
	else
	{
		printf("fork error\n");
		//删除消息队列
		msgctl(msqid, IPC_RMID, 0);
		exit(1);
	}

	return 0;
}