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
                TreeGraphDump(&(akinator->tree)); //include dump
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
    char* name_of_object = ReadWordFromStdInput(&error);

    Stack* stk = SearchObject(name_of_object, tree->root, &error);

    if (stk->size == 0)
    {
        printf("Sorry, object \'%s\' isn't in data base!\n", name_of_object);
    }
    else
    {
        printf("Definition of %s:\n", name_of_object);

        PrintPathToNode(tree->root, stk, stk->size - 1);
    }

    return error;
}

error_t GetComparison(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    printf("Enter name of first object:\n");
    char* name1 = ReadWordFromStdInput(&error);
    Stack* stk1 = SearchObject(name1, tree->root, &error);

    printf("Enter name of first object:\n");
    char* name2 = ReadWordFromStdInput(&error);
    Stack* stk2 = SearchObject(name2, tree->root, &error);

    size_t index1 = 0;
    size_t index2 = 0;

    Node* node1 = tree->root;
    Node* node2 = tree->root;

    printf("Common features of objects:\n");
    SearchFirstDifference(&index1, stk1, stk2, node1, node2);
    PrintNodeData(&index2, stk1, node1, index1);

    printf("\nDifferent features of " tree_format "\n", name1);
    PrintNodeData(&index1, stk1, node1, stk1->size - 1);

    printf("\nDifferent features of " tree_format "\n", name2);
    PrintNodeData(&index2, stk2, node2, stk2->size - 1);

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

Stack* SearchObject(char* name_of_object, Node* node, error_t* error)
{
    Stack* stk = (Stack*) calloc(1, sizeof(Stack));
    if (stk == nullptr)
    {
        *error |= MEM_ALLOC_ERR;
        return nullptr;
    }

    *error |= STACK_CTOR(stk);
    if (*error != NO_ERR)
    {
        return nullptr;
    }

    stk_elem_t temp_element = STK_POISON_VALUE;
    
    if (strcmp(name_of_object, node->data) == 0)
    {
        return stk;
    }

    StackPush(stk, ADD_LEFT_NODE);

    if ((node->left != nullptr) && (SearchObject(name_of_object, node->left, error) != nullptr))
    {
        return stk;
    }

    StackPop(stk, &temp_element);
    StackPush(stk, ADD_RIGHT_NODE);

    if ((node->right != nullptr) && (SearchObject(name_of_object, node->right, error) != nullptr))
    {
        return stk;
    }

    StackPop(stk, &temp_element);

    return nullptr;
}

void SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2, Node* node1, Node* node2)
{
    PTR_ASSERT(index)
    PTR_ASSERT(stk1)
    PTR_ASSERT(stk2)
    PTR_ASSERT(node1)
    PTR_ASSERT(node2)

    while (*index < (size_t)(stk1->size - 1) && *index < (size_t)(stk2->size - 1) && strcmp(node1->data, node2->data) == 0)
    {
        *index += 1;
        switch (GetStkDataElemT(stk1, *index))
        {
            case ADD_LEFT_NODE:
                node1 = node1->left;
                break;

            case ADD_RIGHT_NODE:
                node1 = node1->right;
                break;

            default:
                break;
        }

        switch (GetStkDataElemT(stk2, *index))
        {
            case ADD_LEFT_NODE:
                node2 = node2->left;
                break;

            case ADD_RIGHT_NODE:
                node2 = node2->right;
                break;

            default:
                break;
        }
    }
}