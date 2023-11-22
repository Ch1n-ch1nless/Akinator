#include "akinator_input.h"

error_t OpenFile(const char* const filename, FILE** const file_pointer, const char* const mode)
{
    PTR_ASSERT(filename)
    PTR_ASSERT(file_pointer)
    PTR_ASSERT(mode)

    *file_pointer = fopen(filename, mode);

    if (file_pointer == nullptr)
    {
        return OPEN_FILE_ERR;
    }

    return NO_ERR;
}

error_t CloseFile(FILE* const file_pointer)
{
    PTR_ASSERT(file_pointer)

    if (fclose(file_pointer) != 0)
    {
        return CLOSE_FILE_ERR;
    }

    return NO_ERR;
}

error_t CountBufferSize(const char* const filename, size_t* const buf_size)
{
    PTR_ASSERT(filename)
    PTR_ASSERT(buf_size)

    struct stat st = {};

    stat(filename, &st);
    
    if (st.st_size == 0)
    {
        return EMPTY_FILE_ERR;
    }

    *buf_size = st.st_size;

    return NO_ERR;
}

error_t ReadBufferFromFile(char** const buffer, FILE*  const file_pointer, const size_t buf_size)
{
    PTR_ASSERT(buffer)
    PTR_ASSERT(file_pointer)
    
    *buffer = (char*) calloc(buf_size + 1, sizeof(char));

    if (*buffer == nullptr)
    {
        return MEM_ALLOC_ERR;
    }

    size_t number_of_symbols = fread(*buffer, sizeof(char), buf_size, file_pointer);

    if (number_of_symbols != buf_size) {
        #if 1
        if (feof(file_pointer)) {
            printf("Error reading %s: unexpected end of file\n", "<STRING>");
            return FREAD_ERR;
        } else if (ferror(file_pointer)) {
            printf("Error reading %s", "<STRING>");
            return FREAD_ERR;
        }
        #endif
        if (number_of_symbols > buf_size) {
            printf("Error! Symbols in file  more then buf_size!");
            assert(false);
        }
    }

    return NO_ERR;
}

error_t SkipWhiteSpacesTabsAndEnters(char** const buffer)
{
    PTR_ASSERT( buffer)
    PTR_ASSERT(*buffer)

    size_t count_of_extra_char = 0;                 //Count of extra spaces, tabs before command
    char temp_array[MAX_LEN_OF_WORD] = {};          //Temporary array of symbols

    if (sscanf(*buffer, "%[ \t\n\r]%n", temp_array, &count_of_extra_char) != 1)
    {
        return INPUT_ERR;
    }
    
    *buffer = *buffer + count_of_extra_char;

    return NO_ERR;
}

void ClearBuffer(void)
{
    int c = EOF;
    do
    {
        c = getchar();
    } 
    while (c != EOF && c != '\n');
}

char* ReadWordFromStdInput(error_t* error)
{
    PTR_ASSERT(error)

    char* word = (char*) calloc(MAX_LEN_OF_WORD, sizeof(char));

    if (word == nullptr)
    {
        *error |= MEM_ALLOC_ERR;
        return nullptr;
    }

    if (fgets(word, MAX_LEN_OF_WORD, stdin) == nullptr)
    {
        *error |= INPUT_ERR;
        return nullptr;
    } 

    return word;
}