#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <stdint.h>

#define MAX_INPUT_LEN (200) //!!!(32767)
#define RESTRICTED_PATH "c:\folderstopsecret"
#define NUM_ARGS (2)

int8_t tchar_strcpy(TCHAR* to, TCHAR* from);

int main(int argc, char* argv[])
{
	TCHAR path[MAX_INPUT_LEN + 1];
	TCHAR fileName[MAX_INPUT_LEN + 1];

	if (argc - 1 != NUM_ARGS)
	{
		printf_s("Not 2 args inserted.\nExpected usage: CreateFile.exe <filePath> <fileName>\n");
		return -1;
	}

	if (tchar_strcpy(path, argv[NUM_ARGS - 1]) || tchar_strcpy(fileName, argv[NUM_ARGS]))
	{
		printf_s("Error in reading arguments.\n");
		return -1;
	}
	
	return 0;
}

int8_t tchar_strcpy(TCHAR *to, TCHAR *from)
{
	size_t i;
	for (i = 0; from[i] != '\0'; ++i)
	{
		// Check that we aren't sliping out of the buffer
		if (i > MAX_INPUT_LEN)
		{
			return -1;
		}

		// Copy a char
		to[i] = from[i];
	}

	// Save '\0' at the end of 'to'
	to[i] = '\0';

	return 0;
}

