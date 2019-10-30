#include <stdio.h>
#include <stdlib.h>
/*
 *
 */
typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
/*
 *
 */
typedef struct
{
    Node* head;
    Node* tail;
} DoublyLinkedList;


const DoublyLinkedList EmptyList = {NULL, NULL};
/*
 * convertArrayToDoublyLinkedList
 */
DoublyLinkedList convertArrayToDoublyLinkedList(int array[], int size)
{
    DoublyLinkedList list = {NULL, NULL};
    list.head=malloc(sizeof(Node));
    list.tail=malloc(sizeof(Node));

    Node* n[size];
    n[0]=malloc(sizeof(Node));
    n[0]->prev=NULL;
    list.head=n[0];
    list.head->prev=NULL;
    int i=1;

    n[0]->data=array[0];
    for(i; i<size; i++)
    {
        n[i]=malloc(sizeof(Node));
        n[i]->data=array[i];
        n[i-1]->next=n[i];
        n[i]->prev=n[i-1];
//list.tail=&l[i];

    }
    n[size-1]->next=NULL;
    list.tail=n[size-1];
    list.tail->next=NULL;


    return list;
}
size_t length(DoublyLinkedList list)
{
    if (list.head==NULL)
        return 0;
    size_t count = 0;
    Node*temp=list.head;
    while(temp!=list.tail)
    {
        temp=temp->next;
        count++;

    }
    return count+1;

}
void destroy(DoublyLinkedList*list)
{ Node*x;

  Node*y=list->tail;
  while(list->head!=NULL){
   x=list->head;
   list->head=list->head->next;
   free(x);


   }
list->tail=NULL;
}
DoublyLinkedList dup(DoublyLinkedList list)
{
    int i;
    DoublyLinkedList duplicate;
    Node*x=list.head;
    int a[length(list)];

    if(list.head==EmptyList.head)
        return EmptyList;
    else
    {
        for(i=0; i<length(list); i++)
        {
            a[i]=x->data;
            x=x->next;
        }


        duplicate=convertArrayToDoublyLinkedList(a,length(list));



        return duplicate;
    }

}

DoublyLinkedList concatenate(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList newlist = {NULL, NULL};
    if(list1.head==NULL&&list2.head!=NULL)
        return list2;
    else if(list2.head==NULL&&list1.head!=NULL)
        return list1;
    else if(list2.head==NULL&&list1.head==NULL)
        return EmptyList;
    else
    {
        list2.head->prev=list1.tail;
        list1.tail->next=list2.head;

        newlist.head=list1.head;
        newlist.tail=list2.tail;

        return newlist;
    }
}


void printlnListForward(DoublyLinkedList list)
{
    if(list.head==NULL&&list.tail==NULL)
    {
        printf("the list is empty\n");
    }
    else
    {
        Node*x=list.head;
        while(x!=NULL)
        {
            printf("%d  ",x->data);
        x=x->next;
        }
        printf("\n");
    }
}

void printlnListBackward(DoublyLinkedList list)
{
    if(list.head==NULL&&list.tail==NULL)
    {
        printf("the list is empty\n");
    }
    else
    {
        Node*x=list.tail;
        while(x!=NULL)
        {
            printf("%d  ",x->data);
            x=x->prev;
        }
        printf("\n");
    }
}

void Investigate(char* title, DoublyLinkedList list)
{
    printf("%s\n", title);
    printf("List =         ");
    printlnListForward(list);
    printf("Reverse List = ");
    printlnListBackward(list);
    printf("List Length = %u\n", length(list));
    printf("List isPalindrome = %d\n", isPalindrome(list));
    printf("...................................................\n");
}
/*
 *
 */
int isPalindrome(DoublyLinkedList list)
{
    int i;
    int flag=0;
    Node*temp=list.head;
    Node*temp1=list.tail;
    if(list.head==0)
        return 1;
    else
    {
        Node*temp=list.head;
        if(list.head->data!=list.tail->data)
            return 0;

        else
        {
            for(i=0; i<=length(list)/2; i++)
                if(temp->data==temp1->data)
                    flag=1;
                else
                    flag=0;


            temp=temp->next;
            temp1=temp1->prev;

            return flag;

        }
    }
}


void testPalindrome()
{
    int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array4[] = {7, 8, 9, 9, 8, 7};

    DoublyLinkedList list8 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
    Investigate("List8\n=====", list8);
    DoublyLinkedList list9 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
    Investigate("List9\n=====", list9);

    destroy(&list8);
    destroy(&list9);
}
int areEqual(DoublyLinkedList list1, DoublyLinkedList list2)
{
    int flag=0;
    Node*temp=list1.head;
    Node*temp1=list2.head;
    if(list1.head==NULL^list2.head==NULL)
        return 0;
    else if(list1.head==NULL&&list2.head==NULL)
        return 1;
    else if(length(list1)!=length(list2))
        return 0;
    else
    {
        while(temp!=NULL||temp1!=NULL)
        {
            if(temp->data==temp1->data)
                flag=1;
            else
                flag=0;

            temp=temp->next;
            temp1=temp1->next;

        }



        return flag;


    }




}

void testAreEqual()
{
    int array5[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array6[] = {7, 8, 9, 9, 8, 7};
    int array7[] = {0, 1, 2, 3, 4, 5};

    DoublyLinkedList list10 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
    Investigate("List10\n=====", list10);
    DoublyLinkedList list11 = convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
    Investigate("List11\n=====", list11);
    DoublyLinkedList list12 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("List12\n=====", list12);
    DoublyLinkedList emptyList1 = dup(EmptyList);
    Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList emptyList2 = dup(EmptyList);
    Investigate("EmptyList2 = dup(EmptyList)\n===========================", emptyList2);

    printf("areEqual(List10, List10) = %d\n", areEqual(list10, list10));
    printf("areEqual(List10, List11) = %d\n", areEqual(list10, list11));
    printf("areEqual(List10, List12) = %d\n", areEqual(list10, list12));
    printf("areEqual(List11, List10) = %d\n", areEqual(list11, list10));
    printf("areEqual(List10, EmptyList1) = %d\n", areEqual(list10, emptyList1));
    printf("areEqual(EmptyList1, List10) = %d\n", areEqual(emptyList1, list10));
    printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

    destroy(&list10);
    destroy(&list11);
    destroy(&list12);

}



void testConcatenate1(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;

    list3 = dup(list1);
    Investigate("List3 = dup(List1)\n==================", list3);
    emptyList1 = dup(EmptyList);
    Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList list5 = concatenate(list3,EmptyList);
    Investigate("List5 = List3<->EmptyList1\n==========================", list5);
    destroy(&list5);
    Investigate("List5 (after destroy)\n=====================", list5);
    //destroy(&list3);			//already destroyed when list5 got destroyed
    //destroy(&emptyList1);		//already destroyed when list5 got destroyed
}
/*
 *
 */
void testConcatenate2(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;
    list3 = dup(list1);
    emptyList1 = dup(EmptyList);
    DoublyLinkedList list6 = concatenate(emptyList1, list3);
    Investigate("List6 = EmptyList1<->List3\n==========================", list6);
    destroy(&list6);
    Investigate("List6 (after destroy)\n=====================", list6);
    //destroy(&list3);			//already destroyed when list6 got destroyed
    //destroy(&emptyList1);		//already destroyed when list6 got destroyed
}
/*
 *
 */
void testConcatenate3(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;

    list3 = dup(list1);
    list4 = dup(list2);
    DoublyLinkedList list7 = concatenate(list3, list4);
    Investigate("List7 = List3<->List4\n=====================", list7);
    destroy(&list7);
    Investigate("List7 (after destroy)\n=====================", list7);
    //destroy(&list3);			//already destroyed when list7 got destroyed
    //destroy(&list4);			//already destroyed when list7 got destroyed
}
/*
 *
 */
void testConcatenate()
{
    int array1[] = {0, 1, 2, 3, 4, 5, 6};
    int array2[] = {7, 8, 9};

    DoublyLinkedList list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
    Investigate("List1\n=====", list1);
    DoublyLinkedList list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
    Investigate("List2\n=====", list2);

    testConcatenate1(list1, list2);
    testConcatenate2(list1, list2);
    testConcatenate3(list1, list2);

    destroy(&list1);
    destroy(&list2);
}

main()
{
    testConcatenate();
    testPalindrome();
    testAreEqual();
    return 0;
}
