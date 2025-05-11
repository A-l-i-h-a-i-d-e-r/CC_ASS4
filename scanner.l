%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils.h"
#include "parser.tab.h"

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line; \
    yylloc.first_column = yylloc.last_column; \
    for (int i = 0; i < yyleng; i++) { \
        if (yytext[i] == '\n') { \
            yylloc.last_line++; \
            yylloc.last_column = 1; \
        } else { \
            yylloc.last_column++; \
        } \
    }

void yyerror(const char *msg);

static char *unquote(const char *s) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Unquoting string: %s", s);
    debug_log(msg, __FILE__, __LINE__);
    size_t len = strlen(s);
    if (len < 2 || s[0] != '"' || s[len-1] != '"') {
        return strdup(s);
    }
    char *out = malloc(len - 1);
    if (!out) {
        yyerror("Memory allocation failed in unquote");
        return NULL;
    }
    char *dst = out;
    for (size_t i = 1; i < len-1; i++) {
        if (s[i] == '\\' && i+1 < len-1) {
            i++;
            switch (s[i]) {
                case '"':  *dst++ = '"';  break;
                case '\\': *dst++ = '\\'; break;
                case '/':  *dst++ = '/';  break;
                case 'b':  *dst++ = '\b'; break;
                case 'f':  *dst++ = '\f'; break;
                case 'n':  *dst++ = '\n'; break;
                case 'r':  *dst++ = '\r'; break;
                case 't':  *dst++ = '\t'; break;
                case 'u':
                    *dst++ = '\\'; *dst++ = 'u';
                    for (int k = 0; k < 4 && i+1 < len-1; k++) {
                        *dst++ = s[++i];
                    }
                    break;
                default:
                    *dst++ = s[i];
            }
        } else {
            *dst++ = s[i];
        }
    }
    *dst = '\0';
    return out;
}
%}

%option noyywrap
%option yylineno

DIGIT       [0-9]
DIGITS      {DIGIT}+
INT         -?{DIGITS}
FRAC        \.{DIGITS}
EXP         [eE][+-]?{DIGITS}
NUMBER      {INT}({FRAC})?({EXP})?
STRING      \"([^\"\\]|\\["\\/bfnrt]|\\u[0-9a-fA-F]{4})*\"
WHITESPACE  [ \t\r\n]+
TRUE        true
FALSE       false
T_NULL      null

%%
"{"         { debug_log("Token: LBRACE", __FILE__, __LINE__); return LBRACE; }
"}"         { debug_log("Token: RBRACE", __FILE__, __LINE__); return RBRACE; }
"["         { debug_log("Token: LBRACK", __FILE__, __LINE__); return LBRACK; }
"]"         { debug_log("Token: RBRACK", __FILE__, __LINE__); return RBRACK; }
":"         { debug_log("Token: COLON", __FILE__, __LINE__); return COLON; }
","         { debug_log("Token: COMMA", __FILE__, __LINE__); return COMMA; }

{STRING}    {
                char msg[128];
                snprintf(msg, sizeof(msg), "Processing STRING token: %s", yytext);
                debug_log(msg, __FILE__, __LINE__);
                char *clean_str = unquote(yytext);
                if (!clean_str) return YYerror;
                yylval.str = clean_str;
                return STRING;
            }

{NUMBER}    {
                char msg[128];
                snprintf(msg, sizeof(msg), "Processing NUMBER token: %s", yytext);
                debug_log(msg, __FILE__, __LINE__);
                yylval.str = strdup(yytext);
                if (!yylval.str) {
                    yyerror("Memory allocation failed for number");
                    return YYerror;
                }
                return NUMBER;
            }

{TRUE}      {
                debug_log("Processing TRUE token", __FILE__, __LINE__);
                yylval.str = strdup("true");
                if (!yylval.str) {
                    yyerror("Memory allocation failed for true");
                    return YYerror;
                }
                return TRUE;
            }

{FALSE}     {
                debug_log("Processing FALSE token", __FILE__, __LINE__);
                yylval.str = strdup("false");
                if (!yylval.str) {
                    yyerror("Memory allocation failed for false");
                    return YYerror;
                }
                return FALSE;
            }

{T_NULL}    {
                debug_log("Processing NULL token", __FILE__, __LINE__);
                yylval.str = strdup("");
                if (!yylval.str) {
                    yyerror("Memory allocation failed for null");
                    return YYerror;
                }
                return T_NULL;
            }

{WHITESPACE} { /* skip */ }

.           {
                char msg[64];
                snprintf(msg, sizeof(msg), "Invalid character: %s", yytext);
                yyerror(msg);
                return YYerror;
            }
%%