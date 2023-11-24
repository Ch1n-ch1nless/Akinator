#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

#include "akinator.h"
#include "akinator_input.h"
#include "akinator_output.h"
#include "../../Tree/source/tree_dump.h"

error_t PlayGame(Akinator* akinator);

Mods    GetMode();

error_t GuessObject(Tree* tree);

Answers GetAnswer();

error_t AddNewObject(Node* node);

error_t GetDefinition(Tree* tree);

error_t GetComparison(Tree* tree);

error_t DeleteDataBase(Tree* tree);

error_t SaveDataBase(Tree* tree);

error_t StackDefinition(Node* node, Stack* stk, char** name_of_object);

bool    SearchObject(char* name_of_object, Node* node, Stack* stk, error_t* error);

void    SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2);

#endif /*GAME_FUNCTIONS_H_INCLUDED*/