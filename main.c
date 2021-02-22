#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <stdint.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdbool.h>
#include <string.h>

//!!! todo add error codes

#define MAX_INPUT_LEN (200) //!!!(32767)
#define RESTRICTED_PATH ((TCHAR *) L"c:\\folderstopsecret")
#define EXE_ENDING ((TCHAR *) L".exe") //, ((TCHAR *) L".bat"), ((TCHAR*)L".bin"), ((TCHAR*)L".cmd") } //!!! change the search
#define NUM_ARGS (2)
#define MAKAF ((TCHAR *) L"\\") //!!!

int8_t tchar_strcpy(TCHAR* to, TCHAR* from);
bool is_substr_from_index(TCHAR* str, TCHAR* substr, size_t index);
uint8_t combine_strs(TCHAR* to, TCHAR** froms, size_t amount);

int wmain(int argc, TCHAR* argv[])
{
	TCHAR path[MAX_INPUT_LEN + 1];
	TCHAR fileName[MAX_INPUT_LEN + 1];
	TCHAR full_path[2 * (MAX_INPUT_LEN + 1)];
	TCHAR* path_and_fileName[3] = {path, MAKAF, fileName};

	/* Get and check args */
	// Check if the number of arguments is correct
	if (argc - 1 != NUM_ARGS)
	{
		printf_s("Not 2 args inserted.\nPlease beware of spaces inside path. Fix by adding \" on both sides.\nExpected usage: CreateFile.exe <filePath> <fileName>\n");
		return -1;
	}

	// Copy the path and file name from argv
	if (tchar_strcpy(path, argv[NUM_ARGS - 1]) || tchar_strcpy(fileName, argv[NUM_ARGS]))
	{
		printf_s("Error in reading arguments.\n");
		return -1;
	}

	// Check if the file is not executable	
	if (is_substr_from_index(fileName, EXE_ENDING, wcslen(fileName) - wcslen(EXE_ENDING)))
	{
		printf_s("Unexeptable file name.\n");
		return -1;
	}

	// Check if the path is valid
	if (is_substr_from_index(path, RESTRICTED_PATH, 0))
	{
		printf_s("Unexeptable path.\n");
		return -1;
	}


	/* Create the file */
	// Combine the path and the file name
	if (combine_strs(full_path, path_and_fileName, 3))
	{
		printf_s("Error in combining path and file name.\n");
		return -1;
	}

	wprintf(L"%ls\n%ls\n->\n%ls\n", path, fileName, full_path);

	// Open a handle to the file
	HANDLE hFile = CreateFile(
		L"C:\\Users\\Shir Buchner\\Documents\\צבא\\הכשרה ענפית\\2 Create File\\CreateFile\\other\\NewFile.txt",     // Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);                  // Template file handle

	if (hFile == INVALID_HANDLE_VALUE)
	{
		// Failed to open/create file
		return 2;
	}

	 // Close the handle once we don't need it.
	CloseHandle(hFile);



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

bool is_substr_from_index(TCHAR* str, TCHAR* substr, size_t index)
{
	// Check if the pointers are NULL
	if (str == NULL || substr == NULL)
	{
		return false;
	}

	// Check if index doesn't exist in str
	if (wcslen(str) < index)
	{
		return false;
	}

	// Check if the substr exist in the string from index
	for (size_t i = index; substr[i - index] != '\0'; ++i)
	{
		// Check if we finished the string or non-matching chars
		if (str[i] == '\0' || str[i] != substr[i - index])
		{
			return false;
		}
	}

	return true;
}

uint8_t combine_strs(TCHAR* to, TCHAR** froms, size_t amount)
{
	// Check if the pointers are NULL
	if (froms == NULL)
	{
		return -1;
	}

	for (size_t i = 0; i < amount; ++i)
	{
		if (froms[i] == NULL)
		{
			return -1;
		}
	}

	// Combine all strs into 'to'
	for (size_t i = 0, index = 0; i < amount; index += wcslen(froms[i]), ++i)
	{
		// Add the next str to 'to'
		if (tchar_strcpy(&(to[index]), froms[i]))
		{
			return -1;
		}
	}

	return 0;
}


// Write data to the file
/*
wchar_t* strText = L"Hello World!";
DWORD bytesWritten;
WriteFile(
	hFile,            // Handle to the file
	strText,  // Buffer to write
	wcslen(strText),   // Buffer size
	&bytesWritten,    // Bytes written
	NULL);         // Overlapped
*/

// Test printing
/*
_setmode(_fileno(stdout), _O_U16TEXT);
wprintf(L"\x263a\x263b\n");
wprintf(L"%ls\n%ls\n", path, fileName);
*/