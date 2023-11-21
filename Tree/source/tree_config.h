#ifndef TREE_CONFIG_H_INCLUDED
#define TREE_CONFIG_H_INCLUDED

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef char* tree_elem_t;

#define tree_format "%s"

const tree_t TREE_POISON_VALUE = nullptr;

struct Node
{
    tree_t data  = TREE_POISON_VALUE;
    Node*  left  = nullptr;
    Node*  right = nullptr;
};

struct Tree
{
    Node*       root     = nullptr;
    size_t      size     = 0;
    tree_t      buffer   = nullptr;
    size_t      buf_size = 0;
    const char* name     = nullptr;
    const char* file     = nullptr;
    int         line     = 0;
};

const char* const DATA_FILE_NAME = "data_base.txt";

const size_t MAX_LEN_OF_WORD = 1 << 10;

#endif // TREE_CONFIG_H_INCLUDED
