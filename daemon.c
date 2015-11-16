#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>

int main(void)
{
        pid_t pid,i;
        if((pid=fork())<0)
        {
                perror("fork");return -1;
        }else if(pid!=0)
        {
                exit(0); //结束父进程
        }
        //子进程
        setsid(); //建立新回话期
        chdir("/tmp"); //改变运行根目录
        umask(0); //设置屏蔽字
        openlog("daemon_example",LOG_CONS|LOG_PID,LOG_DAEMON);
        for(i=0;i<sysconf(_SC_OPEN_MAX);i++)
        {
                close(i);//关闭父进程打开的文件描述符
        }
        //todo
        syslog(LOG_INFO,"example log putput");
        return 0;
}
