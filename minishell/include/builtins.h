#ifndef BUILTINS_H
#define BUILTINS_H

#include "shell.h"
#define TABLE_MOD 1279
#define MP 3

// 1.4.2
/*
int handle_builtin(struct Command *cmd);
*/

// 2.1 内置命令处理函数
// return 1 - 表示已经处理
// return 0 - 表示不是内置命令，交给 execute_command()
int handle_builtin( struct Command *cmd, 
                    char history[][MAX_LINE], // 2.1
                    int history_count);

// 4.1
int is_builtin(struct Command *cmd);
char *find_alias(char *str);
int str_hash(char *str);
                    
#endif