#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "shell.h"

// 1.4 执行一条解析好的命令
void execute_command(struct Command *cmd);  // 结构体指针省内存

// 4.3 管道
void execute_pipeline(struct Token tokens[], int token_count,
                     char history[][MAX_LINE], int history_count);


#endif