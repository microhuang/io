#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
        int fd,pid,status;
        char buf[10];
        if((fd=open("/tmp/c/fork.l",O_RDONLY))<0)
        {
                perror("open");exit(-1);
        }
        if((pid=fork())<0)
        {
                perror("fork");exit(-1);
        }else if(pid==0)
        {
                read(fd,buf,2);
                write(STDOUT_FILENO,buf,2);
        }else
        {
                //sleep(2); //刻意让父进程在子进程后运行
                if(wait(&status)!=pid)
                {
                        perror("wait");exit(-2);//让父进程等待子进程
                }
                //lseek(fd,SEEK_CUR,1);
                read(fd,buf,3);  //父进程读取的位置，接进程影响位置，为什么－－子进程复制了父进程fork调用时刻的完整内存空间。包括了进程的文件描述符表，但文件的读写位置存在于文件表
中，文件表在系统中只一份所有进程共享。所以，父子进程虽然file descriptor不共享，但读写位置互相影响（file table共享）。
                write(STDOUT_FILENO,buf,3);
                write(STDOUT_FILENO,"\n",1);
        }
        return 0;
}
