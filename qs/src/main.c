#include <stdio.h>
#include <config.h>

int main(int argc, char *argv[])
{
	printf(
			"qs version %d.%d.%d by %s\n",
			VERSION_MAJOR,
			VERSION_MINOR,
			VERSION_PATCH,
			DEVELOPER
	);
	return 0;
}

