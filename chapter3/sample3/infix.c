
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "parse.h"

/* common */

struct Type {
	size_t size;
	const char * name; /* node's name */
	char rank, rpar;
	void * (* ctor) (void * self, va_list ap);
	void (* dtor) (void * tree);
	void (* execute) (const void * tree, int rank, int par);
};

void * alloc (const void * _type, ...) {
	const struct Type * type = _type;
	assert(type && type->ctor);

	void * result = calloc(1, type->size);
	assert(result);

	va_list ap;
	va_start(ap, _type);
	result = type->ctor(result, ap);
	* (const struct Type **) result = type;
	va_end(ap);
	return result;
}

void dealloc (void * tree) {
	if (tree && * (struct Type **) tree && (* (struct Type **) tree)->dtor)
		(* (struct Type **) tree)->dtor(tree);
	free(tree);
}

static void execute (const void * tree, int rank, int par) {
	assert(tree && * (struct Type **) tree && (* (struct Type **) tree)->execute);
	(* (struct Type **) tree)->execute(tree, rank, par);
}

void process (const void * tree) {
	putchar('\t');
	execute(tree, 0, 0);
	putchar('\n');
}

/* type define */

struct Value {
	const void * type;
	double value;
};

struct Unary {
	const void * type;
	void * arg;
};

struct Binary {
	const void * type;
	void * left, * right;
};

/* operator */

static void * makeValue (void * _self, va_list ap) {
	struct Value * self = _self;
	self->value = va_arg(ap, double);
	return self;
}

static void freeValue (void * tree) {
	/* do nothing */
}

static void doValue (const void * tree, int rank, int par) {
	printf(" %g", ((struct Value *) tree)->value);
}

static void * makeUnary (void * _self, va_list ap) {
	struct Unary * self = _self;
	self->arg = va_arg(ap, void *);
	return self;
}

static void freeUnary (void * tree) {
	dealloc(((struct Unary *) tree)->arg);
}

static void doUnary (const void * tree, int rank, int par) {
	const struct Type * type = * (const struct Type **) tree;
	par = type->rank < rank || (par && type->rank == rank);
	if (par)
		putchar('(');

	printf(" %s", type->name);
	execute(((struct Unary *) tree)->arg, type->rank, type->rpar);

	if (par)
		putchar(')');
}

static void * makeBinary (void * _self, va_list ap) {
	struct Binary * self = _self;
	self->left = va_arg(ap, void *);
	self->right = va_arg(ap, void *);
	return self;
}

static void freeBinary (void * tree) {
	dealloc(((struct Binary *) tree)->left);
	dealloc(((struct Binary *) tree)->right);
}

static void doBinary (const void * tree, int rank, int par) {
	const struct Type * type = * (const struct Type **) tree;
	par = type->rank < rank || (par && type->rank == rank);
	if (par)
		putchar('(');

	execute(((struct Binary *) tree)->left, type->rank, 0);
	printf(" %s", type->name);
	execute(((struct Binary *) tree)->right, type->rank, type->rpar);

	if (par)
		putchar(')');
}

static struct Type _Number = { sizeof(struct Value), "", 0, 0, makeValue, freeValue, doValue };
static struct Type _Positive = { sizeof(struct Unary), "", 0, 0, makeUnary, freeUnary, doUnary };
static struct Type _Nagetive = { sizeof(struct Unary), "-", 0, 1, makeUnary, freeUnary, doUnary };
static struct Type _Add = { sizeof(struct Binary), "+", 1, 0, makeBinary, freeBinary, doBinary };
static struct Type _Sub = { sizeof(struct Binary), "-", 1, 1, makeBinary, freeBinary, doBinary };
static struct Type _Mult = { sizeof(struct Binary), "*", 2, 0, makeBinary, freeBinary, doBinary };
static struct Type _Div = { sizeof(struct Binary), "/", 2, 1, makeBinary, freeBinary, doBinary };

const void * Number = &_Number;
const void * Positive = &_Positive;
const void * Nagetive = &_Nagetive;
const void * Add = &_Add;
const void * Sub = &_Sub;
const void * Mult = &_Mult;
const void * Div = &_Div;

