#include "game_functions.h"

error_t PlayGame(Akinator* akinator)
{
    PTR_ASSERT(akinator);

    error_t error = NO_ERR;

    while (true)
    {
        ShowIntro();

        Mods mode = GetMode();

        switch (mode)
        {
            case MODE_GUESSING:
                error |= GuessObject(akinator->tree.root); 
                break;

            case MODE_DEFINITION:
                error |= GetDefinition(&(akinator->tree)); //TODO fix function
                break;

            case MODE_COMPARISON:
                error |= GetComparison(&(akinator->tree)); //TODO fix function
                break;

            case MODE_DELETE_DATA_BASE:
                error |= DeleteDataBase(&(akinator->tree));
                break;

            case MODE_SAVE_DATA_BASE:
                error |= SaveDataBase(&(akinator->tree));
                break;

            case MODE_DRAW_TREE:
                TreeGraphDump(&(akinator->tree)); 
                break;

            case MODE_QUIT:
                ShowOutro();
                return error;
                break;

            case MODE_INCORRECT:
                printf("You enter wrong mode try again!\n");
                break;
            
            default:
                break;
        }

        printf("Do you want to continue game?\n");

        Answers ans = GetAnswer();
        switch(ans)
        {
            case ANSWER_YES:
                break;

            case ANSWER_NO:
                ShowOutro();
                return error;

            case ANSWER_UNDEFINED:
            default:
                fprintf(stderr, "Error! Unknown answer");
                return error | INPUT_ERR;
        }

    }

    return error;
}

Mods GetMode()
{
    char mode = MODE_INCORRECT;
    scanf(" %c", &mode);

    ClearBuffer();
    
    return (Mods) mode;
}

error_t GuessObject(Node* node)
{
    assert((node != nullptr) && "Pointer to node is NULL!!!\n");

    error_t error = NO_ERR;

    while (true)
    {
        printf(tree_format "?\n", node->data);

        Answers answer = ANSWER_UNDEFINED;

        while ((answer = GetAnswer()) == ANSWER_UNDEFINED)
        {
            printf("Akinator can not understand your command, please, try again!\n\n");
            printf(tree_format "?\n", node->data);
        }

        switch(answer)
        {
            case ANSWER_YES:
            {
                if (node->left == nullptr)
                {
                    printf("I am right, however!\n");
                    return error;
                }
                else
                {
                    node = node->left;
                }
                break;
            }

            case ANSWER_NO:
            {
                if (node->right == nullptr)
                {
                    printf("Ok, i was wrong, who or what did you wish?\n");
                    error |= AddNewObject(node);
                    return error;
                }
                else
                {
                    node = node->right;
                }
                break;
            }

            case ANSWER_UNDEFINED:
                break;

            default:
                break;
        }
    }

    return error;
}

Answers GetAnswer()
{
    printf("Enter \'y\' -- if your answer is yes\n"
           "Enter \'n\' -- if your answer is no\n" );

    char ans = '\0';
    scanf("%c", &ans);

    ClearBuffer();
    
    return (Answers) ans;
}

error_t AddNewObject(Node* node)
{
    assert((node != nullptr) && "Pointer to node is NULL!!!\n");

    error_t error = NO_ERR;

    // check all errors
    printf("Enter the name of your object.\n");
    char* new_object = ReadWordFromStdInput(&error);

    printf("How do they differ from?\n");
    char* difference = ReadWordFromStdInput(&error);

    Node* right_node = NodeCtor(&error, node->data);
    Node* left_node  = NodeCtor(&error, new_object);

    node->data  = difference;
    node->left  = left_node;
    node->right = right_node;

    return error;
}

error_t GetDefinition(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    printf("Enter the name of your object.\n");
    char* name_of_object = nullptr;
    Stack* stk = StackDefinition(tree->root, &error, &name_of_object);

    if (stk->size == 0)
    {
        printf("Sorry, object \'%s\' isn't in data base!\n", name_of_object);
    }
    else
    {
        printf("Definition of %s:\n", name_of_object);

        size_t index = 0;
        PrintNodesData(&index, stk, tree->root, stk->size);
    }

    free(stk);
    free(name_of_object);

    return error;
}

error_t GetComparison(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    printf("Enter name of first object:\n");
    char* name1 = nullptr;
    Stack* stk1 = StackDefinition(tree->root, &error, &name1);

    printf("Enter name of second object:\n");
    char* name2 = nullptr;
    Stack* stk2 = StackDefinition(tree->root, &error, &name2);

    size_t index1 = 0;
    size_t index2 = 0;

    Node* node1 = tree->root;
    Node* node2 = tree->root;

    printf("Common features of objects:\n");
    SearchFirstDifference(&index1, stk1, stk2);
    PrintNodesData(&index2, stk1, tree->root, index1);

    printf("\nDifferent features of " tree_format "\n", name1);
    PrintNodesData(&index1, stk1, node1, stk1->size);

    printf("\nDifferent features of " tree_format "\n", name2);
    PrintNodesData(&index2, stk2, node2, stk2->size);

    free(name1);
    free(name2);
    free(stk1);
    free(stk2);

    return error;
}

error_t DeleteDataBase(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    TreeDtor(tree);

    FILE* data_file = nullptr;

    error = OpenFile(DATA_FILE_NAME, &data_file, "w");
    if (error != NO_ERR)
    {
        return error;
    }

    error |= CloseFile(data_file);

    return error;
}

error_t SaveDataBase(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    FILE* data_file = nullptr;

    error = OpenFile(DATA_FILE_NAME, &data_file, "w");
    if (error != NO_ERR)
    {
        return error;
    }

    PrintInPreOrder(tree->root, data_file);

    return error;
}

Stack* StackDefinition(Node* node, error_t* error, char** name_of_object)
{
    PTR_ASSERT(node)
    PTR_ASSERT(error)
    PTR_ASSERT(name_of_object)

    *name_of_object = ReadWordFromStdInput(error);

    Stack* stk = (Stack*) calloc(1, sizeof(Stack));
    if (stk == nullptr)
    {
        *error |= MEM_ALLOC_ERR;
        return nullptr;
    }

    *error = STACK_CTOR(stk);

    if (SearchObject(*name_of_object, node, stk, error) == false)
    {
        *error |= OBJECT_IS_NOT_IN_DATA_BASE_ERR;
        return nullptr;
    }

    return stk;
}

bool SearchObject(char* name_of_object, Node* node, Stack* stk, error_t* error)
{
    PTR_ASSERT(node)
    PTR_ASSERT(error)
    PTR_ASSERT(stk)
    PTR_ASSERT(name_of_object)

    if (*error != NO_ERR)
    {
        return false;
    }

    stk_elem_t temp_element = STK_POISON_VALUE;
    
    if (node->left == nullptr && node->right == nullptr)
    {
        if (strncmp(node->data, name_of_object, strlen(node->data)) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    StackPush(stk, ADD_LEFT_NODE);

    if ((node->left != nullptr) && SearchObject(name_of_object, node->left, stk, error))
    {
        return true;
    }

    StackPop(stk, &temp_element);
    StackPush(stk, ADD_RIGHT_NODE);

    if ((node->right != nullptr) && SearchObject(name_of_object, node->right, stk, error))
    {
        return true;
    }

    StackPop(stk, &temp_element);

    return false;
}

void SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2)
{
    PTR_ASSERT(index)
    PTR_ASSERT(stk1)
    PTR_ASSERT(stk2)

    while ( *index < (size_t)(stk1->size)   && 
            *index < (size_t)(stk2->size)     )
    {
        if (GetStkDataElemT(stk1, *index) == GetStkDataElemT(stk2, *index))
        {
            *index += 1;
        }
        else
        {
            return;
        }
    }

    return;
}