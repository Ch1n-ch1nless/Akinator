#include "akinator.h"

error_t PlayGame(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    while (true)
    {
        ShowIntro();

        Mods mode = GetMode();

        switch (mode)
        {
            case AKINATOR:
                error |= GuessObject(tree->root); //fix!
                break;

            case MODS_DEFINITION:
                error |= GetDefinition(tree); //TODO fix function
                break;

            case COMPARISON:
                error |= GetComparison(tree); //TODO fix function
                break;

            case DELETE_DATA_BASE:
                error |= DeleteDataBase(tree);
                break;

            case SAVE_DATA_BASE:
                error |= SaveDataBase(tree);
                break;

            case DRAW_TREE:
                TreeGraphDump(tree);
                break;

            case QUIT:
                ShowOutro();
                return error;
                break;

            case INCORRECT_MODE:
                printf("You enter wrong mode try again!\n");
                break;
            
            default:
                break;
        }

        printf("Do you want to continue game?\n");

        Answers ans = GetAnswer();
        switch(ans)
        {
            case YES:
                break;

            case NO:
                ShowOutro();
                return error;

            case UNDEFINED_ANSWER:
            default:
                fprintf(stderr, "Error! Unknown answer");
                return error | INPUT_ERR;
        }

    }

    return error;
}

void ShowIntro()
{
    printf("Hello, dear friend! I am AkinatorGPT. I can read minds!\n"
           "Ok, i will tell you more about my capabilities:\n"
           "\tEnter \'a\' -- I'll guess what you've made up your mind\n"
           "\tEnter \'d\' -- I'll give you a definition of object\n"
           "\tEnter \'c\' -- I'll give you comprasion of 2 objects!\n"
           "\tEnter \'e\' -- I'll delete me data base!\n"
           "\tEnter \'s\' -- I'll save my new data base!\n"
           "\tEnter \'p\' -- I'll draw tree graph!\n"
           "\tEnter \'q\' -- I'll complete the job!\n\n");

    return;
}

void ShowOutro()
{
    printf("Goodbye, my dear friend! See you soon!\n");
}

Mods GetMode()
{
    char mode = INCORRECT_MODE;
    scanf("%c", &mode);

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

        Answers answer = UNDEFINED_ANSWER;

        while ((answer = GetAnswer()) == UNDEFINED_ANSWER)
        {
            printf("Akinator can not understand your command, please, try again!\n\n");
            printf(tree_format "?\n", node->data);
        }

        switch(answer)
        {
            case YES:
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

            case NO:
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

            case UNDEFINED_ANSWER:
                break;

            default:
                break;
        }
    }

    return error;
}

Answers GetAnswer()
{
    printf("Enter \'y\' -- if your answer is yes\n");
    printf("Enter \'n\' -- if your answer is no\n");

    char ans = '\0';
    scanf("%c", &ans);

    ClearBuffer();
    // Remove switch
    switch(ans)
    {
        case (char) YES:
            return YES;
            break;

        case (char) NO:
            return NO;
            break;

        default:
            return UNDEFINED_ANSWER;
            break;
    }
}

error_t AddNewObject(Node* node)
{
    assert((node != nullptr) && "Pointer to node is NULL!!!\n");

    error_t error = NO_ERR;

    // check all errors
    tree_t new_object = GetNameOfObject(&error);
    tree_t difference = GetDifference(&error);

    Node* right_node = NodeCtor(&error, node->data);
    Node* left_node  = NodeCtor(&error, new_object);

    node->data  = difference;
    node->left  = left_node;
    node->right = right_node;

    return error;
}

tree_t GetNameOfObject(error_t* error) //Same functions!
{
    assert((error != nullptr) && "Pointer to error is NULL!!!\n");

    printf("Enter the name of your object?\n");

    tree_t name_of_object = (tree_t) calloc(MAX_LEN_OF_WORD, sizeof(char));
    if ( 0 )
        return nullptr;
    // calloc check?

    fgets(name_of_object, MAX_LEN_OF_WORD, stdin);
    // ret val?
    name_of_object[strlen(name_of_object) - 1] = '\0';

    return name_of_object;
}

tree_t GetDifference(error_t* error) //Same functions!
{
    assert((error != nullptr) && "Pointer to error is NULL!!!\n");

    printf("How do they differ from?\n");

    tree_t difference = (tree_t) calloc(MAX_LEN_OF_WORD, sizeof(char));

    fgets(difference, MAX_LEN_OF_WORD, stdin);
    difference[strlen(difference) - 1] = '\0';   

    return difference;
}

error_t GetDefinition(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    tree_t name_of_object = GetNameOfObject(&error);

    Stack stk = {};

    STACK_CTOR(&stk);

    SearchObject(name_of_object, &stk, tree->root);

    if (stk.size == 0)
    {
        printf("Sorry, object \'%s\' isn't in data base!\n", name_of_object);
    }
    else
    {
        printf("Definition of %s:\n", name_of_object);

        for (size_t i = 0; i < (size_t) stk.size - 1; i++)
        {
            Node* cur_node  = *GetStkDataElemT(&stk, i);
            Node* next_node = *GetStkDataElemT(&stk, i + 1);

            // str = "not "
            if (cur_node->right == next_node)
            {
                printf("\t[%d]: not" tree_format "\n", i, cur_node->data);
            }
            else
            {
                printf("\t[%d]: " tree_format "\n", i, cur_node->data);
            }
        }
    }

    return error;
}

error_t GetComparison(Tree* tree)
{
    assert((tree != nullptr) && "Pointer to tree is NULL!!!\n");

    error_t error = NO_ERR;

    // use GetDefinition here
    tree_t name1 = GetNameOfObject(&error);

    Stack stk1 = {};

    STACK_CTOR(&stk1);

    tree_t name2 = GetNameOfObject(&error);

    Stack stk2 = {};

    STACK_CTOR(&stk2);

    size_t index1 = 0;
    size_t index2 = 0;

    SearchObject(name1, &stk1, tree->root);
    SearchObject(name2, &stk2, tree->root);

    Node* node1 = *GetStkDataElemT(&stk1, index1);
    Node* node2 = *GetStkDataElemT(&stk1, index2);

    printf("Common features of objects:\n");
    SearchFirstDifference(&index1, &stk1, &stk2, node1, node2);
    PrintNodeData(&index2, &stk1, node1, index1);

    printf("\nDifferent features of " tree_format "\n", name1);
    PrintNodeData(&index1, &stk1, node1, stk1.size - 1);

    printf("\nDifferent features of " tree_format "\n", name2);
    PrintNodeData(&index2, &stk2, node2, stk2.size - 1);

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

    //PrintInPreOrder(tree->root, data_file);

    //CLOOOOSE!!!

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

void ClearBuffer(void)
{
    int c = EOF;
    do
    {
        c = getchar();
    } 
    while (c != EOF && c != '\n');
}

bool SearchObject(tree_t name_of_object, Stack* stk, Node* node)
{
    elem_t temp_adress_of_temp_node = nullptr;

    StackPush(stk, &node);
    
    if (strcmp(name_of_object, node->data) == 0)
    {
        return true;
    }

    if ((node->left != nullptr) && SearchObject(name_of_object, stk, node->left))
    {
        return true;
    }

    if ((node->right != nullptr) && SearchObject(name_of_object, stk, node->right))
    {
        return true;
    }

    StackPop(stk, &temp_adress_of_temp_node);

    return false;
}

void PrintNodeData(size_t* index, Stack* stk, Node* node, size_t len)
{
    assert((stk  != nullptr) && "Error! Pointer to stack is NULL!!!\n");
    assert((node != nullptr) && "Error! Pointer to node  is NULL!!!\n");
    assert((*index > len)    && "Error! Index is greater then len!!!\n"); //nullptr!!!

    while (*index < len)
    {
        printf("\t" tree_format "\n", node->data);
        ++*index;
        node = *GetStkDataElemT(stk, *index);
    }

    return;
}

void SearchFirstDifference(size_t* index, Stack* stk1, Stack* stk2, Node* node1, Node* node2)
{
    assert((index != nullptr) && "Error! Pointer to index is NULL!!!\n");
    assert((stk1  != nullptr) && "Error! Pointer to stk1  is NULL!!!\n");
    assert((stk2  != nullptr) && "Error! Pointer to stk1  is NULL!!!\n");
    assert((node1 != nullptr) && "Error! Pointer to node1 is NULL!!!\n");
    assert((node2 != nullptr) && "Error! Pointer to node2 is NULL!!!\n");

    while (*index < (size_t)(stk1->size - 1) && *index < (size_t)(stk2->size - 1) && strcmp(node1->data, node2->data) == 0)
    {
        *index += 1;
        node1 = *GetStkDataElemT(stk1, *index);
        // check error
        node2 = *GetStkDataElemT(stk2, *index);
    }
}