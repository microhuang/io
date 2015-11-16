#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXNUM 100

int main(void)
{
        struct pollfd fds[2];
        int retval,fd;
        char buf[MAXNUM];
        fd=open("/dev/input/mice",O_RDONLY);//鼠标
        /*if(fd<0)
        {
                perror("open");
                exit(-1);
        }*/
        fds[0].fd=0;//键盘
        fds[0].events=POLLIN;//输入事件
        fds[1].fd=fd;//鼠标
        fds[1].events=POLLIN;//
        while(1)
        {
                retval=poll(fds,2,5000); //遍历监控fds中的文件描述
                printf("retval = %d\n",retval);
                if(retval<0)
                        printf("error\n");
                if(retval==0)
                        printf("No data within 5 seconds\n");//超时返回
                if(retval>0)
                {
                        if(fds[0].revents && POLLIN) //键盘输入
                        {
                                printf("Data is available from keyboard now\n");
                                read(0,buf,MAXNUM);
                        }
                        if(fds[1].revents & POLLIN) //鼠标输入
                        {
                                printf("Data is available from mouse now\n");
                                read(fd,buf,MAXNUM);
                        }
                }
        }
        return 0;
}
