#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int
main(int argc, char *argv[]){
  if(argc != 2){				//上述提到，这是参数总数，第一个是程序名字，第二个开始是用户输入的参数
    fprintf(2, "Error: please input one parameter..\n");
    exit(1);
  }
  int time = atoi(argv[1]);
  sleep(time);			//此处是xv内核 sys_sleep 函数的调用
  exit(0);
}

