#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

#include "akinator.h"
#include "akinator_input.h"
#include "akinator_output.h"
#include "../../Tree/source/tree_dump.h"

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

error_t PlayGame(Akinator* akinator);

Mods    GetMode();

error_t GuessObject(Node* node);

Answers GetAnswer();

error_t AddNewObject(Node* node);

error_t GetDefinition(Tree* tree);

error_t GetComparison(Tree* tree);

error_t DeleteDataBase(Tree* tree);

error_t SaveDataBase(Tree* tree);

Stack*  StackDefinition(Node* node, error_t* error, char** name_of_object);

bool    SearchObject(char* name_of_object, Node* node, Stack* stk, error_t* error);

void    SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2);

#endif /*GAME_FUNCTIONS_H_INCLUDED*/