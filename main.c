#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <stdint.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdbool.h>
#include <string.h>
//todo remove unneccary

//todo todo add error codes

#define MAX_INPUT_LEN (200) //todo (32767)
#define RESTRICTED_FOLDER_NAME ((TCHAR *) L"\\folderstopsecret")
#define EXE_ENDING ((TCHAR *) L".exe") 
#define DATA_ENDING ((TCHAR *) L":$DATA") 
#define NUM_ARGS (2)
#define MAKAF ((TCHAR *) L"\\") //todo changename

int8_t tchar_strcpy(TCHAR* to, TCHAR* from);
bool is_substr_at_index(TCHAR* str, TCHAR* substr, size_t index);
uint8_t combine_strs(TCHAR* to, TCHAR** froms, size_t amount);
uint8_t createFile(TCHAR* full_path);
uint8_t get_full_path(int argc, TCHAR* argv[], TCHAR* full_path);
bool valid_filename(TCHAR* fileName);
bool valid_path(TCHAR* path);
bool is_substr(TCHAR* str, TCHAR* substr);

int wmain(int argc, TCHAR* argv[]) //todo puth sections into functions
{
	TCHAR full_path[2 * (MAX_INPUT_LEN + 1)];

	/* Get and check args */
	if(get_full_path(argc,argv, full_path))
	{
		return -1;
	}

	/* Create the file */
	if (createFile(full_path))
	{
		printf_s("Unable to create file.\n");
		return 1;
	}

	printf("%d\n", is_substr(L"hello", L"nk"));

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

bool is_substr_at_index(TCHAR* str, TCHAR* substr, size_t index)
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
		if (str[i] == '\0' || tolower(str[i]) != tolower(substr[i - index]))
		{
			return false;
		}
	}

	return true;
}

bool is_substr(TCHAR* str, TCHAR* substr)
{
	// Check if the pointers are NULL
	if (str == NULL || substr == NULL)
	{
		return false;
	}

	if (substr[0] == '\0')
	{
		return true;
	}

	// Check if the substr exist in the string from index
	for (size_t i = 0; i <= MAX_INPUT_LEN && str[i] != '\0'; ++i)
	{
		for (size_t j = 0; j <= MAX_INPUT_LEN && str[i + j] == substr[j]; ++j)
		{
			if (substr[j + 1] == '\0')
			{
				return true;
			}
		}
	}

	return false;
}

uint8_t get_full_path(int argc, TCHAR* argv[], TCHAR* full_path)
{
	TCHAR path[MAX_INPUT_LEN + 1];
	TCHAR fileName[MAX_INPUT_LEN + 1];
	TCHAR* path_and_fileName[3] = { path, MAKAF, fileName };

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
	if (!valid_filename(fileName))
	{
		printf_s("Unexeptable file name.\n");
		return -1;
	}

	// Check if the path is valid
	if (!valid_path(path))
	{
		printf_s("Unexeptable path.\n");
		return -1;
	}

	// Combine the path and the file name
	if (combine_strs(full_path, path_and_fileName, 3))
	{
		printf_s("Error in combining path and file name.\n");
		return -1;
	}

	return 0;
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

//todo check failure
uint8_t createFile(TCHAR* full_path)
{
	//todo wprintf(L"\n***\n%ls\n", full_path);

	// Open a handle to the file //todo check other params
	HANDLE hFile = CreateFile(
		full_path,				// Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);                  // Template file handle

	// File existing
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	// Close the handle once we don't need it.
	CloseHandle(hFile);

	return 0;
}

bool valid_filename(TCHAR* fileName)
{
	// Check if there is an ".exe" ending
	if (is_substr_at_index(fileName, EXE_ENDING, wcslen(fileName) - wcslen(EXE_ENDING)))
	{
		return false;
	}

	// Check if there is an ":$DATA" ending
	if (is_substr_at_index(fileName, DATA_ENDING, wcslen(fileName) - wcslen(DATA_ENDING)))
	{
		return false;
	}

	return true;
}

bool valid_path(TCHAR* path)
{
	// Check if RESTRICTED_FOLDER_NAME is in the path


	//todo
	if (is_substr_at_index(path, RESTRICTED_FOLDER_NAME, 0))
	{
		return false;
	}

	return true;
}





/* Comments */
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

// Printing
/*
wprintf(L"%ls\n", path);

_setmode(_fileno(stdout), _O_U16TEXT);
wprintf(L"\x263a\x263b\n");
wprintf(L"%ls\n%ls\n", path, fileName);

wprintf(L"%ls\n%ls\n->\n%ls\n", path, fileName, full_path);
*/