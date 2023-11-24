#include "akinator_output.h"

void ShowIntro()
{
    printf("Hello, dear friend! I am AkinatorGPT. I can read minds!\n"
           "Ok, i will tell you more about my capabilities:\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll guess what you've made up your mind\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll give you a definition of object\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll give you comprasion of 2 objects!\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll delete me data base!\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll save my new data base!\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll draw tree graph!\n"
           "\tEnter \'" LYELLOW("%c") "\' -- I'll complete the job!\n\n",
           MODE_GUESSING, MODE_DEFINITION, MODE_COMPARISON, MODE_DELETE_DATA_BASE,
           MODE_SAVE_DATA_BASE, MODE_DRAW_TREE, MODE_QUIT);

    return;
}

void ShowOutro()
{
    printf("Goodbye, my dear friend! See you soon!\n");

    return;
}

void PrintNodesData(size_t* index, Stack* stk, Node* node, size_t len)
{
    PTR_ASSERT(stk)
    PTR_ASSERT(node)
    PTR_ASSERT(index)
    assert((*index <= len) && "ERROR! Index is greater then len!!!\n");

    while (*index < len)
    {
        PrintNodeData(*index, stk, &node);

        ++*index;
    }

    return;
}

void PrintNodeData(size_t index, Stack* stk, Node** node)
{
    PTR_ASSERT(node)
    PTR_ASSERT(stk)

    stk_elem_t  indicator = GetStkDataElemT(stk, index);

    const char* line = nullptr;

    switch(indicator)
    {
        case ADD_LEFT_NODE:
            line = "";
            break;

        case ADD_RIGHT_NODE:
            line = "not ";
            break;

        default:
            break;
    }

    printf("\t %s" tree_format "\n", line, (*node)->data);

    switch(indicator)
    {
        case ADD_LEFT_NODE:
            *node = (*node)->left;
            break;

        case ADD_RIGHT_NODE:
            *node = (*node)->right;
            break;

        default:
            break;
    }
}
