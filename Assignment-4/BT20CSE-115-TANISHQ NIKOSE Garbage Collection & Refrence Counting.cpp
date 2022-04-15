//                     CSP202 Software lab-2
//						Assignment-4			BT20CSE-115-TANISHQ NIKOSE
//Question:Write a program to implement Garbage Collection & Refrence Counting.
#include<iostream>
using namespace std;
struct node
{
    int data;
    int count;
    struct node* adjacent1;
    struct node* adjacent2;
    struct node* adjacent3;
    node(int num)
    {
        data = num;
        adjacent1=NULL;
        adjacent2=NULL;
        adjacent3=NULL;
        count=0;
    }
}; //we know at most 3 connections are present
typedef struct root_tag
{
    node* pointer;
}root;

node* heap[8];
/*
root1->5 7 3
       |/|/|
root2->1 8 | 
       |\| |
       | |\|
       |\| |\
       2 9 10
*/
void initialize(root& root1,root& root2)
{                                                   
    node* temp = new node(5);
    heap[0]=temp;
    temp = new node(1);
    heap[1]=temp;
    temp = new node(2);
    heap[2]=temp;
    temp = new node(9);
    heap[3]=temp;
    temp = new node(10);
    heap[4]=temp;
    temp = new node(7);
    heap[5]=temp;
    temp = new node(8);
    heap[6]=temp;
    temp = new node(3);
    heap[7]=temp;
    temp = NULL;
    //now all nodes are in the 'heap',to create connections now
    //while making connections, update reference counts
    root1.pointer=heap[0];//root1->5
    heap[0]->count+=1;
    heap[0]->adjacent1=heap[1];//5->1
    heap[1]->count+=1;
    root2.pointer=heap[1];//root2->1
    heap[1]->count+=1;
    heap[1]->adjacent1=heap[2];//1->2
    heap[2]->count+=1;
    heap[1]->adjacent2=heap[3];//1->9
    heap[3]->count+=1;
    heap[1]->adjacent3=heap[4];//1->10
    heap[4]->count+=1;
    heap[5]->adjacent1=heap[1];//7->1
    heap[1]->count+=1;
    heap[5]->adjacent2=heap[6];//7->8
    heap[6]->count+=1;
    heap[6]->adjacent1=heap[4];//8->10
    heap[4]->count+=1;
    heap[7]->adjacent1=heap[6];//3->8
    heap[6]->count+=1;
    heap[7]->adjacent2=heap[4];//3->10
    heap[4]->count+=1;
    //connections done
}
void print_node(const node* node)
{
    if(node==NULL)
    {
        return;
    }
    cout<<" "<<node->data<<"(rfc="<<node->count<<")";
    if (node->adjacent1!=NULL || node->adjacent2!=NULL || node->adjacent3!=NULL)
    {
        cout<<"-[";
        print_node(node->adjacent1);
        print_node(node->adjacent2);
        print_node(node->adjacent3);
        cout<<" ]";
    }
}
void print_heap(node** arr)
{
    for(int i=0;i<8;i++)
    {
        if(arr[i]!=NULL)
        {
            print_node(arr[i]);
            cout<<endl;
        }
    }
}
void print_useful_heap(const root& value)
{
    cout<<"root->";
    print_node(value.pointer);
    cout<<endl;
}
int main()
{
    root A,B;
    initialize(A,B);
    cout<<"This is the Simulation for reference counting garbage collector\n";
    cout<<"Key to navigate the printed table: - indicates connection and [] indicate all the elements connected to the element\n";
    cout<<"the full heap is: "<<endl;
    print_heap(heap);
    cout<<"-----------------"<<endl;
    cout<<"Heap connected to the roots is: "<<endl;
    print_useful_heap(A);
    print_useful_heap(B);
    cout<<"-----------------"<<endl;    
}