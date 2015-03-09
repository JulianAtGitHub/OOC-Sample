
#ifndef PARSE_H
#define PARSE_H

enum tokens {
	NUMBER = 'n',
	POSITIVE = '+',
	NAGETIVE = '-',
	ADD = '+',
	SUB = '-',
	MULT = '*',
	DIV = '/',
	L_PARENTHESES = '(',
	R_PARENTHESES = ')'
};

void error (const char * fmt, ...);

/* return error count */ 
int mainLoop(void);

#endif