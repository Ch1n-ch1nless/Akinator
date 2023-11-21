#include "tree.h"

Node* NodeCtor(error_t* error, tree_t string)
{
    Node* new_node = nullptr;

    new_node = (Node*) calloc(1, sizeof(Node));
    if (new_node == nullptr)
    {
        *error = *error | MEM_ALLOC_ERR;
        return new_node;
    }

    new_node->data = string;

    if (strlen(string) > MAX_LEN_OF_WORD)
    {   
        *error = *error | LEN_OF_WORD_IS_BIGGER_MAX_SIZE_ERR;
        return new_node;
    }

    new_node->left  = nullptr;

    new_node->right = nullptr;

    return new_node;
}

error_t DataBaseCtor(Tree* tree)
{
    assert((tree != nullptr) && "Error! Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    FILE* data_file = nullptr;

    error = OpenFile(DATA_FILE_NAME, &data_file, "rb");

    error |= CountBufferSize(DATA_FILE_NAME, &(tree->buf_size));

    error |= ReadBufferFromFile(&(tree->buffer), data_file, tree->buf_size);

    return error;
}

error_t TreeCtor(Tree* tree, const char* name, const char* file, const int line)
{
    error_t error = NO_ERR;

    tree->root = nullptr;

    tree->size = 0;

    tree->name = name;

    tree->line = line;

    tree->file = file;

    tree->buffer = nullptr;

    tree->buf_size = 0;

    error = DataBaseCtor(tree);

    return error;
}

error_t SubTreeDtor(Node** node)
{
    error_t error = NO_ERR;

    if ((*node)->left != nullptr)
    {
        error |= SubTreeDtor(&((*node)->left));
    }

    if ((*node)->right != nullptr)
    {
        error |= SubTreeDtor(&((*node)->right));
    }

    free((*node)->data);

    free(*node);

    *node = nullptr;

    return error;
}

error_t TreeDtor(Tree* tree)
{
    error_t error = NO_ERR;

    error |= SubTreeDtor(&(tree->root));

    tree->size = 0;

    tree->name = nullptr;

    tree->file = nullptr;

    tree->line = -1;

    tree->buf_size = -1;

    free(tree->buffer);

    tree->buffer = nullptr;

    return error;
}

error_t TreeInsert(Tree* tree, tree_t string, Node* cur_node, size_t indicator)
{
    error_t error = NO_ERR;

    Node* new_node  = nullptr;

    new_node = NodeCtor(&error, string);

    if (cur_node == nullptr)
    {
        tree->root = new_node;
    }
    else
    {
        if (indicator == ADD_LEFT_NODE)
        {
            cur_node->left = new_node;
        }
        else if (indicator == ADD_RIGHT_NODE)
        {
            cur_node->right = new_node;
        }
        else
        {
            error = UNKNOWN_INDICATOR_ERR;
        }
    }

    CHECK_TREE_ERROR(tree, error);

    return error;
}

error_t FillTreeFromBuffer(Tree* tree)
{
    assert((tree != nullptr) && "Error! Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    Node** node = &(tree->root);

    char* cur_symbol = tree->buffer;

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

    while ((size_t)(cur_symbol - tree->buffer) < tree->buf_size)
    {
        SkipWhiteSpacesTabsAndEnters(&cur_symbol);

        switch(*cur_symbol)
        {
            case ('('):
            {
                error |= StackPush(&stk, node);

                if ((*node)->left == nullptr)
                {
                    node = &((*node)->left);
                }
                else
                {
                    if ((*node)->right == nullptr)
                    {
                        node = &((*node)->right);
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
                    if ((size_t)(cur_symbol - tree->buffer) != tree->buf_size - 1)
                    {
                        error |= WRONG_BUFFER_SYNTAX_ERR;
                        return error;
                    }
                }

                error |= StackPop(&stk, &node);

                ++cur_symbol;
                break;
            }

            case('\"'):
            {
                ++cur_symbol;
                char* word = ReadWord(cur_symbol, &error);
                *node = NodeCtor(&error, word);
                cur_symbol = strchr(cur_symbol, '\"');
                ++cur_symbol;
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