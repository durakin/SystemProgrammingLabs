/*! \file   main.c
 *  \brief  Provides console interface for work with FileIO.
 */


#include <malloc.h>
#include "FileIO.h"
#include "Input.h"
#include <unistd.h>

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
 *  \param numberToCheck number to check
 *
 *  \return true if number can be a main menu operation codes
 *  false - otherwise
 */
bool MainMenuInputCheck(int operationCode)
{
    return operationCode >= ADD && operationCode <= QUIT;
}

/*! \brief Checks if number doesn't reach maximal input size
 *
 *  \param intToCheck number to check
 *
 *  \return true if number doesn't reach maximal input size
 *  false - otherwise
 */
bool InputSizeInputCheck(int intToCheck)
{
    return intToCheck > 0 && intToCheck < MAX_INPUT_SIZE;
}

/*! \brief Checks if number can be a print menu operation codes
 *
 *  \param numberToCheck number to check
 *
 *  \return true if number can be a print menu operation codes
 *  false - otherwise
 */
bool PrintMenuInputCheck(int operationCode)
{
    return operationCode >= PRINT_BY_NAME && operationCode <= PRINT_BACK;
}

/*! \brief Checks if number can be a change file menu operation codes
 *
 *  \param numberToCheck number to check
 *
 *  \return true if number can be a change file menu operation codes
 *  false - otherwise
 */
bool ChangeFileMenuInputCheck(int operationCode)
{
    return operationCode >= CHANGE_FILE_EXISTING &&
           operationCode <= CHANGE_FILE_NEW;
}

/*! \brief Checks if number can be a modify menu operation codes
 *
 *  \param numberToCheck number to check
 *
 *  \return true if number can be a modify menu operation codes
 *  false - otherwise
 */
bool ModifyMenuInputCheck(int operationCode)
{
    return operationCode >= MODIFY_NAME &&
           operationCode <= MODIFY_BACK;
}

/*! \brief Checks if string can be a filename or islands group name
 *
 *  \param stringToCheck string to check
 *
 *  \return true if number can be a modify menu operation codes
 *  false - otherwise
 */
bool NameInputCheck(char* stringToCheck)
{
    for (int i = 0; i < strlen(stringToCheck); i++)
    {
        if (!(stringToCheck[i] >= '0' && stringToCheck[i] <= '9' ||
              stringToCheck[i] >= 'A' && stringToCheck[i] <= 'Z' ||
              stringToCheck[i] >= 'a' && stringToCheck[i] <= 'z'))
        {
            return false;
        }
    }
    return true;
}

/*! \brief Checks if number can be an overall number of islands in group
 *
 *  \param numberToCheck number to check
 *
 *  \return true if number can be an overall number of islands in group
 */
bool IslandsNumberCheck(int numberToCheck)
{
    return numberToCheck > 0;
}

/*! \brief Checks if number can be a number of inhabitant islands in group
 *
 *  \param numberToCheck number to check
 *
 *  \return true if number can be a number of inhabitant islands in group
 */
bool InhabitedIslandsNumberCheck(int numberToCheck)
{
    return numberToCheck >= 0;
}


int main()
{
    int fd;
    bool loaded;
    loaded = false;
    int inputSize;
    int operationCode;
    char filename[MAX_INPUT_SIZE];

    while (true)
    {
        int subOperationCode;
        if (!loaded)
        {
            printf("NO SAVE FILE TO WORK WITH. Save file must be "
                   "chosen (5) to proceed.\n");
        }
        printf("\n1. Add island group.\n"
               "2. Print data.\n"
               "3. Delete data.\n"
               "4. Modify data.\n"
               "5. Change save file.\n"
               "6. Quit.\n");
        operationCode = CheckedInputInt(MainMenuInputCheck);

        if (!loaded && operationCode != CHANGE_FILE && operationCode != QUIT)
        {
            continue;
        }
        {

            if (operationCode == ADD)
            {
                printf("Enter island group's name\n");
                char* name;
                name = (char*) malloc(inputSize * sizeof(char));
                CheckedInputString(name, NameInputCheck, inputSize);
                int islands;
                printf("Enter overall number of islands in group\n");
                islands = CheckedInputInt(IslandsNumberCheck);
                int inhabitedIslands;
                printf("Enter number of inhabited islands in group\n");
                inhabitedIslands = CheckedInputInt(
                        InhabitedIslandsNumberCheck);
                if (AddIslandGroup(fd, name, islands, inhabitedIslands,
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
                subOperationCode = CheckedInputInt(PrintMenuInputCheck);
                if (subOperationCode == PRINT_BY_NAME)
                {
                    char* name;
                    name = (char*) malloc(inputSize * sizeof(char));
                    printf("Enter required group's name\n");
                    CheckedInputString(name, NameInputCheck, inputSize);
                    PrintIslandGroupByName(fd, name, inputSize);
                    free(name);
                }
                if (subOperationCode == PRINT_BY_ISLANDS)
                {
                    int requiredIslands;
                    printf("Enter required number of islands\n");
                    requiredIslands = CheckedInputInt(
                            IslandsNumberCheck);
                    PrintIslandGroupsByIslands(fd, requiredIslands,
                                               inputSize);
                }
                if (subOperationCode == PRINT_IF_ANY_UNINHABITED)
                {
                    if (IsAnyUninhabited(fd, inputSize))
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
                if (subOperationCode == PRINT_ALL)
                {
                    PrintAllIslandGroups(fd, inputSize);
                }
                if (subOperationCode == PRINT_BACK)
                {
                    break;
                }
            }
        }

        if (operationCode == DELETE)
        {
            char* name;
            name = (char*) malloc(inputSize * sizeof(char));
            printf("Enter required group's name\n");
            CheckedInputString(name, NameInputCheck, inputSize);

            if (DeleteGroupByName(&fd, name, filename, inputSize))
            {
                printf("Deleted!\n");
            }
            else
            {
                printf("No such island group\n");
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
            subOperationCode = CheckedInputInt(ModifyMenuInputCheck);
            if (subOperationCode == MODIFY_NAME)
            {
                char* originalName;
                printf("Enter required group's name\n");
                originalName = (char*) malloc(inputSize * sizeof(char));
                CheckedInputString(originalName, NameInputCheck, inputSize);
                char* newName;
                printf("Enter new name for this island group\n");
                newName = (char*) malloc(inputSize * sizeof(char));
                CheckedInputString(newName, NameInputCheck, inputSize);

                if (ChangeIslandGroupName(fd, originalName,
                                          newName, inputSize) == 0)
                {
                    printf("Name changed!\n");
                }
                else
                {
                    printf("Either new name is taken, or there is no"
                           "island group with such name\n");
                }
                free(originalName);
                free(newName);
            }

            if (subOperationCode == MODIFY_ISLANDS)
            {
                char* name;
                name = (char*) malloc(inputSize * sizeof(char));
                printf("Enter required group's name\n");
                CheckedInputString(name, NameInputCheck, inputSize);
                int newIslands;
                printf("Enter new overall number of islands in group\n");
                newIslands = CheckedInputInt(IslandsNumberCheck);
                if (ChangeIslandGroupIslands(fd, name,
                                             newIslands, inputSize) == 0)
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
                name = (char*) malloc(inputSize * sizeof(char));
                printf("Enter required group's name\n");
                CheckedInputString(name, NameInputCheck, inputSize);
                int newInhabitedIslands;
                printf("Enter new number of inhabited islands in group\n");
                newInhabitedIslands = CheckedInputInt(
                        InhabitedIslandsNumberCheck);
                if (ChangeIslandGroupInhabitantIslands(fd, name,
                                                       newInhabitedIslands,
                                                       inputSize) == 0)
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

        if (operationCode == CHANGE_FILE)
        {
            if(loaded)
            {
                close(fd);
            }
            while (true)
            {

                printf("\n1. Load existing file."
                       "\n2. Create new file."
                       "\n");
                subOperationCode = CheckedInputInt(ChangeFileMenuInputCheck);
                if (subOperationCode == CHANGE_FILE_EXISTING)
                {
                    printf("Enter name for save file\n");
                    CheckedInputString(filename, NameInputCheck,
                                       MAX_INPUT_SIZE);
                    if (OpenFile(&fd, filename, &inputSize) == 0)
                    {
                        printf("Successfully loaded!\n");
                        break;
                    }
                    else
                    {
                        printf("Couldn't load this file.\n");
                    }
                }
                if (subOperationCode == CHANGE_FILE_NEW)
                {
                    printf("Enter name for new save file. Warning: if"
                           " such file exists - it will be overwritten\n");
                    CheckedInputString(filename, NameInputCheck,
                                       MAX_INPUT_SIZE);
                    printf("Enter size of name string (1 - 63)\n");
                    inputSize = CheckedInputInt(InputSizeInputCheck);
                    if (PrepareNewFile(&fd, filename, inputSize) == 0)
                    {
                        break;
                    }
                    else
                    {
                        printf("Couldn't create new save file.\n");
                    }
                }
            }
            loaded = true;
        }

        if (operationCode == QUIT)
        {
            if (loaded)
            {
                close(fd);
            }
            break;
        }
    }
    return 0;
}
