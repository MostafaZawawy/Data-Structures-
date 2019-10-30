#include <stdio.h>
#include <stdlib.h>
#define maxsize 1000
#include<string.h>
#include<ctype.h>
#include<math.h>
typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */

typedef struct
{
    int top;
    Item*item;
} Stack;
/*
 *
 */

void init(Stack *s)
{

    Item*arrItems=(Item*)malloc(sizeof(Item)*maxsize);
    s->item=arrItems;
    s->top=-1;

}
/*
 *
 */
int isEmpty(Stack *s)
{

    if(s->top==-1)
        return 1;
    else
        return 0;

}
/*
 *
 */

/*
 *
 */


Item pop(Stack *s)
{
    Item temp;
    temp.fData=-1;

    if(s->top==-1)
        return temp;
    return s->item[s->top--];
}
/*
 *
 */
Item top(Stack *s)
{
    Item temp;
    temp.fData=-1;
    if(s->top==-1)
        return temp;
    else
        return s->item[s->top];

}

int Full(Stack*s)
{

    if((s->top)>=maxsize)
        return 1;
    else
        0;

}
void push(Stack *s, Item val)
{
    if((s->top)<1000)
    {
        s->top=s->top+1;
        s->item[s->top]=val;
    }
    else
        printf("stack is Full !");

}
/*
 *
 */
void destroy(Stack *s)
{
    free(s->item);
    s->item=NULL;
    s->top=-1;

}


int Token()
{
    char str[80] = "( 3 + 4 ) ^ 5";
    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while( token != NULL )
    {
        printf( " %s\n", token );

        token = strtok(NULL, s);
    }

    return(0);
}


/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)4 --> 23+4

 */
int priority(char x)
{

    if(x=='(')
        return 0;
    if(x=='+'||x=='-')
        return 1;
    if(x=='*'||x=='/'||x=='.')
        return 2;

}
void clear(char*p){
 free(p);
 p=NULL;
 }

void infixToPostfix(char* infix, char* postfix)
{  //clear(postfix);
    Stack s;
    init(&s);
    Item temp;
    char*temp1=infix;
    char*temp2=postfix;

    while(*infix!='\0')
    {

        if(isalnum(*infix))
        {
            *(postfix++)=*infix;

        }
        else if(*infix=='(')
        {
            temp.cpData='(';
            push(&s,temp);

        }
        else if(*infix==')')
        {
            while((temp.cpData=pop(&s).cpData)!='(')
                *(postfix++)=*temp.cpData;
        }
        else if(isEmpty(&s)||top(&s).cpData=='(')
        {
            temp.cpData=infix;
            push(&s,temp);
        }


        else
        {
            while(priority((char)top(&s).cpData)>=priority(*infix))
                *(postfix++)=*pop(&s).cpData;
            temp.cpData=infix;
            push(&s,temp);
        }
        infix++;
    }


    while(s.top!=-1)
    {
        *(postfix++)=*pop(&s).cpData;
    }
    postfix=temp2;
    destroy(&s);
}


//}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float operation(float x, float y,char c)
{
    if(c=='+')
        return y+x;
    if(c=='-')
        return y-x;
        if(c=='/')
        return y/x;
    if(c=='*')
        return x*y;
    if(c=='^')
        return powf(x,y);
        if(c=='.')
        return y+0.1*x;

}

float evaluatePostfix(char* postfix)
{
    Item result;
    Stack s;
    init(&s);
    Item temp;
    Item temp2;
    temp2.fData=0;
    temp.fData=0;
    float temp3,temp4;
    char c;

int i=0;
    for(i;i<strlen(postfix);i++)
    {
        if(isdigit(postfix[i]))
        {
            postfix[i]=postfix[i]-'0';
            temp.fData=postfix[i];
            push(&s,temp);
        }
       else if(postfix[i]=='*'||postfix[i]=='-'||postfix[i]=='+'||postfix[i]=='^'||postfix[i]== '/'||postfix[i]=='.')
        {
            temp3=pop(&s).fData;
            temp4=pop(&s).fData;
            temp2.fData=operation(temp3,temp4,postfix[i]);
            push(&s,temp2);


        }
    }
    clear(postfix);

    result=pop(&s);
    destroy(&s);
    return result.fData;

}

/*
 *
 */

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");

    }

    return 0;
}
