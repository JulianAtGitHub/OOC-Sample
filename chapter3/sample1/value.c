
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "parse.h"

/* common */

struct Type {
	size_t size;
	void * (* ctor) (void * self, va_list ap);
	void (* dtor) (void * tree);
	double (* execute) (const void * tree);
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

static double execute (const void * tree) {
	assert(tree && * (struct Type **) tree && (* (struct Type **) tree)->execute);
	return (* (struct Type **) tree)->execute(tree);
}

void process (const void * tree) {
	printf("\t%g\n", execute(tree));
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

static double doValue (const void * tree) {
	return ((struct Value *) tree)->value;
}

static void * makeUnary (void * _self, va_list ap) {
	struct Unary * self = _self;
	self->arg = va_arg(ap, void *);
	return self;
}

static void freeUnary (void * tree) {
	dealloc(((struct Unary *) tree)->arg);
}

static double doPositive (const void * tree) {
	return execute(((struct Unary *) tree)->arg);
}

static double doNagetive (const void * tree) {
	return - execute(((struct Unary *) tree)->arg);
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

static double doAdd (const void * tree) {
	return execute(((struct Binary *) tree)->left) + execute(((struct Binary *) tree)->right);
}

static double doSub (const void * tree) {
	return execute(((struct Binary *) tree)->left) - execute(((struct Binary *) tree)->right);
}

static double doMult (const void * tree) {
	return execute(((struct Binary *) tree)->left) * execute(((struct Binary *) tree)->right);
}

static double doDiv (const void * tree) {
	double left = execute(((struct Binary *) tree)->left);
	double right = execute(((struct Binary *) tree)->right);

	assert(right != 0);
	return left / right;
}

static struct Type _Number = { sizeof(struct Value), makeValue, freeValue, doValue };
static struct Type _Positive = { sizeof(struct Unary), makeUnary, freeUnary, doPositive };
static struct Type _Nagetive = { sizeof(struct Unary), makeUnary, freeUnary, doNagetive };
static struct Type _Add = { sizeof(struct Binary), makeBinary, freeBinary, doAdd };
static struct Type _Sub = { sizeof(struct Binary), makeBinary, freeBinary, doSub };
static struct Type _Mult = { sizeof(struct Binary), makeBinary, freeBinary, doMult };
static struct Type _Div = { sizeof(struct Binary), makeBinary, freeBinary, doDiv };

const void * Number = &_Number;
const void * Positive = &_Positive;
const void * Nagetive = &_Nagetive;
const void * Add = &_Add;
const void * Sub = &_Sub;
const void * Mult = &_Mult;
const void * Div = &_Div;

