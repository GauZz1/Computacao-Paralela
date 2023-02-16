#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int sieveOfEratosthenes(int n)
{
    int primes = 0;
    bool *prime = (bool*) malloc((n+1)*sizeof(bool));
    int sqrt_n = sqrt(n);

    memset(prime, true,(n+1)*sizeof(bool));

    #pragma omp parallel for schedule(dynamic)
    for (int p=2; p <= sqrt_n; p++)
    {
        if (prime[p] == true)
        {
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }

    for (int p=2; p<=n; p++)
        if (prime[p])
            primes++;

    return(primes);
}

int main()
{
    int n = 100000000;
    printf("%d\n",sieveOfEratosthenes(n));
    // Código sequencial: real = 4.072s
    // Código em paralelo: real = 2.75s
    // SpeedUp = 48% de melhora
    return 0;
}
