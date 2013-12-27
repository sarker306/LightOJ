#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROW 201
#define COL 101

long lcs[35][35];
char first[35], second[35];
long long sss[35][35][70];
char vis[35][35][70];

long long findSSS(int x, int y, int len){
	long long res = 0;
	
	if ( len == 0 ) return (first[x] == 0 && second[y] == 0);
	if ( vis[x][y][len] == 1 ) return sss[x][y][len];
	
/*	printf("%d %d %d\n", x, y, len);*/
	vis[x][y][len] = 1;
	if ( first[x] && first[x] == second[y] ) res += findSSS(x + 1, y + 1, len - 1);
	else{
		if ( first[x] ) res += findSSS(x + 1, y, len - 1);
		if ( second[y] ) res += findSSS(x, y + 1, len - 1);
	}
	
	return sss[x][y][len] = res;
}

void calcLCS(char *f, char *s){
    int i, j;
    
    for ( i = 0 ; f[i] ; i++ ) lcs[i][0] = 0;
    for ( j = 0 ; s[j] ; j++ ) lcs[0][j] = 0;
    
    for ( i = 1 ; f[i] ; i++)
        for ( j = 1 ; s[j] ; j++ ){
            if ( f[i] == s[j] ){
                lcs[i][j] = lcs[i-1][j-1] + 1;
            }
            else if ( lcs[i-1][j] > lcs[i][j-1] ){
                lcs[i][j] = lcs[i-1][j];
            }
            else{
                lcs[i][j] = lcs[i][j-1];
            }
        }
    
    memset(vis, 0, sizeof(vis));
    printf("%d %lld\n", i + j - 2 - lcs[i-1][j-1], findSSS(1, 1, i + j - 2 - lcs[i-1][j-1]));
}

int main(){
    int test, kase;
    first[0] = second[0] = ':';
    
    while (scanf("%d", &test) == 1){
    	getchar();
        for ( kase = 1 ; kase <= test ; kase++ ){
            gets(first + 1);
            gets(second + 1);
            printf("Case #%d: ", kase);
            calcLCS(first, second);
        }
    }
    
    return 0;
}

