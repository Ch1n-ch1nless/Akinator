#ifndef AKINATOR_CONFIG_H_INCLUDED
#define AKINATOR_CONFIG_H_INCLUDED

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../CommonFiles/config_errors.h"
#include "../../Tree/source/tree.h"
#include "../../Stack/source/stack.h"

enum Mods : char
{
    MODE_INCORRECT        = '\0',
    MODE_GUESSING         = 'g',
    MODE_DEFINITION       = 'd',
    MODE_COMPARISON       = 'c',
    MODE_DELETE_DATA_BASE = 'e',
    MODE_SAVE_DATA_BASE   = 's',
    MODE_DRAW_TREE        = 'p',
    MODE_QUIT             = 'q'
};

enum Answers : char
{
    ANSWER_UNDEFINED    = '\0',
    ANSWER_YES          = 'y',
    ANSWER_NO           = 'n'
};

struct Akinator
{
    Tree        tree      = {};
    char*       buffer    = nullptr;
    size_t      buf_size  = 0;
    const char* name      = nullptr;
    const char* file      = nullptr;
    int         line      = 0;
};

#endif /*AKINATOR_CONFIG_H_INCLUDED*/
