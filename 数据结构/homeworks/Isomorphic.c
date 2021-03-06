#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic(Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */
int Isomorphic(Tree T1, Tree T2 ){
    if (T1 && T2){
        if (T1->Element != T2->Element){
            return 0;
        }
        else {
            if (Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Right, T2->Right) ||
                Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left)){
                    return 1;
                }
            else 
                return 0;
        }
    }
    else if (!T1 && !T2){
        return 1;
    }
    else
        return 0;
}