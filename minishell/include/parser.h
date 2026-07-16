#ifndef PARSER_H
#define PARSER_H

#include "shell.h"
#include "tokenizer.h"

// 1.3 将一行输入作为结构体 cmd 拆成 argv + argc
/*
int parse_line(char *line, struct Command *cmd);
*/

// 4.0
int parse_tokens(struct Token tokens[], int token_count, struct Command *cmd);

#endif