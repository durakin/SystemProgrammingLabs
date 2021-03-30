#include <stdio.h>
#include <string.h>
#include "IslandGroup.h"
#include "Input.h"


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
    QUIT = 5
};

bool MainMenuInputCheck(int operationCode)
{
    return operationCode >= ADD && operationCode <= QUIT;
}

bool PrintMenuInputCheck(int operationCode)
{
    return operationCode >= PRINT_BY_NAME && operationCode <= PRINT_BACK;
}

bool ModifyMenuInputCheck(int operationCode)
{
    return operationCode >= MODIFY_NAME &&
           operationCode <= MODIFY_BACK;
}

int main()
{
    ListLink* objectList;
    objectList = NULL;

    int operationCode;
    while (true)
    {
        int subOperationCode;
        printf("\n1. Add island group.\n"
               "2. Print data.\n"
               "3. Delete data.\n"
               "4. Modify data.\n"
               "5. Quit.\n");
        operationCode = CycledCheckedInputInt(MainMenuInputCheck);

        if (operationCode == ADD)
        {
            printf("Enter island group's name\n");
            char* name;
            name = CycledCheckedInputString(IslandGroupNameCheck);
            int islands;
            printf("Enter overall number of islands in group\n");
            islands = CycledCheckedInputInt(IslandsNumberCheck);
            int inhabitedIslands;
            printf("Enter number of inhabited islands in group\n");
            inhabitedIslands = CycledCheckedInputInt(
                    InhabitedIslandsNumberCheck);
            ListLink* addResult;

            addResult = AddIslandGroup(objectList, name, islands,
                                       inhabitedIslands);
            if (addResult != NULL)
            {
                objectList = addResult;
                printf("Added!\n");
            }
            else
            {
                printf("There is a conflict in islands numbers or group with such name already exists. None added\n");
            }
            continue;
        }

        if (operationCode == PRINT)
        {

            while (true)
            {
                printf("\n1. Print group by name."
                       "\n2. Print group by islands number."
                       "\n3. Check if any island group is totally uninhabited."
                       "\n4. Print all island group."
                       "\n5. Back."
                       "\n");
                subOperationCode = CycledCheckedInputInt(PrintMenuInputCheck);
                if (subOperationCode == PRINT_BY_NAME)
                {
                    char* name;
                    printf("Enter required group's name\n");
                    name = CycledCheckedInputString(IslandGroupNameCheck);
                    PrintIslandGroupLink(
                            FindIslandGroupLinkByName(objectList, name));
                    free(name);
                }
                if (subOperationCode == PRINT_BY_ISLANDS)
                {
                    int requiredIslands;
                    printf("Enter required number of islands\n");
                    requiredIslands = CycledCheckedInputInt(
                            IslandsNumberCheck);
                    ListLink* tempSubList;
                    tempSubList = ListLinkIslandGroupsByIslands(objectList,
                                                                requiredIslands);
                    PrintAllIslandGroups(tempSubList);
                    ListLinkFree(tempSubList, (void*) FreeIslandGroup);
                }
                if (subOperationCode == PRINT_IF_ANY_UNINHABITED)
                {
                    if (AnyUnInhabitedIslandGroups(objectList))
                    {
                        printf("Found at least one totally uninhabited island group\n");
                    }
                    else
                    {
                        printf("There is no any uninhabited island groups\n");

                    }
                }
                if (subOperationCode == PRINT_ALL)
                {
                    PrintAllIslandGroups(objectList);
                }
                if (subOperationCode == QUIT)
                {
                    break;
                }
            }
        }
        if (operationCode == DELETE)
        {
            char* name;
            printf("Enter name of the group to delete\n");
            name = CycledCheckedInputString(IslandGroupNameCheck);

            if (DeleteIslandGroupByName_proper(&objectList, name) == 0)
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
                if ((ChangeIslandGroupName(
                        FindIslandGroupLinkByName(objectList, originalName),
                        newName)) == 0)
                {
                    printf("Name changed!");
                }
                else
                {
                    printf("Either new name is taken, or there is no island group with such name");
                }
                free(originalName);
                free(newName);
            }
            if (subOperationCode == MODIFY_ISLANDS)
            {
                char* name;
                printf("Enter required group's name\n");
                name = CycledCheckedInputString(IslandGroupNameCheck);
                int newIslands;
                printf("Enter new overall number of islands in group\n");
                newIslands = CycledCheckedInputInt(IslandsNumberCheck);
                if (ChangeIslandGroupIslands(
                        FindIslandGroupLinkByName(objectList, name),
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
                int newInhabitedIslands;
                printf("Enter new number of inhabited islands in group\n");
                newInhabitedIslands = CycledCheckedInputInt(
                        InhabitedIslandsNumberCheck);
                if (ChangeInhabitedIslandGroupIslands(
                        FindIslandGroupLinkByName(objectList, name),
                        newInhabitedIslands) == 0)
                {
                    printf("Number of inhabited islands changed!\n");
                }
                else
                {
                    printf("Either there is no such island or number of inhabited islands is bigger than overall number of islands\n");
                }
                free(name);
            }
        }
        if (operationCode == QUIT)
        {
            break;
        }
    }
    return 0;
}
