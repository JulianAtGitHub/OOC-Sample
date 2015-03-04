
#include <stdio.h>

#include "String.h"
#include "new.h"

int main (int argc, char ** argv) {
	void * a = alloc(String, "a");
	void * b = alloc(String, "b");
	void * aa = clone(a);

	printf("sizeOf(a) == %u \n", (unsigned int)sizeOf(a));

	if (differ(a, b))
		puts("ok");

	if (differ(a, aa))
		puts("differ?");

	if (a == aa)
		puts("clone?");

	dealloc(a);
	dealloc(b);
	dealloc(aa);

	return 0;
}