#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

int tokenize_line(char *line, struct Token tokens[], int *token_count) {
    int i = 0;
    int count = 0;
    int len = (int)strlen(line);

    while (i < len) {
        // ' '  '\t'  '\0'
        while (i < len  && (line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {
            i++;
        }

        if (i >= len) break;

        // " "
        if (line[i] == '"') {
            int start = i + 1;
            int end = start;

            while (end < len && line[end] != '"') {
                end++;
            }

            if (end >= len) {
                fprintf(stderr, "tokenizer: unmatched quote\n");
                return 0;
            }

            line[end] = '\0';
            tokens[count].type = TOK_WORD;
            tokens[count].text = &line[start];
            count++;

            i = end + 1;
            continue;
        }

        // '<'
        if (line[i] == '<') {
            tokens[count].type = TOK_IN;
            tokens[count].text = "<";
            count++;

            line[i] = '\0';
            i++;
            continue;
        }

        // '>>' / '>'
        if (line[i] == '>') {
            if (i + 1 < len && line[i+1] == '>') {
                tokens[count].type = TOK_APPEND;
                tokens[count].text = ">>";
                count++;

                line[i] = '\0';
                line[i+1] = '\0';
                i += 2;
            } else {
                tokens[count].type = TOK_OUT;
                tokens[count].text = ">";
                count++;

                line[i] = '\0';
                i++;
            }
            continue;
        }

        if (line[i] == '|') {
            tokens[count].type = TOK_PIPE;
            tokens[count].text = "|";
            count++;

            line[i] = '\0';
            i++;
            continue;
        }

        if (line[i] == '&') {
            tokens[count].type = TOK_AMP;
            tokens[count].text = "&";
            count++;

            line[i] = '\0';
            i++;
            continue;
        }

        int start = i;
        while ( i < len &&
                line[i] != ' ' &&
                line[i] != '\t' &&
                line[i] != '<' &&
                line[i] != '>' &&
                line[i] != '|' &&
                line[i] != '&' &&
                line[i] != '"') {
            i++;
        }

        tokens[count].type = TOK_WORD;
        tokens[count].text = strndup(&line[start], i - start);
        count++;
    }

    *token_count = count;
    return 1;
}