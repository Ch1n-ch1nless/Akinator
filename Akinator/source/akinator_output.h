#ifndef AKINATOR_OUTPUT_H_INCLUDED
#define AKINATOR_OUTPUT_H_INCLUDED

#include "akinator_input.h"

#include "akinator_config.h"

void ShowIntro();

void ShowOutro();

void PrintNodesData(size_t* index, Stack* stk, Node* node, size_t len);

void PrintNodeData(size_t index, Stack* stk, Node** node);

#endif /*AKINATOR_OUTPUT_H_INCLUDED*/