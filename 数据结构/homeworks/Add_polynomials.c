#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

Polynomial Add( Polynomial a, Polynomial b){
    Polynomial pa, pb, new, head;
    pa = a, pb = b;
    new = (Polynomial)malloc(sizeof(struct Node));
    new->Next = NULL;
    head = new;

    while(pa != NULL && pb != NULL){
        if (pa->Exponent > pb->Exponent){
            new->Next = pa;
            pa = pa->Next;
            new = new->Next;
            new->Next = NULL;
        }
        else if (pa->Exponent < pb->Exponent){
            new->Next = pb;
            pb = pb->Next;
            new = new->Next;
            new->Next = NULL;
        }
        else {
            if (pa->Coefficient + pb->Coefficient != 0){
               new->Next = (Polynomial)malloc(sizeof(struct Node));
                new = new->Next;
                new->Coefficient = pa->Coefficient + pb->Coefficient;
                new->Exponent = pa->Exponent;
                new->Next = NULL;
            }
            pa = pa->Next;
            pb = pb->Next;
        }
    }

    if (pa == NULL && pb != NULL){
        while(pb != NULL){
            new->Next = pb;
            pb = pb->Next;
            new = new->Next;
            new->Next = NULL;
        }

        return head;
    }
    else if (pa != NULL && pb == NULL){
        while(pa != NULL){
            new->Next = pa;
            pa = pa->Next;
            new = new->Next;
            new->Next = NULL;
        }

        return head;
    }
    else{
        return head;
    }
}