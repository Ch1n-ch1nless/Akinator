#ifndef AKINATOR_OUTPUT_H_INCLUDED
#define AKINATOR_OUTPUT_H_INCLUDED

#include "akinator_input.h"

#include "akinator_config.h"

void ShowIntro();

void ShowOutro();

void PrintNodeData(size_t* index, Stack* stk, Node* node, size_t len);

void PrintPathToNode(Node* node, Stack* stk, size_t len);

#endif /*AKINATOR_OUTPUT_H_INCLUDED*/