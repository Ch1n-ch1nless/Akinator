#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include "akinator_config.h"
#include "akinator_input.h"

#define AKINATOR_CTOR(akinator) AkinatorCtor(akinator, #akinator, __FILE__, __LINE__);

error_t AkinatorCtor(Akinator* akinator, const char* name, const char* file, const int line);

error_t DataBaseCtor(char** const buffer, size_t* const buf_size);

error_t AkinatorDtor(Akinator* akinator);

error_t DataBaseDtor(char** buffer, size_t* const buf_size);

error_t FillTreeFromBuffer(Akinator* akinator);

char*   ReadWordFromBuffer(char* string, error_t* error);

Node*   GetNodeFromStack(Stack* stk, Tree* tree, error_t* error);

#endif //AKINATOR_H_INCLUDED
