#include <stdio.h>      // perror 打印错误
#include <unistd.h>     // 提供 fork execvp 系统调用
#include <sys/wait.h>   // 提供 waitpid 等待子进程
#include <fcntl.h>      // open() ... 
#include "executor.h"   // 声明头文件
#include "redirection.h"

void execute_command(struct Command *cmd) {
    pid_t pid;  // pid_t 为 Linux 中专门存放进程 ID 的类型，本质 int

    // 1.4
    // 创建子进程 + 程序替换
    pid = fork();   // 复制一个子进程

    // fork 失败
    if (pid < 0) {  // usually pid = -1
        perror("fork");
        return;
    }

    // 子进程：执行真正的外部命令
    if (pid == 0) { // 当前在子进程中
        struct RedirectBackup backup;

        if (apply_redirection(cmd, &backup) != 0) {
            _exit(1);
        }

        execvp(cmd->argv[0], cmd->argv);    // 成功，后面代码不运行
        perror("execvp");   // execvp 失败才到这里
        return;     // 更规范：_exit(1);
        
    } else {    
        // 父进程；值是子进程 PID
        waitpid(pid, NULL, 0);  // 等子进程执行完后再显示提示符
    }
}