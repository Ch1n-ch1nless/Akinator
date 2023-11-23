#include "akinator.h"

error_t AkinatorCtor(Akinator* const akinator, const char* const name, const char* const file, const int line)
{
    PTR_ASSERT(akinator)
    PTR_ASSERT(name)
    PTR_ASSERT(file)
    assert((line > 0) && "ERROR! Line is not greater then zero!!!\n");

    error_t error = NO_ERR;

    error |= TREE_CTOR(&(akinator->tree));

    error |= FillBuffer(&(akinator->buffer), &(akinator->buf_size));

    error |= FillTreeFromBuffer(akinator);

    akinator->name = name;

    akinator->file = file,

    akinator->line = line;

    return error;
}

error_t FillBuffer(char** const buffer, size_t* const buf_size)
{
    PTR_ASSERT(buffer)
    PTR_ASSERT(buf_size)

    error_t error = NO_ERR;

    FILE* file_pointer = nullptr;

    error = OpenFile(DATA_FILE_NAME, &file_pointer, "rb");

    error = CountBufferSize(DATA_FILE_NAME, buf_size);

    error = ReadBufferFromFile(buffer, file_pointer, *buf_size);

    error = CloseFile(file_pointer);

    return error;
}

error_t AkinatorDtor(Akinator* akinator)
{
    PTR_ASSERT(akinator)

    error_t error = NO_ERR;

    error = TreeDtor(&(akinator->tree));

    error = DeleteBuffer(&(akinator->buffer), &(akinator->buf_size));

    akinator->name  = nullptr;

    akinator->file  = nullptr;

    akinator->line  = -1;

    return error;
}

error_t DeleteBuffer(char** buffer, size_t* const buf_size)
{
    PTR_ASSERT(buffer)
    PTR_ASSERT(buf_size)

    error_t error = NO_ERR;

    free(*buffer);

    *buffer = nullptr;

    buffer = nullptr;

    *buf_size = 0;

    return error;
}

error_t FillTreeFromBuffer(Akinator* akinator)
{
    PTR_ASSERT(akinator)
    PTR_ASSERT(akinator->buffer)

    error_t error = NO_ERR;

    Node* node = (akinator->tree).root;

    char* cur_symbol = akinator->buffer;

    Stack stk = {};

    error |= STACK_CTOR(&stk);

    if (*cur_symbol != '(')
    {
        error |= WRONG_BUFFER_SYNTAX_ERR;
        return error;
    }
    else
    {
        cur_symbol++;
    }

    while ((size_t)(cur_symbol - akinator->buffer) < akinator->buf_size)
    {
        SkipWhiteSpacesTabsAndEnters(&cur_symbol);

        switch(*cur_symbol)
        {
            case ('('):
            {
                if (node->left == nullptr)
                {
                    error |= StackPush(&stk, ADD_LEFT_NODE);
                    node->left = NodeCtor(&error, nullptr);
                }
                else
                {
                    if (node->right == nullptr)
                    {
                        error |= StackPush(&stk, ADD_RIGHT_NODE);
                        node->right = NodeCtor(&error, nullptr);
                    }
                    else
                    {
                        error |= WRONG_BUFFER_SYNTAX_ERR;
                        return error;
                    }
                }
                ++cur_symbol;
                break;
            }

            case(')'):
            {
                if (stk.size == 0)
                {
                    if ((size_t)(cur_symbol - akinator->buffer) != akinator->buf_size - 1)
                    {
                        error |= WRONG_BUFFER_SYNTAX_ERR;
                        return error;
                    }
                }

                stk_elem_t ret_value = STK_POISON_VALUE;
                error |= StackPop(&stk, &ret_value);

                node = GetNodeFromStack(&stk, &(akinator->tree), &error);

                ++cur_symbol;
                break;
            }

            case('\"'):
            {
                node = GetNodeFromStack(&stk, &(akinator->tree), &error);

                cur_symbol++;
                char* word = ReadWordFromBuffer(cur_symbol, &error);
                node->data = word;
                cur_symbol = strchr(cur_symbol, '\"');
                if (cur_symbol == nullptr)
                {
                    return error | WRONG_BUFFER_SYNTAX_ERR;
                }
                cur_symbol++;
                break;
            }

            default:
            {
                error |= WRONG_BUFFER_SYNTAX_ERR;
                return error;
            }
        }
    }

    error |= StackDtor(&stk);

    return error;
}

char* ReadWordFromBuffer(char* string, error_t* error)
{
    PTR_ASSERT(string)
    PTR_ASSERT(error)

    char* word = (char*) calloc(MAX_LEN_OF_WORD, sizeof(char));
    if (word == nullptr)
    {
        *error |= MEM_ALLOC_ERR;
        return nullptr;
    }

    bool is_find_double_quotes = false;

    for (size_t i = 0; i < MAX_LEN_OF_WORD; i++)
    {
        if (string[i] != '\"')
        {
            word[i] = string[i];
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

Node* GetNodeFromStack(Stack* stk, Tree* tree, error_t* error)
{
    PTR_ASSERT(stk)
    PTR_ASSERT(tree)
    PTR_ASSERT(error)

    Node* node = tree->root;

    for (size_t i = 0; i < (size_t) stk->size; i++)
    {
        switch(GetStkDataElemT(stk, i))
        {
            case ADD_LEFT_NODE:
                node = node->left;
                break;

            case ADD_RIGHT_NODE:
                node = node->right;
                break;

            default:
                *error |= UNKNOWN_INDICATOR_ERR;
                return nullptr;
        }
    }

    return node;
}

error_t AkinatorVerify(Akinator* const akinator)
{
    PTR_ASSERT(akinator)

    error_t error = NO_ERR;

    error = TreeVerify(&(akinator->tree));

    if (akinator->buffer == nullptr)
    {
        error |= BUFFER_IS_NULL_ERR;
    }

    if (akinator->name == nullptr)
    {
        error |= NULL_NAME_ERR;
    }

    if (akinator->file == nullptr)
    {
        error |= NULL_FILE_ERR;
    }

    if (akinator->line <= 0)
    {
        error |= MINUS_LINE_ERR;
    }

    return error;
}

void PrintAkinatorError(error_t error)
{
    if (error & BUFFER_IS_NULL_ERR)
    {
        printf("Error! Buffer is NULL!\n");
    }

    if (error & NULL_NAME_ERR)
    {
        printf("Error! Name is NULL!\n");
    }

    if (error & NULL_FILE_ERR)
    {
        printf("Error! File is NULL!\n");
    }

    if (error & MINUS_LINE_ERR)
    {
        printf("Error! Line is fewer then 0!\n");
    }

    if (error & LEN_OF_WORD_IS_BIGGER_MAX_SIZE_ERR)
    {
        printf("Error! Size of word is bigger then maximal len of word!\n");
    }

    if (error & UNKNOWN_INDICATOR_ERR)
    {
        printf("Error! User writes wrong indicator!\n");
    }

    if (error & WRONG_BUFFER_SYNTAX_ERR)
    {
        printf("Error! Program can not correct read the buffer\n");
    }

    if (error & INPUT_ERR)
    {
        printf("Error! User writes wrong expression!\n");
    }

    if (error & EMPTY_FILE_ERR)
    {
        printf("Error! File is empty!\n");
    }

    if (error & FREAD_ERR)
    {
        printf("Error! Error in function 'fread'!!\n");
    }
}