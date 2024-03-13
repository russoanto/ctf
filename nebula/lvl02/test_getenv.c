#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	printf("env: %s", getenv("PATH"));
	
	return 0;
}
