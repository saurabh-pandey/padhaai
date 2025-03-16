#ifndef _RPN_PARSER_H
#define _RPN_PARSER_H

typedef enum {
    NUMBER,
    OP,
    NEW_LINE,
    END_OF_FILE,
    INVALID
} Token;

Token getop(char parsed_inp[]);

#endif /* _RPN_PARSER_H */