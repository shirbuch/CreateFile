#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <stdint.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT_LEN (200) //!!!(32767)
#define RESTRICTED_PATH ((TCHAR *) L"c:\\folderstopsecret")
#define NUM_ARGS (2)

int8_t tchar_strcpy(TCHAR* to, TCHAR* from);
bool is_prefix(TCHAR* str, TCHAR* prefix);

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

	// Copy the path and file name from argv
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

	// Check if the path is valid
	if (is_prefix(path, RESTRICTED_PATH))
	{
		printf_s("Unexeptable path.\n");
		return -1;
	}



	return 0;
}

int8_t tchar_strcpy(TCHAR *to, TCHAR *from)
{
	size_t i;

	// Check if the pointers are NULL
	if (to == NULL || from == NULL)
	{
		return -1;
	}

	// Copy the 'from' string to the 'to' string
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

bool is_prefix(TCHAR* str, TCHAR* prefix)
{
	// Check if the pointers are NULL
	if (str == NULL || prefix == NULL)
	{
		return false;
	}

	// Check if the prefix exist in the string
	for (size_t i = 0; prefix[i] != '\0'; ++i)
	{
		// Check if we finished the string or non-matching chars
		if (str[i] == '\0' || str[i] != prefix[i])
		{
			return false;
		}
	}

	return true;
}