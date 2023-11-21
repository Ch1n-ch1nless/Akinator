#ifndef TREE_INPUT_H_INCLUDED
#define TREE_INPUT_H_INCLUDED

#include "tree_error.h"

error_t OpenFile(const char* filename, FILE** file_pointer, const char* mode);

error_t CloseFile(FILE* file_pointer);

error_t CountBufferSize(const char* filename, size_t* buf_size);

error_t ReadBufferFromFile(tree_t* buffer, FILE* data_file, const size_t buf_size);

error_t SkipWhiteSpacesTabsAndEnters(tree_t* buffer);

tree_t  ReadWord(tree_t buffer, error_t* error);

#endif // TREE_INPUT_H_INCLUDED
