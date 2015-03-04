
#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

int main (int argc, char ** argv) {
	void * s = alloc(Set);
	void * a = add(s, alloc(Object));
	void * b = add(s, alloc(Object));
	void * c = alloc(Object);

	if (contains(s, a) && contains(s, b))
		puts("ok");

	if (contains(s, c))
		puts("contains?");

	if (differ(a, add(s, a)))
		puts("differ?");

	if (contains(s, drop(s, a)))
		puts("drop?");

	dealloc(drop(s, b));
	dealloc(drop(s, c));

	dealloc(s);

	return 0;
}