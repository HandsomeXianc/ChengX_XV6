#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int parent_fd[2];
    int child_fd[2];
    //调用函数创建管道,并判断是否创建成功
    if(pipe(parent_fd) == -1)printf("Error: parernt_pipe not create...");
	if(pipe(child_fd) == -1)printf("Error: child_pipe not create...");
    //创建子进程,获取进程ID
    int pid = fork();
    //创建数据容器,保存数据
    char buf[64];
    if(pid == 0){//获取的PID == 0时为子进程
        read(parent_fd[0],buf,4);
        printf("%d: reacive %s\n",getpid(),buf);
        write(child_fd[1],"ping",strlen("ping"));
    }else{
        //PID != 0 时为父进程
        write(parent_fd[1],"pang",strlen("pang"));
        read(child_fd[0],buf,4);
		printf("%d: reacive %s\n",getpid(),buf);
    }
    close(parent_fd[0]);
    close(parent_fd[1]);
    close(child_fd[0]);
    close(child_fd[1]);
    exit(0);
}

