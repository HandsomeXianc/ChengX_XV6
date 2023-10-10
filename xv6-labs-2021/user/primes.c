#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//用指针的形式，让所有子进程能够读取同一块空间的数据，num记录目前还需要筛选数子的个数
void solution(int *array,int num){
    if(num == 1){  // 筛选到最后一个数字的时候，该数字已经是质数了，所以程序也就结束了
        printf("prime is %d\n",*array);
        return;
    }
    int fd[2], i ,temp;
    int prime = *array;
    printf("prime is %d\n",prime);;
    pipe(fd);
    if(fork() == 0){		//父进程创建一个子进程(一)，子进程循环写入剩余的每一个数字到管道
        for(i = 0; i < num; i++){
            temp = *(array + i);
            write(fd[1], (char *)(&temp), 4);
        }
        exit(0);
    }
    close(fd[1]);
    if(fork() == 0){		//父进程再创建一个子进程（二），子进程读取上面一个子进程写入管道的数据
        int count = 0;		//该变量记录本轮没有被筛掉的数字个数
        char buffer[4];
        while(read(fd[0], buffer, 4) != 0){
            temp = *((int *)buffer);
            if(temp % prime != 0){
                *array = temp;
                array = array + 1;
                count ++;
            }
        }
        solution(array - count,count);
        exit(0);
    }
}

int main(int argc,char argv[]){
    int target[34];
    int i = 0;
    for(;i < 34;i++) target[i] = i + 2;
    solution(target, 34);
    exit(0);
}

