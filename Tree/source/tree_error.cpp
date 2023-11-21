#include "tree_error.h"

error_t TreeVerify(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    if (tree->root == nullptr)
    {
        error |= ROOT_IS_NULL_ERR;
    }

    if (tree->name == nullptr)
    {
        error |= TREE_NAME_IS_NULL_ERR;
    }

    if (tree->file == nullptr)
    {
        error |= TREE_FILE_IS_NULL_ERR;
    }

    if (tree->line <= 0)
    {
        error |= TREE_LINE_IS_FEWER_ZERO_ERR;
    }

    return error;
}

const char* PrintTreeErrors(error_t error, char* buffer);
{

}

void PrintTreeErrors(Tree* tree, error_t error, const char* file,
                                                const int   line,
                                                const char* function)
{
   assert((tree     != nullptr) && "Pointer to tree is NULL!!!\n");
   assert((file     != nullptr) && "Pointer to tree is NULL!!!\n");
   assert((function != nullptr) && "Pointer to function is NULL!!!\n");
   assert((line      > 0)       && "Line is fewer than 0");

   char*err_array =

   if (error & OPEN_FILE_ERR)
   {
        printf("Error! Program can not open file!!!\n");
   }

   if (error & MEM_ALLOC_ERR)
   {
        printf("Error! Program can not allocate memory!!!\n");
   }

   if (error & CLOSE_FILE_ERR)
   {
        printf("Error! Program can not close file!!!\n");
   }

   if (error & ADD_ARG_ERR)
   {
        printf("Error! Function can not add element to tree!!!\n");
   }

   if (error & ROOT_IS_NULL_ERR)
   {
        printf("Error! Root of tree is NULL!!!\n");
   }

   if (error & TREE_NAME_IS_NULL_ERR)
   {
        printf("Error! Name of tree is NULL!!!\n");
   }

   if (error & TREE_FILE_IS_NULL_ERR)
   {
        printf("Error! File of tree is NULL!!!\n");
   }

   if (error & TREE_LINE_IS_FEWER_ZERO_ERR)
   {
        printf("Error! Line is fewer than zero!!!\n");
   }

   return;
}
