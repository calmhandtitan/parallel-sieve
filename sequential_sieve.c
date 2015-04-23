#include <stdio.h>
#include <math.h>

const int MAX = 1000000010; //10^9
char isprime[1000000010];

int sieve(int n)
{
	int i, j, k;
	/*let all numbers are prime numbers */
	for(i = 1; i <= n; i++)	
		isprime[i] = 1;

	/* mark all multiples of 2 as composite */
	for(i = 4; i <= n; i+=2)	
		isprime[i] = 0;

	int LMT = sqrt(n);
	for(i = 3; i <= LMT; i+=2)
		if(isprime[i])
			for(j = i*i, k = i<<1; j <= n; j += k)
				isprime[j] = 0;

	/* sieve is complete, count primes */
	int total = 0;
	for(i = 2; i <= n; i++)
		total += isprime[i];

	return total;
}

int main()
{
	int n = MAX;
	int total = sieve(n);
	printf("%d\n", total);
	return 0;
}
