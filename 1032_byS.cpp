#include<stdio.h>
#include<iostream>
//#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<string>
using namespace std;
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
int N,LEN;
int power2[31], numfrac[32], num[31];
long long dp[32][2][2];
bool vis[32][2][2];
int swap(int &x, int &y)
{
    int z = x;
    x = y;
    y = z;
}
void generate()
{
    int n = N,i=0,j;
    while(n)
    {
        num[i++] = n%2;
        n /= 2;
    }
    LEN = i--;
    for (j=0; j<i; ++j, --i) swap(num[i],num[j]);
    numfrac[LEN] = 0;
    for (j=0, i=LEN-1; j<LEN; ++j,--i)
    {
        if (num[i]) numfrac[i] = numfrac[i+1] | (1<<j);
        else numfrac[i] = numfrac[i+1];
    }
}
int rec1(int pos, int eq)
{
    if (!eq) return power2[LEN-pos];
    return numfrac[pos]+1;
}
long long rec2(int pos, int last, int eq)
{
    if (pos==LEN) return 0;
    if (vis[pos][last][eq]) return dp[pos][last][eq];
    vis[pos][last][eq] = true;
    long long ret = rec2(pos+1, 0, MINI(eq, !num[pos]));
    if (!eq || num[pos])
    {
        if (last) ret += rec1(pos+1, eq) + rec2(pos+1, 1, eq);
        else ret += rec2(pos+1, 1, eq);
    }
    return dp[pos][last][eq] = ret;
}
int main()
{
    int t,T;
    int i;
    long long ans;
    scanf("%d", &T);
    power2[0] = 1;
    for (i=1; i<32; ++i) power2[i] = power2[i-1]<<1;
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        generate();
        memset(vis, false, sizeof(vis));
        ans = rec2(0,0,1);
        printf("Case %d: %lld\n", t, ans);
    }
    return 0;
}
