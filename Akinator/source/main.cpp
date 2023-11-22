#include "akinator.h"
#include "game_functions.h"

int main()
{
    error_t error = NO_ERR;

    Akinator akinator = {};

    error = AKINATOR_CTOR(&akinator)

    error |= FillTreeFromBuffer(&akinator);

    error |= PlayGame(&akinator);

    TreeGraphDump(&(akinator.tree));

    error = AkinatorDtor(&akinator);

    return error;
}
