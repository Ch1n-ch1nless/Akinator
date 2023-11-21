#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "tree_input.h"
#include "tree_error.h"
#include "../../Stack/source/stack.h"

#define TREE_CTOR(tree) TreeCtor(tree, #tree, __FILE__, __LINE__);

const size_t ADD_LEFT_NODE  =  1;
const size_t ADD_RIGHT_NODE = -1;

error_t  TreeCtor(Tree* tree, const char* name, const char* file, const int line);
Node*    NodeCtor(error_t* error, tree_t string);
error_t  DataBaseCtor(Tree* tree);

error_t  TreeDtor(Tree* tree);
error_t  SubTreeDtor(Node** node);

error_t TreeInsert(Tree* tree, tree_t element, Node* new_node, size_t indicator);

error_t FillTreeFromBuffer(Tree* tree);

#endif // TREE_H_INCLUDED
