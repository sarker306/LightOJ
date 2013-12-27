/*
  Name: Sudoku solver
  Copyright: None
  Author: Me
  Date: 17/08/09 18:32
  Description: Solves sudoku using brute force.
*/
#include <stdio.h>
#include<stdlib.h>

typedef struct{
    int r, c, candi, number[10];
}pos;
pos position[82];
char grid[9][9];
char gridCandidates[9][9][10];
int boxsize;
int rowsize;
int unfilled;

char variant='C';
int nsol;
void printSolution(void);
void printState(void);
void printMarks();
int safe(int row, int col, int n, int solving);
void solve(int, int);
int input(void);
int checkValidity(void);
void precalc(void);
int cmp(const void* a, const void *b);
int SolveUsingRule();
void initCandidateList();

int main(){
	char ch;
	int i, j, test, kase;
	
	while(scanf("%d", &test) == 1){
    	for ( kase = 1 ; kase <= test ; kase++ ) {
    	    if(!input()) break;
    	    printf("Case %d:\n", kase);
    	    
    	    initCandidateList();
    	    if(!checkValidity()) printf("NO SOLUTION\n");
    	    else{
    	       while ( SolveUsingRule() );
    	        /*printMarks();*/
    	        printState();
    	        printf("Faaka %d\n", unfilled);
        	    nsol=0;
        		precalc();
        		
        		switch (nsol) {
                    case 0: printf("NO SOLUTION\n"); break;
                }
            }
    	}
    }
	
    return 0;
}

int cmp(const void *a, const void *b){
    return ((pos*)a)->candi-((pos*)b)->candi;
}

int input(){
    int i, j;
    char ch;
    
    unfilled = 0;
    boxsize = 3;
    rowsize=boxsize*boxsize;
    for(i=0;i<rowsize;i++)
    for(j=0;j<rowsize;){
		if(scanf("%c",&ch)==EOF) return 0;
    	if (ch>='0'&&ch<=(rowsize+'0')||ch=='.'){
			if (ch=='.'){
                ch='0';
                unfilled++;
            }
			grid[i][j++]=ch;
		}
    }
    
    return 1;
}

int checkValidity(){
    int i, j, k=0;
    
    for(i = 0; i < rowsize; i++ ){
        for( j = 0; j < rowsize; j++ ){
            if(grid[i][j] != '0')
            if(!safe( i, j, grid[i][j] - '0', 0)){
                return 0;
            }
        }
    }
    
    return 1;
}

void printMarks(void){
    int r, c, n;
    
    for ( r = 0 ; r < 9 ; r++ ){
        for ( c = 0 ; c < 9 ; c++ ){
            if ( c ) putchar(' ');
            if ( grid[r][c] == '0' ){
                putchar('{');
                for ( n = 1 ; n <= 9 ; n++ )
                    if ( gridCandidates[r][c][n] ) putchar(n + '0');
                
                putchar('}');
            }
            else putchar(grid[r][c]);
        }
        
        putchar('\n');
    }
}

void printState(void){
    int r, c;

    printf("\n\n-----   state    -----\n");
    for (r = 0; r < rowsize; r++){
		printf("     ");
		for (c = 0; c < rowsize; c++){
		    printf("%c", (grid[r][c]=='0')?'.':grid[r][c]);
		    if (c % boxsize == 2)
			printf("  ");
		}
		printf("\n");
		if (r % boxsize == boxsize-1) printf("\n");
    }
    
    return;
}

void printSolution(void){
    int r, c;
    
    nsol++;
    
    for (r = 0; r < rowsize; r++){
		for (c = 0; c < rowsize; c++){
		    printf("%c", grid[r][c]);
		}
		printf("\n");
    }
    return;
}

void printCandidates( int row, int col ){
    int n, index = row * rowsize + col;
    
    printf("-> %d %d :", row, col);
    for ( n = 1 ; n <= rowsize ; n++ )
        if ( position[index].number[n] ) printf(" %d",n);
    puts("");
}

void initCandidateList(){
    int i, j, n;
    
    for ( i = 0 ; i < 9 ; i++ )
        for ( j = 0 ; j < 9 ; j++ )
            for ( n = 1 ; n <= 9 ; n++ )
                gridCandidates[i][j][n] = -1;
                
    for ( i = 0 ; i < 9 ; i++ )
        for ( j = 0 ; j < 9 ; j++ ){
            if ( grid[i][j] == '0' )
                for ( n = 1 ; n <= 9 ; n++ ){
                    gridCandidates[i][j][n] = safe(i, j, n, 0);
                }
            else{
                for ( n = 1 ; n <= 9 ; n++ ) 
                    gridCandidates[i][j][n] = 0;
                gridCandidates[i][j][grid[i][j]-'0'] = 1;
            }
        }
}

void precalc(void){
    int i, j, k=0, n;
    
    for ( i = 0 ; i < rowsize ; i++ ){
        for ( j = 0 ; j < rowsize ; j++){
            position[k].r=i, position[k].c=j, position[k].candi=0;
            for ( n = 1 ; n <= rowsize ; n++ ){
                if(safe(i, j, n, 1)){
                    position[k].number[n] = 1;
                    position[k].candi++;
                }
                else position[k].number[n] = 0;
            }
            k++;
        }
    }
    
    for ( i = 0, n = 100 ; i < rowsize * rowsize ; i++ )
        if ( '0' == grid[position[i].r][position[i].c] && n > position[i].candi )
            n = position[i].candi, j = i;
    
    solve(position[j].r, position[j].c);
}

int safe(int row, int col, int n, int solving){
    int r, c, d, br, bc;
    
    n += '0';
    if (solving && grid[row][col] == n) return 1;
    if (solving && grid[row][col] != '0') return 0;
    for (c = 0; c < rowsize; c++)
	if (c!=col && grid[row][c] == n) return 0;
    for (r = 0; r < rowsize; r++)
	if (r!=row && grid[r][col] == n) return 0;
    br = row / boxsize;
    bc = col / boxsize;
    for (r = br * boxsize; r < (br + 1) * boxsize; r++)
	for (c = bc * boxsize; c < (bc + 1) * boxsize; c++)
	    if (r!=row && c!=col && grid[r][c] == n) return 0;
    return 1;
}

void solve(int row, int col){
    int n, t, i, flag, index = row * rowsize + col;
    int temp[3][10], tmp2[3][10], br, bc, r, c, x, y;
    int flag1, flag2, flag3;
    
    if (unfilled == 0){
        nsol++;
	    printSolution();
	    return;
    }
	
    else if(nsol<1){
        /*printCandidates(row, col);
        printState();*/
        /*getchar();*/
        
    	for (n = 1; n <= rowsize && nsol < 1; n++){
    	    if (position[index].number[n]){
                printf("  %d %d, %d?\n", row, col, n);
    			t = grid[row][col];
    			flag = 1;
    			
    			x = 100;
    			
    			for ( c = 0 ; c < rowsize ; c++ ){
                    temp[0][c] = position[row * rowsize + c].number[n];
                    tmp2[0][c] = position[row * rowsize + c].candi;
                }
                
    			for ( r = 0 ; r < rowsize ; r++ ){
                    temp[1][r] = position[r * rowsize + col].number[n];
                    tmp2[1][r] = position[r * rowsize + col].candi;
                }
                
                br = row / boxsize;
                bc = col / boxsize;
                for (r = br * boxsize, i = 0 ; r < (br + 1) * boxsize; r++)
            	for (c = bc * boxsize ; c < (bc + 1) * boxsize; c++, i++){
            	    temp[2][i] = position[r * rowsize + c].number[n];
            	    tmp2[2][i] = position[r * rowsize + c].candi;
                }
            	
            	flag1 = flag2 = flag3 = 1;
    			for ( i = 0 ; i < rowsize ; i++ ){
                    if ( grid[row][i] == '0' && position[row * rowsize + i].candi ){
                        if ( i == col || position[row * rowsize + i].number[n] == 0 ) continue;
                        position[row * rowsize + i].number[n] = 0;
                        position[row * rowsize + i].candi--;
                        if ( position[row * rowsize + i].candi == 0 ) flag1 = 0;
                        else if ( x > position[row * rowsize + i].candi )
                            x = position[row * rowsize + i].candi, y = row * rowsize + i;
            	        printf("%d %d, posibility of %d null\n", row, i, n);
                    }
                }
                
    			for ( i = 0 ; i < rowsize ; i++ ){
                    if ( grid[i][col] == '0' && position[i * rowsize + col].candi ){
                        if ( i == row || position[i * rowsize + col].number[n] == 0 ) continue;
                        position[i * rowsize + col].number[n] = 0;
                        position[i * rowsize + col].candi--;
                        if ( position[i * rowsize + col].candi == 0 ) flag2 = 0;
                        else if ( x > position[i * rowsize + col].candi )
                            x = position[i * rowsize + col].candi, y = i * rowsize + col;
            	        printf("%d %d, posibility of %d null\n", i, col, n);
                    }
                }
                
                br = row / boxsize;
                bc = col / boxsize;
                for (r = br * boxsize, i = 0 ; r < (br + 1) * boxsize; r++)
            	for (c = bc * boxsize ; c < (bc + 1) * boxsize; c++, i++){
                    if ( grid[r][c] == '0' && position[r * rowsize + c].candi ){
                        if ( ( r == row && c == col ) || position[r * rowsize + c].number[n] == 0 ) continue;
            	        position[r * rowsize + c].number[n] = 0;
            	        position[r * rowsize + c].candi--;
            	        if ( position[r * rowsize + c].candi == 0 ) flag3 = 0;
                        else if ( x > position[r * rowsize + c].candi )
                            x = position[r * rowsize + c].candi, y = r * rowsize + c;
            	        printf("%d %d, posibility of %d null\n", r, c, n);
                    }
                }
            	
            	puts("");
            	flag = flag1 & flag2 & flag3;
            	if ( flag ){
                    
                    /*for ( i = 1 ; i <= rowsize ; i++ )
                        if ( i != n ) position[index].number[i] = 0;*/
                    
        			grid[row][col] = n+'0';
        			
                    for ( i = 0 ; i < rowsize * rowsize ; i++ )
                        if ( grid[position[i].r][position[i].c] == '0' && x > position[i].candi ) x = position[i].candi, y = i;
                    
                    if ( unfilled ){
                        unfilled--;
                        if ( unfilled == 0 ){
                            printf("Solution found:\n");
                            nsol++;
                            printSolution();
                        }
                        else solve(position[y].r, position[y].c);
                        unfilled++;
                    }
                    else printf("No candidate in %d,%d\n", position[y].r, position[y].c);
                }
    			
    			printf("Back to %d, %d with %d\n", row, col, n);
    			grid[row][col] = t;
    			for ( i = 0 ; i < rowsize ; i++ ){
                    position[row * rowsize + i].candi = tmp2[0][i];
                    position[row * rowsize + i].number[n] = temp[0][i];
                }
                
    			for ( i = 0 ; i < rowsize ; i++ ){
                    position[i * rowsize + col].candi = tmp2[1][i];
                    position[i * rowsize + col].number[n] = temp[1][i];
                }
                
                br = row / boxsize;
                bc = col / boxsize;
                for (r = br * boxsize, i = 0 ; r < (br + 1) * boxsize; r++)
            	for (c = bc * boxsize ; c < (bc + 1) * boxsize; c++, i++){
                    position[r * rowsize + c].candi = tmp2[2][i];
            	    position[r * rowsize + c].number[n] = temp[2][i];
                }
    	    }
        }
    }
    
	return;
}

void removeCandidate( int row, int col, int n ){
    int i, br, bc, r, c;
    
    for ( i = 0 ; i < 9 ; i++ )
        if ( col != i ) gridCandidates[row][i][n] = 0;
    for ( i = 0 ; i < 9 ; i++ )
        if ( row != i ) gridCandidates[i][col][n] = 0;
    
    br = row / 3, bc = col / 3;
    for ( r = br * 3 ; r < ( br + 1 ) * 3 ; r++ )
        for ( c = bc * 3 ; c < ( bc + 1 ) * 3 ; c++ )
            if ( c != col && r != row ) gridCandidates[r][c][n] = 0;
}

int nakedSingle(){
    int i, j, n, cnt, flag = 0;
    char configuration[10];
    
    /*printf("In naked single\n");*/
    for ( i = 0 ; i < 9 ; i++ ) 
        for ( j = 0 ; j < 9 ; j++ ){
            if ( grid[i][j] != '0' ) continue;
            for ( n = 1, cnt = 0; n <= 9 ; n++ ){
                configuration[n] = 0;
                configuration[n] = safe(i, j, n, 0);
                if ( configuration[n] ) cnt++;
            }
            
            if ( cnt == 1 ){
                for ( n = 1 ; n <= 9 ; n++ ) if ( configuration[n] == 1 ) break;
                grid[i][j] = n + '0';
                flag = 1;
                removeCandidate(i, j, n);
                unfilled--;
                /*printf("grid[%d][%d] = %d\n", i, j, n);*/
            }
        }
    
    return flag;
}

int hiddenSingle(){
    int i, j, n, flag = 0, r, c, br, bc;
    char configuration[10], blockConf[10], blockConf2[10];
    int boxFirstRow[] = { 0, 0, 0, 3, 3, 3, 6, 6, 6 };
    int boxFirstCol[] = { 0, 3, 6, 0, 3, 6, 0, 3, 6 };
    
    for ( i = 0 ; i < 9 ; i++ ){
        for ( n = 1 ; n <= 9 ; n++ ){
            configuration[n] = 0;
            for ( j = 0 ; j < 9 ; j++ ){
                blockConf[j] = 0;
                if ( grid[i][j] != '0' ) continue;
                blockConf[j] = safe(i, j, n, 0);
                configuration[n] += blockConf[j];
            }
            
            if ( configuration[n] == 1 ){
                for ( j = 0 ; j < 9 ; j++ ) if ( blockConf[j] == 1 ) break;
                grid[i][j] = n + '0';
                removeCandidate(i, j, n);
                flag = 1;
                unfilled--;
                /*printf("grid[%d][%d] = %d, hidden row\n", i, j, n);*/
            }
        }
    }
    
    for ( i = 0 ; i < 9 ; i++ ){
        for ( n = 1 ; n <= 9 ; n++ ){
            configuration[n] = 0;
            for ( j = 0 ; j < 9 ; j++ ){
                blockConf[j] = 0;
                if ( grid[j][i] != '0' ) continue;
                blockConf[j] = safe(j, i, n, 0);
                configuration[n] += blockConf[j];
            }
            
            if ( configuration[n] == 1 ){
                for ( j = 0 ; j < 9 ; j++ ) if ( blockConf[j] == 1 ) break;
                grid[j][i] = n + '0';
                flag = 1;
                removeCandidate(j, i, n);
                unfilled--;
                /*printf("grid[%d][%d] = %d, hidden col\n", j, i, n);*/
            }
        }
    }
    
    for ( i = 0 ; i < 9 ; i++ ){
        for ( n = 1 ; n <= 9 ; n++ ){
            configuration[n] = 0;
            br = boxFirstRow[i] / 3;
            bc = boxFirstCol[i] / 3;
            j = 0;
            for ( r = br * 3 ; r < ( br + 1 ) * 3 ; r++ )
            for ( c = bc * 3 ; c < ( bc + 1 ) * 3 ; c++, j++ ){
                blockConf[j] = 0;
                blockConf2[j] = r * 9 + c;
                if ( grid[r][c] != '0' ) continue;
                blockConf[j] = safe(r, c, n, 0);
                /*printf("(%d,%d) %s for %d.... %d %d %d\n", r, c, blockConf[j]?"safe":"unsafe", n, i, bc, br);*/
                configuration[n] += blockConf[j];
            }
            
            if ( configuration[n] == 1 ){
                for ( j = 0 ; j < 9 ; j++ ) if ( blockConf[j] == 1 ) break;
                r = blockConf2[j]/9, c = blockConf2[j]%9;
                grid[r][c] = n + '0';
                flag = 1;
                removeCandidate(r, c, n);
                unfilled--;
                /*printf("grid[%d][%d] = %d, hidden box\n", r, c, n);*/
            }
        }
    }

    return flag;
}

int (*ruleArr[10])(void);

int SolveUsingRule(){
    int i, flag = 0;
    ruleArr[0] = nakedSingle;
    ruleArr[1] = hiddenSingle;
    
    for ( i = 0 ; i < 2 ; i++ )
        if ( (*ruleArr[i])() ) flag = 1;
    
    return flag;
}
