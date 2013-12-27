#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
	long x = *(long*)a, y = *(long*)b;
	
	if ( x == y ) return 0;
	return x > y ? 1 : -1;
}

int binarySearch( long *arr, long size, long n ){
	int low = 0, high = size, mid;
	
	while ( low + 1 < high ){
		mid = ( low + high ) >> 1;
		if ( arr[mid] >= n ) high = mid;
		else low = mid;
	}
	
	/*printf("->%d %ld %ld\n", high, arr[high], n);*/
	return low;
}

int main(){
	long array[2005], result;
	int n, i, j, test, kase, temp;
	
	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%d", &n);
			for ( i = 0 ; i < n ; i++ ) scanf("%ld", &array[i]);
			
			qsort(array, n, sizeof(long), cmp);
			/*for ( i = 0 ; i < n ; i++ ) printf("%ld ", array[i]);
			puts("");*/
			for ( result = i = 0 ; i < n ; i++ )
				for ( j = i + 1 ; j < n ; j++ ){
					temp = binarySearch(array, n, array[i] + array[j]);
					if ( temp > j ) result += temp - j;
				}

			printf("Case %d: %ld\n", kase, result);
		}
	}
	
	return 0;
}

