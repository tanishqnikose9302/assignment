//                     CSP202 Software lab-2
//						Assignment-4			BT20CSE-115-TANISHQ NIKOSE
//Question:Write a program to implement heap management scheme. Implement the ‘allocate’ and ‘free’ functions. Ensure that adjacent free blocks are merged together.
#include "BT20CSE115-TANISHQ NIKOSE Functions.c"
int main()
{
    initialize();
    int size = 0, choice = 1;
    char name[20];
    while (choice)
    {
        printf("\nEnter the choice\n");
        printf("1.Allocation\n2.Free Memory\n3.Print Lists\n4.Exit\n");
        printf("Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the process name : ");
            scanf("%s", name);
            printf("Enter the no. of the block to allocate : ");
            scanf("%d", &size);
            ManuallyAllocate(size, name);
            printf("\n");
            break;

        case 2:
            printf("Enter the process to be freed : ");
            scanf("%s", name);
            FreeMember(name);
            printf("\n");
            break;

        case 3:
            PrintList();
            break;

        case 4:
            exit(0);
            break;

        default:
            printf("Invaid Choice, please try again\n");
        }
    }
    return 0;
}