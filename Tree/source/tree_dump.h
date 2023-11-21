#ifndef TREE_DUMP_H_INCLUDED
#define TREE_DUMP_H_INCLUDED

#include "tree.h"

#define TREE_TXT_DUMP(tree, output, mode) \
        TreeTextDump(tree, output, __FILE__, __LINE__, __FUNCTION__, mode);

const char* const DOT_FILE      = "tree.dot";

const char* const PICTURE_FILE  = "tree.png";

const char* const TXT_DUMP_FILE = "tree.dmp";

const char* const PRE_ORDER     = "pre_order";
const char* const POST_ORDER    = "post_order";
const char* const IN_ORDER      = "in_order";

void TreeTextDump(Tree* tree, FILE* output, const char* file, const int   line,
                                            const char* func, const char* mode );

void PrintInPreOrder(Node* node, FILE* output);

void PrintInPostOrder(Node* node, FILE* output);

void PrintInInOrder(Node* node, FILE* output);

void TreeGraphDump(Tree* tree);

void NodeGraphDump(Node* node, FILE* dot_file);

void EdgeGraphDump(Node* node, FILE* dot_file);

#endif // TREE_DUMP_H_INCLUDED
