#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include "../../Tree/source/tree.h" // -I ../../Tree/source : #include <tree.h>
#include "../../Tree/source/tree_dump.h"

enum Mods : char
{
    INCORRECT_MODE   = '\0',
    AKINATOR         = 'a',
    DEFINITION       = 'd',
    COMPARISON       = 'c',
    DELETE_DATA_BASE = 'e',
    SAVE_DATA_BASE   = 's',
    DRAW_TREE        = 'p',
    QUIT             = 'q'
};

enum States : char 
{
    AKINATOR = 'a', 
};

enum Answers : char
{
    UNDEFINED_ANSWER = '\0',
    YES              = 'y',
    NO               = 'n'
};

error_t PlayGame(Tree* tree);

void    ShowIntro();

void    ShowOutro();

Mods    GetMode();

error_t GuessObject(Node* node);

Answers GetAnswer();

error_t AddNewObject(Node* node);

tree_t  GetNameOfObject(error_t* error);

tree_t  GetDifference(error_t* error);

error_t GetDefinition(Tree* tree);

error_t GetComparison(Tree* tree);

error_t DeleteDataBase(Tree* tree);

error_t SaveDataBase(Tree* tree);

void    ClearBuffer(void);

bool    SearchObject(tree_t name_of_object, Stack* stk, Node* node);

void    PrintNodeData(size_t* index, Stack* stk, Node* node, size_t len);

void    SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2, Node* node1, Node* node2);

#endif //AKINATOR_H_INCLUDED