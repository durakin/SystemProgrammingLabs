#include <malloc.h>
#include "FileIO.h"
#include "Input.h"

/*! \enum
 *  \brief  Operation code for main menu and every sub-menu
 */
enum OperationsCodes
{
    ADD = 1,
    PRINT = 2,
    PRINT_BY_NAME = 1,
    PRINT_BY_ISLANDS = 2,
    PRINT_IF_ANY_UNINHABITED = 3,
    PRINT_ALL = 4,
    PRINT_BACK = 5,
    DELETE = 3,
    MODIFY = 4,
    MODIFY_NAME = 1,
    MODIFY_ISLANDS = 2,
    MODIFY_UNINHABITED_ISLANDS = 3,
    MODIFY_BACK = 4,
    CHANGE_FILE = 5,
    CHANGE_FILE_EXISTING = 1,
    CHANGE_FILE_NEW = 2,
    QUIT = 6
};

/*! \brief Checks if number can be a main menu operation codes
 *
 *  \param numberToCheck number to check.
 *
 *  \return true if number can be a main menu operation codes
 *  false - otherwise
 */
bool MainMenuInputCheck(int operationCode)
{
    return operationCode >= ADD && operationCode <= QUIT;
}

/*! \brief Checks if number can be a print menu operation codes
 *
 *  \param numberToCheck number to check.
 *
 *  \return true if number can be a print menu operation codes
 *  false - otherwise
 */
bool PrintMenuInputCheck(int operationCode)
{
    return operationCode >= PRINT_BY_NAME && operationCode <= PRINT_BACK;
}

bool ChangeFileMenuInputCheck(int operationCode)
{
    return operationCode >= CHANGE_FILE_EXISTING &&
           operationCode <= CHANGE_FILE_NEW;
}

/*! \brief Checks if number can be a modify menu operation codes
 *
 *  \param numberToCheck number to check.
 *
 *  \return true if number can be a modify menu operation codes
 *  false - otherwise
 */
bool ModifyMenuInputCheck(int operationCode)
{
    return operationCode >= MODIFY_NAME &&
           operationCode <= MODIFY_BACK;
}

bool nameInputCheck(char* stringToCheck)
{
    for (int i = 0; i < strlen(stringToCheck); i++)
    {
        if (stringToCheck[i] >= '0' && stringToCheck[i] <= '9' ||
            stringToCheck[i] >= 'A' && stringToCheck[i] <= 'Z' ||
            stringToCheck[i] >= 'a' && stringToCheck[i] <= 'z')
        {
            return true;
        }
    }
    return false;
}

bool islandsNumberCheck(int numberToCheck)
{
    return numberToCheck > 0;
}

bool inhabitedIslandsNumberCheck(int numberToCheck)
{
    return numberToCheck >= 0;
}


int main()
{
    int fd;

    int inputSize;

    int operationCode;

    while (true)
    {
        int subOperationCode;
        printf("\n1. Add island group.\n"
               "2. Print data.\n"
               "3. Delete data.\n"
               "4. Modify data.\n"
               "5. Change save file.\n"
               "6. Quit.\n");
        operationCode = checkedInputInt(MainMenuInputCheck);

        if (operationCode == ADD)
        {
            printf("Enter island group's name\n");
            char* name;
            name = (char*) malloc(inputSize * sizeof(char));
            checkedInputString(name, nameInputCheck, inputSize);
            int islands;
            printf("Enter overall number of islands in group\n");
            islands = checkedInputInt(islandsNumberCheck);
            int inhabitedIslands;
            printf("Enter number of inhabited islands in group\n");
            inhabitedIslands = checkedInputInt(
                    inhabitedIslandsNumberCheck);
            if (addIslandGroup(fd, name, islands, inhabitedIslands,
                               inputSize) == 0)
            {
                printf("Added!\n");
            }
            else
            {
                printf("There is a conflict in islands numbers or group"
                       "with such name already exists. None added\n");
            }
            free(name);
            continue;
        }

        if (operationCode == PRINT)
        {

            while (true)
            {
                printf("\n1. Print group by name."
                       "\n2. Print group by islands number."
                       "\n3. Check if any island group is totally"
                       "uninhabited."
                       "\n4. Print all island group."
                       "\n5. Back."
                       "\n");
                subOperationCode = checkedInputInt(PrintMenuInputCheck);
                if (subOperationCode == PRINT_BY_NAME)
                {
                    char* name;
                    name = (char*) malloc(inputSize * sizeof(char));
                    printf("Enter required group's name\n");
                    checkedInputString(name, nameInputCheck, inputSize);
                    printIslandGroupByName(fd, name, inputSize);
                    free(name);
                }
                /*
                if (subOperationCode == PRINT_BY_ISLANDS)
                {

                    int requiredIslands;
                    printf("Enter required number of islands\n");
                    requiredIslands = CycledCheckedInputInt(
                            islandsNumberCheck);
                    PrintIslandGroupsByIslands(objectList, requiredIslands);

                }
                if (subOperationCode == PRINT_IF_ANY_UNINHABITED)
                {
                    if (AnyUnInhabitedIslandGroups(objectList))
                    {
                        printf("Found at least one totally uninhabited"
                               "island group\n");
                    }
                    else
                    {
                        printf("There is no any uninhabited island"
                               "groups\n");

                    }
                }
                 */
                if (subOperationCode == PRINT_ALL)
                {
                    printAllIslandGroup(fd, inputSize);
                }
                if (subOperationCode == QUIT)
                {
                    break;
                }
            }
        }
        /*
        if (operationCode == DELETE)
        {
            char* name;
            printf("Enter name of the group to delete\n");
            name = CycledCheckedInputString(IslandGroupNameCheck);

            if (DeleteIslandGroup(&objectList, name) == 0)
            {
                printf("Deleted!");
            }
            else
            {
                printf("No such island group");
            }
            free(name);
        }
        if (operationCode == MODIFY)
        {
            printf("\n1. Change island group name."
                   "\n2. Change island group overall number of islands."
                   "\n3. Change island group number of inhabited islands."
                   "\n4. Back."
                   "\n");
            subOperationCode = CycledCheckedInputInt(ModifyMenuInputCheck);
            if (subOperationCode == MODIFY_NAME)
            {
                char* originalName;
                printf("Enter required group's name\n");
                originalName = CycledCheckedInputString(IslandGroupNameCheck);
                char* newName;
                printf("Enter new name for this island group\n");
                newName = CycledCheckedInputString(IslandGroupNameCheck);

                if (ChangeIslandGroupName(objectList, originalName,
                                          newName) == 0)
                {
                    printf("Name changed!");
                    newName = NULL;
                }
                else
                {
                    printf("Either new name is taken, or there is no"
                           "island group with such name");
                    free(newName);
                }
                free(originalName);
            }
            if (subOperationCode == MODIFY_ISLANDS)
            {
                char* name;
                printf("Enter required group's name\n");
                name = CycledCheckedInputString(IslandGroupNameCheck);
                int newIslands;
                printf("Enter new overall number of islands in group\n");
                newIslands = CycledCheckedInputInt(islandsNumberCheck);
                if (ChangeIslandGroupIslands(objectList, name,
                                             newIslands) == 0)
                {
                    printf("Number of islands changed!\n");
                }
                else
                {
                    printf("There is no island group with such name\n");
                }
                free(name);
            }
            if (subOperationCode == MODIFY_UNINHABITED_ISLANDS)
            {
                char* name;
                printf("Enter required group's name\n");
                name = CycledCheckedInputString(IslandGroupNameCheck);
                int newInhIslands;
                printf("Enter new number of inhabited islands in group\n");
                newInhIslands = CycledCheckedInputInt(
                        inhabitedIslandsNumberCheck);
                if (ChangeIslandGroupInhIslands(objectList, name,
                                                newInhIslands) == 0)
                {
                    printf("Number of inhabited islands changed!\n");
                }
                else
                {
                    printf("Either there is no such island or number of"
                           "inhabited islands is bigger than overall number"
                           "of islands\n");
                }
                free(name);
            }
        }
         */
        if (operationCode == CHANGE_FILE)
        {
            while (true)
            {
                printf("\n1. Load existing file."
                       "\n2. Create new file."
                       "\n");
                subOperationCode = checkedInputInt(PrintMenuInputCheck);
                if (subOperationCode == CHANGE_FILE_EXISTING)
                {
                    printf("Enter name for save file\n");
                    char filename[MAX_INPUT_SIZE];
                    checkedInputString(filename, nameInputCheck, MAX_INPUT_SIZE);
                    if (openFile(&fd, filename, &inputSize) != 0)
                    {
                        printf("Couldn't load this file.\n");
                        break;
                    }
                }
                if (subOperationCode == CHANGE_FILE_NEW)
                {
                    printf("Enter name for new save file. Warning: if such file exists - it will be overwritten\n");
                    char filename[MAX_INPUT_SIZE];
                    checkedInputString(filename, nameInputCheck, MAX_INPUT_SIZE);
                    if (prepareNewFile(&fd, filename, INPUT_SIZE) != 0)
                    {
                        printf("Couldn't create new save file.\n");
                    }
                }
            }
        }

        if (operationCode == QUIT)
        {
            break;
        }
    }
    return 0;
}
