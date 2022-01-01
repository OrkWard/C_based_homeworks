#define MAXN 1000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXN];

SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName Root1, SetName Root2);