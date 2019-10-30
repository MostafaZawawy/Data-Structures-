#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<assert.h>
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
typedef struct node
{
    struct node*left;
    struct node*right;
    char*data;
} node;

node*InitializeNode(char*str)
{
    node*n= malloc(sizeof(node));
    n->data=malloc(sizeof(char)*30);
    strcpy(n->data,str);
    n->left=NULL;
    n->right=NULL;
    return n;
}
int size(node* root)
{
    return(root==NULL)?0:1+size(root->left)+size(root->right);

}
node* successor(node*root,node*node)
{
    struct node* temp;
    if(node->right!=NULL)
    {
        temp=node->right;

        while(temp->left!=NULL)
            temp=temp->left;

        return temp;
    }
    else
    {
        struct node*ancestor=root;
        struct node*successor=NULL;
        while(ancestor!=node)
        {
            if(strcmp(node->data,ancestor->data)<0)
            {
                successor=ancestor;
                ancestor=ancestor->left;
            }
            else
                ancestor=ancestor->right;
        }
        return (successor==NULL)?node:successor;
    }
}
int height(node*root)
{
    return(root==NULL)?-1:1+max(height(root->right),height(root->left));
}
node*predecessor(node*root,node*node)
{
    struct node* temp;
    if(node->left!=NULL)
    {
        temp=node->left;

        while(temp->right!=NULL)
            temp=temp->right;

        return temp;
    }
    else
    {
        struct node*ancestor=root;
        struct node*predeccessor=NULL;

        while(ancestor!=node)
        {
            if(strcmp(node->data,ancestor->data)>0)
            {
                predeccessor=ancestor;
                ancestor=ancestor->right;
            }
            else
                ancestor=ancestor->left;

        }

        return (predeccessor==NULL)?node:predeccessor;

    }


}
void search(node*root,char*str)
{
    struct node*temp;
    temp=root;

    while(root!=NULL)
    {
        if(strcmp(root->data,str)==0){
            printf("CORRECT\n");
            break;
            }

        else if(strcmp(root->data,str)>0){
            if(root->left!=NULL)
            root=root->left;
            else {
                 printf("%s,",root->data);
            printf("%s,",successor(temp,root)->data);
            printf("%s\n",predecessor(temp,root)->data);
                break;
            }
            }
        else{
          if(root->right!=NULL)
            root=root->right;
         else{
             printf("%s,",root->data);
            printf("%s,",successor(temp,root)->data);
            printf("%s\n",predecessor(temp,root)->data);
            break;        }
         }
        if(isLeaf(root)&&strcasecmp(root->data,str)!=0)
        {
            printf("%s,",root->data);
            printf("%s,",successor(temp,root)->data);
            printf("%s\n",predecessor(temp,root)->data);
            break;
        }
    }
}
int isLeaf(node*node)
{

assert(node!=NULL);
        return node->left==NULL&&node->right==NULL;
}
void insert(node** root,char*str)
{

    if(*root==NULL)
    {
        *root=InitializeNode(str);
    }
    else if(strcmp(str,(*root)->data)<0)
    {
        insert(&(*root)->left,str);
    }
    else if(strcmp(str,(*root)->data)>0)
    {
        insert(&(*root)->right,str);
    }

}

int main()
{
    char*s;
    char*x;
    const char c[2] = " ";
    char*filename;
    filename=malloc(sizeof(char)*20);
    char *token;
    token=malloc(sizeof(char)*30);

    s=malloc(sizeof(char)*40);
    x=malloc(sizeof(char)*100);
   printf("Please enter file name:");

   fgets(filename,40,stdin);
 printf("-----------------------\n");
    if ((strlen(filename) > 0) && (filename[strlen (filename) - 1] == '\n'))
        filename[strlen (filename) - 1] = '\0';

    FILE*f=fopen(filename,"r");

    node*root;
    root=NULL;

    if(f==NULL)
    {
        exit(1);
    }
    while(!feof(f))
    {
        fscanf(f,"%s",s);
        insert(&root,s);
    }
    fclose(f);

    printf("Tree Size equals %d\n",size(root));
    printf("Tree height is %d\n",height(root));
    printf("-----------------------\n");
    printf("Please enter a word:");
    fgets(x,256,stdin);
    if ((strlen(x) > 0) && (x[strlen (x) - 1] == '\n'))
        x[strlen (x) - 1] = '\0';


    token = strtok(x,c);


    while( token != NULL )
      { printf("\n%s-",token);
          search(root,token);
           token = strtok(NULL, c);
      }
}
