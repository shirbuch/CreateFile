#include <stdio.h>
#include <stdlib.h>
#include "windows.h"

#define MAX_INPUT_LEN (32767)
#define RESTRICTED_PATH "c:\folderstopsecret"

int main(int argc, char* argv[])
{
	TCHAR* path;
	TCHAR* fileName;

	printf_s("argc: %d\n", argc);
	for (size_t i = 1; i < argc; ++i)
	{
		printf_s("%s\n", argv[i]);
	}

	return 0;
}
