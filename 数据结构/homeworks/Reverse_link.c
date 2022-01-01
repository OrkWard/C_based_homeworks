#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Reverse(List L){
    PtrToNode head, p1, p2, new;
    head = L;

    if (L->Next == NULL){
        return head;
    }

    p1 = L->Next;
    p2 = p1->Next;
    new = p1;
    new->Next = NULL;

    while (p2 != NULL){
        p1 = p2;
        p2 = p2->Next;
        p1->Next = new;
        new = p1;
    }

    head->Next = new;
    return head;
}