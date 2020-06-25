#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int recursion_c(int n, int k){

	if(n == 0 && k >0)
		{return 0;}
	if(k == 0 && n >= 0)
		{return 1;}
	if(k == 1)
		{return n;}
	if(k == n)
		{return 1;}
	return recursion_c(n-1,k-1) + recursion_c(n-1,k);
}
int dynamic_c(int n,int r) {
		int c[n+1][r+1];
		int i,j;
		for(i=0;i<=n;i++) {
				c[i][0] = 1;
		}
		for(j=1;j<=r;j++) {
				c[0][j] = 0;
		}
		for(i=1;i<=n;i++) {
				for(j=1;j<=r;j++) {
						if (i == j) {
								c[i][j] = 1;
						}
						else if (j > i) {
							continue;  // doesn't exist
						}
						else {
								// apply the standard recursive formula        
								c[i][j] = c[i-1][j-1] + c[i-1][j];
						}
				}
		}
		return c[n][r];
}


int main(){




	int n , k ;
	long long  recursion ;
	long long dynamic;
	clock_t t;
	clock_t t2;

	printf("enter two number : ");
	scanf( "%d %d", &n, &k);

	if(n <0 || k <0 || k > n){
		printf("input error  ( n, k > 0 and n >= k)\n");
		exit(0);
	}


	t = clock();
	recursion = recursion_c(n,k);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;


	t = clock();
	dynamic = dynamic_c(n,k);
	t = clock() - t;
	double time_taken2 = ((double)t)/CLOCKS_PER_SEC;

	printf(" result C(%d,%d) solved by recursion is %lli\n time consuming :%lf\n\n ", n , k , recursion, time_taken);
	printf(" ressult C(%d,%d) solved by dynamic is %lli\n time consuming : %lf\n ", n , k , dynamic, time_taken2);
	
	}
