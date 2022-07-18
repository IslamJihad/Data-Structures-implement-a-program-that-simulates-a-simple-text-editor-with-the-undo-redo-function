/*
Islam Jihad Joma
1191375
section 3
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100
//struct node
typedef struct node* PtrToNode;
typedef PtrToNode Stack;
struct node
{
    char array[size];
    PtrToNode Next;
};

int IsEmpty( Stack S );
Stack CreateStack( );
void MakeEmpty( Stack S );
Stack CreateStack( );
void Pop( Stack S );
char *Top( Stack S );
void Push( char X[], Stack S );
void DisposeStack( Stack S );
void undo(Stack RandU, Stack s);
void redo(Stack RandU, Stack s);
Stack print(Stack s, int counter);
Stack save(Stack s,int counter);
void quit(Stack s, int counter);

int main()
{
    char x[size] ; //here I Identify an array to savve every input in it before using it
    Stack s=CreateStack();
    Stack RandU=CreateStack(); // this stack so save the undo or redo operation


    int counter=0; // to know how much nodes we have

    do
    {
        printf("MyCommand > ");
        gets(x);
        if(strcmp(x,"undo")==0)
        {
            undo(RandU, s); //the undo function to make a pop for the stack
            counter--;
            s= print(s, counter); // and print the output emediatly, I made the print function to return the original stack too
        }
        else if(strcmp(x,"redo")==0)
        {
            redo(RandU, s); // this function is to redo the last line wrote by making push for the original stack
            counter++;
            s= print(s, counter);
        }
        else if(strcmp(x,"print")==0)
        {
            s= print(s, counter);
        }
        else if(strcmp(x,"save")==0)
        {
            s= save( s, counter); // to save in file
        }
        else if(strcmp(x,"quit")==0)
        {
            quit( s, counter);
            DisposeStack(s); //to make the stack empty after finishing the program
            break;
        }
        else
        {
            Push(x,s); //else those input the input will be saved as sentences
            counter++;
        }


    }
    while(1);

    return 0;
}

void undo(Stack RandU, Stack s)
{
// make push on the RandU that save the operations and pop up s stack
    Push(Top(s), RandU);
    Pop(s);

}

void redo(Stack RandU, Stack s)
{
// make push on the s from the saved sentences from the RandU and pop up then push in s stack

    Push(Top(RandU), s);
    Pop(RandU);

}

Stack print(Stack s,int counter)
{
    // I made 2 stack one to save the original stack the seconed to reverse them so I can print it normaly
    Stack temp1= CreateStack();
    Stack temp2= CreateStack();

    for(int i=0; i<counter; i++)
    {
        Push(Top(s), temp1);
        Push(Top(s), temp2);
        Pop(s);
    }
// printing rusults by top & pop from the first stack
    printf("result >\n");
    for(int i=0; i<counter; i++)
    {
        printf("%s\n",Top(temp1));
        Pop(temp1);
    }
    //reversing to normal stack
    for(int i=0; i<counter; i++)
    {
        Push(Top(temp2), s);
        Pop(temp2);
    }
    return s;

}

Stack save(Stack s,int counter)
{
    FILE *f= fopen("output.txt","w");
/* I did the same to print the data on the file normaly not reversed so i needed 2 for loops
one to reverse the reversed and one to print*/

    Stack temp1= CreateStack();
    Stack temp2= CreateStack();

    for(int i=0; i<counter; i++)
    {
        Push(Top(s), temp1);
        Push(Top(s), temp2);
        Pop(s);
    }

    for(int i=0; i<counter; i++)
    {
        fprintf(f, "%s\n", Top(temp1));
        Pop(temp1);
    }
    fclose(f);
    for(int i=0; i<counter; i++)
    {
        Push(Top(temp2), s);
        Pop(temp2);
    }
    return s;
}

void quit(Stack s, int counter)
{
    /* the quit will save the results in the file and as the previos function  but without to return the
    original stack as we finished using the code so we only save data*/
    printf("result > Good Bye!");
    FILE *f= fopen("output.txt","w");


    Stack temp_save= CreateStack();

    for(int i=0; i<counter; i++)
    {
        Push(Top(s), temp_save);
        Pop(s);
    }

    for(int i=0; i<counter; i++)
    {
        fprintf(f, "%s\n", Top(temp_save));
        Pop(temp_save);
    }
    fclose(f);
}







// those are the functions of the stack, I didne't use them all but used what I needed in the code
int IsEmpty( Stack S )
{
    return S->Next == NULL;
}

Stack CreateStack( )
{
    Stack S;
    S = (Stack)malloc( sizeof( struct node ) );
    if( S == NULL )
        printf( "Out of space!" );
    S->Next = NULL;
    return S;
}

void MakeEmpty( Stack S )
{
    if( S == NULL )
        printf( "Out of space!" );
    else
        while( !IsEmpty( S ))
            Pop( S );
}

void Pop( Stack S )
{
    PtrToNode firstCell;
    if( IsEmpty( S ) )
        printf( "Empty stack" );
    else
    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free( firstCell );
    }
}

char *Top( Stack S )
{
    if( !IsEmpty( S ) )
        return S->Next->array;
    printf( "Empty stack");
    return 0;
}


void Push( char X[], Stack S )
{

    PtrToNode temp;
    temp = ( Stack )malloc( sizeof( struct node ) );
    if( temp == NULL)
        printf( "Out of space!" );
    else
    {
        strcpy(temp->array,X);
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack( Stack S )
{
    MakeEmpty( S );
    free( S );
}
