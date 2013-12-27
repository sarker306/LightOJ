#include <stdio.h>

typedef unsigned long long ull;

ull factorial[21];
int occurance[26];
char word[21], nthWord[21];

ull numberPermutations(){
    ull val = 1;
    int i, x;
    
    for ( i = 0, x = 0 ; i < 26 ; i++ ){
        x += occurance[i];
        val *= factorial[occurance[i]];
    }
    
    return factorial[x]/val;
}
    
void initFactorial(){
    int i;
    
    factorial[0] = 1;
    for ( i = 1 ; i < 21 ; i++ )
        factorial[i] = factorial[i-1] * i;
}

void formNthWord(int index, ull n){
    int i;
    ull temp;
    
    if ( word[index] == 0 ){
        nthWord[index] = 0;
        puts(nthWord);
        return;
    }
    
    for ( i = 0 ; i < 26 ; i++ ){
        if ( occurance[i] > 0 ){
            occurance[i]--;
            if ( ( temp = numberPermutations() ) < n )
                occurance[i]++, n -= temp;
            else{
                nthWord[index] = i + 'a';
                formNthWord(index + 1, n);
            }
        }
    }       
}

int main(){
    int test, kase, i;
    ull n;
    
    initFactorial();
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            for ( i = 0 ; i < 26 ; i++ ) occurance[i] = 0;
            scanf("%s%llu", word, &n);
            for ( i = 0 ; word[i] ; i++ ) occurance[word[i]-'a']++;
            printf("Case %d: ", kase);
            if ( numberPermutations() < n ) puts("Impossible");
            else formNthWord(0, n);
        }
    }
    
    return 0;
}
