#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define SIZE 100000
#define RANGE 1429431
int TREE[4194299], array[SIZE+3];
vector <int> V;
void initialize(int node, int left, int right)
{
    if (left==right)
    {
        if (left&1) TREE[node] = 1;
        return;
    }
    int mid = (left+right)>>1;
    initialize(node<<1, left, mid);
    initialize((node<<1)+1, mid+1, right);
    TREE[node] = TREE[node<<1] + TREE[(node<<1) + 1];
}
int findNext(int node, int left, int right, int A, int last)
{
    if (left==right) return left;
    int mid = (left+right)>>1;
    if (last<mid && TREE[node<<1]>A) return findNext(node<<1, left, mid, A, last);
    return findNext((node<<1)+1, mid+1, right, A-TREE[node<<1], last);
}
int query(int node, int left, int right, int indx)
{
    if (left==right) return left;
    int mid = (left+right)>>1;
    if (TREE[node<<1]>=indx) return query(node<<1, left, mid, indx);
    return query((node<<1)+1, mid+1, right, indx-TREE[node<<1]);
}
void prepVec(int indx)
{
    V.clear();
    int x,i;
    for (i=indx; i <= RANGE && i<=TREE[1]; i += indx)
    {
        x = query(1, 1, RANGE, i);
        V.push_back(x);
    }
}
void update(int node, int left, int right, int indx)
{
    if (left <= indx && indx <= right) --TREE[node];
    else return;
    if (left==right) return;
    int mid = (left+right)>>1;
    if (indx<=mid) update(node<<1, left, mid, indx);
    else update((node<<1)+1, mid+1, right, indx);
}
void calculate()
{
    initialize(1, 1, RANGE);
    array[1] = 1;
    int A, indx, i;
    for (A=2; A<=SIZE; ++A)
    {
        indx = findNext(1, 1, RANGE, A-1, array[A-1]);
        array[A] = indx;
        prepVec(indx);
        for (i=0; i<V.size(); ++i) update(1, 1, RANGE, V[i]);
    }
}
int main()
{
    int t,T,N;
    calculate();
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        printf("Case %d: %d\n", t, array[N]);
    }
    return 0;
}
