#ifndef AKINATOR_INPUT_H_INCLUDED
#define AKINATOR_INPUT_H_INCLUDED

#include "../../CommonFiles/config_errors.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

const char* const DATA_FILE_NAME = "data_base.txt";

const size_t MAX_LEN_OF_WORD = 1 << 10;

error_t OpenFile(const char* const filename, FILE** const file_pointer, const char* const mode);

error_t CloseFile(FILE* const file_pointer);

error_t CountBufferSize(const char* const filename, size_t* const buf_size);

error_t ReadBufferFromFile(char** const buffer, FILE* const file_pointer, const size_t buf_size);

error_t SkipWhiteSpacesTabsAndEnters(char** const buffer);

void    ClearBuffer(void);

char*   ReadWordFromStdInput(error_t* error);

#endif /*AKINATOR_H_INCLUDED*/