#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXNUM 100

#define max(a,b) ( ((a)>(b)) ? (a):(b) )

int main(void)
{
        fd_set rfds;
        struct timeval tv;
        int retval,fd,mfd;
        char buf[MAXNUM];
        fd=open("/dev/input/mice",O_RDONLY);//鼠标  
        mfd=max(fd,0);
        while(1)
        {
                FD_ZERO(&rfds);
                FD_SET(0,&rfds);//键盘，默认打开
                FD_SET(fd,&rfds);//
                tv.tv_sec=5;
                tv.tv_usec=0;

                retval=select(mfd+1,&rfds,NULL,NULL,&tv); //遍历从0到mfd所有文件描述符进行监控（系统最大监控数FD_SETSIZE），
                if(retval<0)
                        printf("error\n");
                if(retval==0)
                        printf("No data within 5 seconds\n");//超时返回
                if(retval>0)
                {
                        if(FD_ISSET(0,&rfds)) //键盘返回
                        {
                                printf("Data is available from keyboard now\n");
                                read(0,buf,MAXNUM);
                        }
                        if(FD_ISSET(fd,&rfds)) //鼠标返回
                        {
                                printf("Data is available from mouse now\n");
                                read(fd,buf,MAXNUM);
                        }
                }
        }
        return 0;
}
