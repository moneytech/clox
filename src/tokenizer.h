#ifndef TOKNZR_H
#define TOKNZR_H
#include "ds/list.h"

typedef enum tokentype {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One character probably followed by an Equal character.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    EOF
} TokenType;

typedef struct tokenization {
    List* values;
} Tokenization;

typedef struct token {
    TokenType type;
    char* luxeme;
    char* literal;
    int column;
    int line;
} Token;

Tokenization* toknzr(const char* code);
void toknzr_destroy(Tokenization* toknz);
#endif