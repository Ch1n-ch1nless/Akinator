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
