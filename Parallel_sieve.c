#include<stdio.h>
#include<math.h>
#include<omp.h>

char isPrime[1000000010];	//10^9

// odd-only sieve
int eratosthenesOdd(int N, int useOpenMP)
{
	/* enable/disable OpenMP */
	omp_set_num_threads(useOpenMP ? omp_get_num_procs() : 1);

	/* instead of i*i <= N we write i <= sqr(N) to help OpenMP */
	const int NSqrt = (int)sqrt((double)N);
	int memorySize = (N-1)/2;
	
	
	int i, j;	
	/* Let all numbers be prime initially */
	#pragma omp parallel for
	for (i = 0; i <= memorySize; i++)
		isPrime[i] = 1;
		
		
	/* find all odd non-primes */
	#pragma omp parallel for schedule(dynamic)
	for (i = 3; i <= NSqrt; i += 2)
		if (isPrime[i/2])
			for (j = i*i; j <= N; j += 2*i)
				isPrime[j/2] = 0;
				
	/* sieve is complete, count primes */
	int total = N >= 2 ? 1 : 0;
	#pragma omp parallel for reduction(+:total)
	for (i = 1; i <= memorySize; i++)
		total += isPrime[i];
		
	return total;
}

int main()
{
	int total = eratosthenesOdd(1000000000, 1);
	printf("%d\n", total);
	return 0;
}
