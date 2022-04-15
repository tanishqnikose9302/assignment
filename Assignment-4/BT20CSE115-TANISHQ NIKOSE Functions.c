#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Assuming Heap memory size 100
#define HEAPSIZE 100

//Node for Allocation List
typedef struct NodeAllocate
{
    char name[20];
    int StartingIndex, OccupiedSpace;
    struct NodeAllocate *next, *prev;
} NodeAllocate;

//Declaring pointer variable for Allocation List
NodeAllocate *AllocHead, *AllocTail;

//Node for Free list
typedef struct NodeFree
{
    int StartingIndex, FreeSpace;
    struct NodeFree *next, *prev;
} NodeFree;

//Declaring pointer variable for Free List
NodeFree *FreeHead, *FreeTail;

//Initial condition i.e, before allocation of any memory
void initialize()
{
    AllocHead = NULL;
    AllocTail = NULL;
    NodeFree *Node;
    Node = (NodeFree *)malloc(sizeof(NodeFree));
    Node->StartingIndex = 0;
    Node->FreeSpace = HEAPSIZE;
    Node->next = NULL;
    Node->prev = NULL;
    FreeHead = Node;
    FreeTail = Node;
}

//Function to print out free list and allocated list
void PrintList(void)
{
    NodeAllocate *tempAlloc = AllocHead;
    NodeFree *tempFree = FreeHead;
    printf("The Free List is :\n");
    printf("\tStarting Address\tEnding Address\n");
    while (tempFree)
    {
        printf("\t%d\t\t\t%d\n", tempFree->StartingIndex, (tempFree->FreeSpace + tempFree->StartingIndex - 1));
        tempFree = tempFree->next;
    }
    printf("\n");
    printf("The Allocated List is :\n");
    printf("\tProcess name\tStarting Address\tEnding Address\n");
    while (tempAlloc)
    {
        printf("\t%s\t\t%d\t\t\t%d\n", tempAlloc->name, tempAlloc->StartingIndex, tempAlloc->OccupiedSpace + tempAlloc->StartingIndex - 1);
        tempAlloc = tempAlloc->next;
    }
}

//Allocation of heap memory
void ManuallyAllocate(int size, char *str)
{
    int flag = 1;
    NodeFree *temp = FreeHead;
    while (flag && temp)
    {
        if (temp->FreeSpace >= size)
        {
            NodeAllocate *NewAlloc = (NodeAllocate *)malloc(sizeof(NodeAllocate));
            NewAlloc->next = NULL;
            NewAlloc->prev = NULL;
            NewAlloc->OccupiedSpace = size;
            NewAlloc->StartingIndex = temp->StartingIndex;
            temp->FreeSpace -= size;
            if (!temp->FreeSpace)   //if hole is completed by the process 
            {
                if (!temp->next && !temp->prev)//if there is no hole left
                {
                    FreeHead = NULL;
                    FreeTail = NULL;
                }
                else                            //if there is atleast 1 hole left
                {
                    if (!temp->next)
                    {
                        FreeTail = temp->prev;
                        temp->prev->next = NULL;
                    }
                    else
                    {
                        FreeHead = temp->next;
                        temp->next->prev = NULL;
                    }
                }
                free(temp);
            }
            else                //if hole size > process size
            {
                temp->StartingIndex += size;
            }
            strcpy(NewAlloc->name, str);
            flag = 0;
            if (!AllocHead)     //if Allocation list is empty
            {
                AllocHead = NewAlloc;
                AllocTail = NewAlloc;
            }
            else                //if Allocation List has atleast 1 element
            {
                AllocTail->next = NewAlloc;
                NewAlloc->prev = AllocTail;
                AllocTail = NewAlloc;
            }
        }
        else
        {
            temp = temp->next;
        }
    }
    if (flag)           //if there is no space to store the process
    {
        printf("Memory cannot be Allocated to the Process '%s' as there is not enough heap memory", str);
    }
}

//Freeing allocated memory
void FreeMember(char *str)
{
    NodeAllocate *temp1 = AllocHead;
    while (strcmp(str, temp1->name) && temp1)//finding the process to be freed
    {
        temp1 = temp1->next;
    }
    if (temp1)                                 //if process to be freed found
    {
        if (!(temp1->prev))                    //if the process to be freed is the first process 
        {
            if (temp1 != AllocTail)
            {
                AllocHead = temp1->next;
                AllocHead->prev = NULL;
            }
            else
            {
                AllocHead = NULL;
            }
        }
        else                                    //if the process to be freed is not the first process
        {
            temp1->prev->next = temp1->next;
            if (temp1 != AllocTail)              //if the process to be freed is in between process
            {
                temp1->next->prev = temp1->prev;
            }
            else                                 //if the process to be freed is the last process
            {
                AllocTail = temp1->prev;
            }
        }
        NodeFree *temp2 = FreeHead;
        while (temp2 && temp2->StartingIndex < (temp1->StartingIndex + temp1->OccupiedSpace - 1))
        {
            temp2 = temp2->next;
        }
        if (temp2) 
        {
            if (temp2->StartingIndex == temp1->StartingIndex + temp1->OccupiedSpace)
            {
                temp2->StartingIndex -= temp1->OccupiedSpace;
                temp2->FreeSpace += temp1->OccupiedSpace;
            }
            else if (temp2->prev && temp1->StartingIndex == temp2->prev->StartingIndex + temp2->prev->FreeSpace)
            {
                temp2->FreeSpace += temp1->OccupiedSpace;
            }
            else
            {
                NodeFree *temp3 = (NodeFree *)malloc(sizeof(NodeFree));
                temp3->FreeSpace = temp1->OccupiedSpace;
                temp3->StartingIndex = temp1->StartingIndex;
                temp3->next = temp2;
                if (!temp2->prev)
                {
                    temp3->prev = NULL;
                    FreeHead = temp3;
                }
                else
                {
                    temp3->prev = temp2->prev;
                    temp2->prev->next = temp3;
                }
                temp2->prev = temp3;
            }
        }
        else
        {
            NodeFree *temp3 = (NodeFree *)malloc(sizeof(NodeFree));
            temp3->FreeSpace = temp1->OccupiedSpace;
            temp3->StartingIndex = temp1->StartingIndex;
            temp3->next = NULL;
            if(!FreeTail)
            {
                temp3->prev = NULL;
                FreeHead = temp3;
            }
            else
            {
                temp3->prev = FreeTail;
                FreeTail->next = temp3;
            }
            FreeTail = temp3;
        }
        free(temp1);
    }
    else
    {
        printf("No such process is stored in heap\n");
    }
}