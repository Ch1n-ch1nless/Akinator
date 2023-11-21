#include "akinator.h"

int main()
{
    error_t error = NO_ERR;

    Tree tree = {};

    TREE_CTOR(&tree)

    error |= FillTreeFromBuffer(&tree);

    error |= PlayGame(&tree);

    TreeDtor(&tree);

    return error;
}
