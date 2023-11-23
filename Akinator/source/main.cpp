#include "akinator.h"
#include "game_functions.h"

int main()
{
    error_t error = NO_ERR;

    Akinator akinator = {};

    error = AKINATOR_CTOR(&akinator)
    CHECK_ERRORS(error)

    error |= PlayGame(&akinator);
    CHECK_ERRORS(error)

    error = AkinatorDtor(&akinator);

    return error;
}
