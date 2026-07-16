#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "shell.h"

// 1.4 执行一条解析好的命令
void execute_command(struct Command *cmd);  // 结构体指针省内存

#endif