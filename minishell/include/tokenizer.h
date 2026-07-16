#ifndef TOKENIZER_H
#define TOKENIZER_H

#define MAX_TOKENS 128

typedef enum {
    TOK_WORD,
    TOK_IN, // <
    TOK_OUT,    // >
    TOK_APPEND, // >>
    TOK_PIPE,   // |
    TOK_AMP     // &
} TokenType;

struct Token {
    TokenType type;
    char *text;
};

int tokenize_line(char *line, struct Token tokens[], int *token_count);

#endif