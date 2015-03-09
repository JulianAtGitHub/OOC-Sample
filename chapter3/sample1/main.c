
#include "parse.h"

int main(int argc, char const *argv[])
{
	int errors = mainLoop();
	return errors > 0;
}
