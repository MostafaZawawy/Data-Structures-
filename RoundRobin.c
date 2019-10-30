#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char name[5];
    int remaining_time;
    int bt;
} Process, *Item;
/*
 *
 */
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node* front;
    Node* rear;
} Queue;
/*
 *
 */
void init(Queue *q)
{
    q->front=NULL;
    q->rear=NULL;
    q->rear=malloc(sizeof(Node));
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->front==NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    Item x;
    if(isEmpty(q))
        return NULL;
    else
    {
        Node*temp=malloc(sizeof(Node));
        temp=q->front;
        x=temp->data;
        q->front=q->front->next;
        free(temp);
        return x;
    }

}
/*
 *
 */
void enqueue(Queue *q, Item val)
{
    if(q->front==NULL)
    {
        q->rear=malloc(sizeof(Node));
        q->rear->next=NULL;
        q->front=q->rear;
        q->front->data=val;
    }
    else
    {
        Node*temp;
        temp=malloc(sizeof(Node));
        temp->data=val;
        q->rear->next=temp;
        temp->next=NULL;
        q->rear=temp;
    }
}

/*
 *
 */
void destroy(Queue *q)
{
    Node*temp;

    while(q->front!=NULL)
    {
        temp=q->front;
        q->front=q->front->next;
        free(temp);
    }
    q->rear=NULL;
}

/*
 * RoundRobin Scheduling
 */
//FUNCTION TO CHECK THE BIRTHTIME
void checkEnterTime(Process p[], Queue *q,int x,int NoOfprocesses)
{  FILE*f;
    int i=0;
    for(i=0 ; i < NoOfprocesses ; i++ )
    {        if(p[i].bt == x)
            enqueue(q,&p[i]);

    }


}
void checkquantum(Item k, Queue * q)
{
    if(k->remaining_time == 0)
        printf("%s halts",k->name);
    else
        enqueue(q,k);
}

void RoundRobin(char* filename)
{
    int x;
    int i=0;
    Process p[20] ;
    Queue q;
    init(&q);
    FILE *f ;

    f=fopen("RoundRobin.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%s %d %d",p[i].name,&p[i].bt, &p[i].remaining_time);
        i++;
    }
    fclose(f);
 checkEnterTime(p,&q,0,i);
 //as the file is sorted we can get the max time from the last processes.
 int EndOFTime=p[i-1].remaining_time+p[i-1].bt;
for(x=0 ; x < EndOFTime; x++)
    { if(isEmpty(&q))
        {printf("idle\t(%d-->%d)\n",x,x+1);
            checkEnterTime(p, &q, x+1,i);
            }
        else
        {
            Item n = dequeue(&q);
            printf("%s\t(%d-->%d)",n->name, x, x+1);
            n->remaining_time--;

            checkEnterTime(p, &q, x+1,i);
            checkquantum(n, &q);
            printf("\n");
        }
    }
    printf("Stop");
}
/*
 *
 */
int main(int argc, char**argv)
{

    if(argc!=2) {
    	printf("Usage: %s filename\n", argv[0]);
    	exit(1);
    }
    RoundRobin(argv[2]);

       return 0;
}

