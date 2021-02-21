#include <stdio.h>
#include <stdlib.h>
#include "windows.h"

#define MAX_INPUT_LEN (32767)
#define RESTRICTED_PATH "c:\folderstopsecret"
#define NUM_ARGS (2)

int main(int argc, char* argv[])
{
	TCHAR path[MAX_INPUT_LEN];
	TCHAR fileName[MAX_INPUT_LEN];

	if (argc - 1 != NUM_ARGS)
	{
		printf_s("Not 2 args inserted.\nExpected usage: CreateFile.exe <filePath> <fileName>\n");
		return -1;
	}

	return 0;
}


