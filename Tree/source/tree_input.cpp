#include "tree_input.h"

error_t OpenFile(const char* filename, FILE** file_pointer, const char* mode)
{
    assert((filename     != nullptr) && "Error! Pointer to filename is NULL!!!\n");
    assert((file_pointer != nullptr) && "Error! Pointer to file_pointer is NULL!!!\n");
    assert((mode         != nullptr) && "Error! Pointer to mode is NULL!!!\n");

    error_t error = NO_ERR;

    *file_pointer = fopen(filename, mode);

    if (*file_pointer == nullptr)
    {
        return error | OPEN_FILE_ERR;
    }

    return error;
}

error_t CloseFile(FILE* file_pointer)
{
    assert((file_pointer != nullptr) && "Error! Pointer to file_pointer is NULL!!!\n");

    error_t error = NO_ERR;

    if (fclose(file_pointer) != 0)
    {
        return error | CLOSE_FILE_ERR;
    }

    return error;
}

error_t CountBufferSize(const char* filename, size_t* buf_size)
{
    assert((filename != nullptr) && "Error! Pointer to filename is NULL!!!\n");
    assert((buf_size != nullptr) && "Error! Pointer to buf_size is NULL!!!\n");

    error_t error = NO_ERR;

    struct stat st = {};

    stat(filename, &st);

    (*buf_size) = st.st_size;

    return error;
}

error_t ReadBufferFromFile(tree_t* buffer, FILE* data_file, const size_t buf_size)
{
    assert((data_file != nullptr) && "Error! Pointer to data_file is NULL!!!\n");

    error_t error = NO_ERR;

    *buffer = (tree_t) calloc(buf_size + 1, sizeof(char));

    if (*buffer == nullptr)
    {
        error = MEM_ALLOC_ERR;
        return error;
    }

    size_t number_of_symbols = fread(*buffer, sizeof(char), buf_size, data_file);
    if (number_of_symbols != buf_size) {
        #if 1
        if (feof(data_file)) {
            printf("Error reading %s: unexpected end of file\n", "<STRING>");
        } else if (ferror(data_file)) {
            printf("Error reading %s", "<STRING>");
        }
        #endif
        if (number_of_symbols > buf_size) {
            printf("ERROR! Symbols in file  more then buf_size!");
            assert(false);
        }
    }

    return error;
}

error_t SkipWhiteSpacesTabsAndEnters(tree_t* buffer)
{
    assert((buffer  != nullptr)  && "Error! Pointer to buffer is NULL!!!");
    assert((*buffer != nullptr)  && "Error! Pointer to string is NULL!!!");

    error_t error = NO_ERR;

    size_t count_of_extra_char = 0;                 //Count of extra spaces, tabs before command
    char temp_array[MAX_LEN_OF_WORD] = {};          //Temporary array of symbols

    if (sscanf(*buffer, "%[ \t\n\r]%n", temp_array, &count_of_extra_char) != 1)
    {
        error |= INPUT_ERR;
        return error;
    }
    
    *buffer = *buffer + count_of_extra_char;

    return error;
}

tree_t ReadWord(tree_t buffer, error_t* error)
{
    assert((buffer  != nullptr)  && "Error! Pointer to buffer is NULL!!!\n");
    assert((error   != nullptr)  && "Error! Pointer to error  is NULL!!!\n");

    tree_t word = (tree_t) calloc(MAX_LEN_OF_WORD, sizeof(char));
    if (word == nullptr)
    {
        *error |= MEM_ALLOC_ERR;
        return nullptr;
    }

    bool is_find_double_quotes = false;

    for (size_t i = 0; i < MAX_LEN_OF_WORD; i++)
    {
        if (buffer[i] != '\"')
        {
            word[i] = buffer[i];
        }
        else
        {
            word[i] = '\0';
            is_find_double_quotes = true;
            break;
        }
    }

    if (is_find_double_quotes == false)
    {
        *error |= LEN_OF_WORD_IS_BIGGER_MAX_SIZE_ERR;
    }

    return word;
}
