
#include <stdlib.h>
#include <assert.h>

#include "new.h"

void * alloc(const void * _class, ...) {
	const struct Class * desc = _class;
	void * p = calloc(1, desc->size);

	assert(p);
	* (const struct Class **) p = desc;

	if (desc->ctor) {
		va_list ap;
		va_start(ap, _class);
		p = desc->ctor(p, &ap);
		va_end(ap);
	}
	return p;
}

void dealloc (void * self) {
	const struct Class ** cp = self;
	if (self && * cp && (* cp)->dtor)
		self = (* cp)->dtor(self);
	free(self);
}

void * clone (const void * self) {
	const struct Class * const * cp = self;
	assert(self && * cp && (* cp)->clone);
	return (* cp)->clone(self);
}

int differ (const void * self, const void * b) {
	const struct Class * const * cp = self;
	assert(self && * cp && (* cp)->differ);
	return (* cp)->differ(self, b);
}

size_t sizeOf (const void * self) {
	const struct Class * const * cp = self;
	assert(self && * cp);
	return (* cp)->size;
}