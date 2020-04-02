#include <stdio.h>
#include <windows.h>

#ifndef __CALC__H__
#define __CALC__H__ ;

#define NUMBER '0'

// ===========================stack
void push(double f);
double pop();
void clear();

// ============================getchar
int getch();
void ungetch(int c);

// ===============================util
int myGetop(char s[]);

#endif