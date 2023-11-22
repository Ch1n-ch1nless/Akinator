#include "akinator_output.h"

void ShowIntro()
{
    printf("Hello, dear friend! I am AkinatorGPT. I can read minds!\n"
           "Ok, i will tell you more about my capabilities:\n"
           "\tEnter \'g\' -- I'll guess what you've made up your mind\n"
           "\tEnter \'d\' -- I'll give you a definition of object\n"
           "\tEnter \'c\' -- I'll give you comprasion of 2 objects!\n"
           "\tEnter \'e\' -- I'll delete me data base!\n"
           "\tEnter \'s\' -- I'll save my new data base!\n"
           "\tEnter \'p\' -- I'll draw tree graph!\n"
           "\tEnter \'q\' -- I'll complete the job!\n\n");

    return;
}

void ShowOutro()
{
    printf("Goodbye, my dear friend! See you soon!\n");

    return;
}

void PrintNodeData(size_t* index, Stack* stk, Node* node, size_t len)
{
    PTR_ASSERT(stk)
    PTR_ASSERT(node)
    PTR_ASSERT(index)
    assert((*index > len) && "ERROR! Index is greater then len!!!\n");

    while (*index < len)
    {
        printf("\t" tree_format "\n", node->data);
        ++*index;
        switch(GetStkDataElemT(stk, *index))
        {
            case ADD_LEFT_NODE:
                node = node->left;
                break;

            case ADD_RIGHT_NODE:    
                node = node->right;
                break;

            default:
                break;
        }
    }

    return;
}

void PrintPathToNode(Node* node, Stack* stk, size_t len)
{
    PTR_ASSERT(node)
    PTR_ASSERT(stk)

    for (size_t index = 0; index < len; index++)
    {
        printf("\t" tree_format "\n", node->data);

        switch(GetStkDataElemT(stk, index))
        {
            case ADD_LEFT_NODE:
                node = node->left;
                break;

            case ADD_RIGHT_NODE:
                node = node->right;
                break;

            default:
                break;
        }
    }
}
