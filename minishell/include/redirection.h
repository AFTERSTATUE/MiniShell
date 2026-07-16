#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "shell.h"

struct RedirectBackup { // 备份原来标准输入输出
    int saved_stdin;
    int saved_stdout;
};

// 应用重定向
int apply_redirection(struct Command *cmd, struct RedirectBackup *backup);
// 恢复重定向
void restore_redirection(struct RedirectBackup *backup);

#endif