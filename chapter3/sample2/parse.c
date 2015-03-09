
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "value.h"
#include "parse.h"

static jmp_buf onError;

static enum tokens token;	/* current input symbol */

static double number;	/* if NUMBER: numerical value */

/* return token = next input symbol */
static enum tokens scan (const char * buf) {
	static const char * bp;

	if (buf)
		bp = buf;	/* new input line */

	while (isspace(* bp))
		++ bp;
	if (isdigit(* bp) || * bp == '.') {
		errno = 0;
		token = NUMBER, number = strtod(bp, (char **) & bp);
		if (errno == ERANGE)
			error("bad value: %s", strerror(errno));
	} else
		token = * bp ? * bp ++ : 0;

	return token;
}

static void * sum (void);

static void * factor (void) {
	void * result;
	switch (token) {
		case POSITIVE:
			scan(0);
			return factor();
		case NAGETIVE:
			scan(0);
			return alloc(Nagetive, factor());
		default:
			error("bad factor: '%c' 0x%x", token, token);
		case NUMBER:
			result = alloc(Number, number);
			break;
		case L_PARENTHESES:
			scan(0);
			result = sum();
			if (token != R_PARENTHESES)
				error("expecting %c", R_PARENTHESES);
	}
	scan(0);
	return result;
}

/* product : factor { *|/ factor }... */
static void * product (void) {
	void * result = factor();
	const void * type;

	for (;;) {
		switch (token) {
			case MULT:
				type = Mult;
				break;
			case DIV:
				type = Div;
				break;
			default:
				return result;
		}
		scan(0);
		result = alloc(type, result, factor());
	}
}

/* sum : product { +|- product }... */
static void * sum (void) {
	void * result = product();
	const void * type;

	for (;;) {
		switch (token) {
			case ADD:
				type = Add;
				break;
			case SUB:
				type = Sub;
				break;
			default:
				return result;
		}
		scan(0);
		result = alloc(type, result, product());
	}
}

int mainLoop(void) {
	volatile int errors = 0;
	char buf [BUFSIZ] = {0, };

	if (setjmp(onError))
		++ errors;

	while (gets(buf)) {
		if (scan(buf)) {
			void * e = sum();

			if (token)
				error("trash after sum");
			process(e);
			dealloc(e);
		}
	}

	return errors;
}

void error (const char * fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap), putc('\n', stderr);
	va_end(ap);
	longjmp(onError, 1);
}