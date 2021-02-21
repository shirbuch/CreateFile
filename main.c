#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <stdint.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>

#define MAX_INPUT_LEN (200) //!!!(32767)
#define RESTRICTED_PATH "c:\folderstopsecret"
#define NUM_ARGS (2)

int8_t tchar_strcpy(TCHAR* to, TCHAR* from);

int wmain(int argc, TCHAR* argv[])
{
	TCHAR path[MAX_INPUT_LEN + 1];
	TCHAR fileName[MAX_INPUT_LEN + 1];

	// Check if the number of arguments is correct
	if (argc - 1 != NUM_ARGS)
	{
		printf_s("Not 2 args inserted.\nExpected usage: CreateFile.exe <filePath> <fileName>\n");
		return -1;
	}

	// Try coping the path and file name from argv
	if (tchar_strcpy(path, argv[NUM_ARGS - 1]) || tchar_strcpy(fileName, argv[NUM_ARGS]))
	{
		printf_s("Error in reading arguments.\n");
		return -1;
	}

	// Test printing
	/*
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\x263a\x263b\n");
	wprintf(L"%ls\n%ls\n", path, fileName);
	*/

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

