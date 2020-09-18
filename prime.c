/**********************************************************
Author: Gabriel Hofer
Course: CSC-410
Date: September 18, 2020
Instructor: Christer Karlsson
Program 1
***********************************************************/
#include <stdio.h>
#include <math.h> 
#include <time.h> 
#include <omp.h>

char sieve[1<<30];
int primes[1<<30];

/**********************************************************
builds the sieve, NON-parallelized
***********************************************************/
void erat(long int n, long int * pcnt){
  for(int i=2;i<=n;i++)
    sieve[i]=1;
  for(int i=2;i*i<=n;i++)
    if(sieve[i])
      for(int j=i*i;j<=n;j+=i)
        sieve[j]=0;
  *pcnt=0;
  for(int i=2;i<=n;i++)
    if(sieve[i])
      primes[(*pcnt)++]=i; 
}

/**********************************************************
prints all primes, formatted 
***********************************************************/
void print(int len){
  int ten=0;
  for(int i=0;i<len;i++){
    if(!(i%10))
      printf("\n%i: ",10*ten++);
    printf("%i ",primes[i]);
  }
  printf("\n");
}

/**********************************************************
builds the sieve, Parallelized
***********************************************************/
void erat2(long int n, long int * pcnt){
  #pragma omp parallel for
  for(int i=2;i<=n;i++)
    sieve[i]=1;
  int sqrtn = sqrt((double)n);
  for(int i=2;i <= sqrtn;i++)
    if(sieve[i]){
      #pragma omp parallel for
      for(int j=i*i;j<=n;j+=i)
        sieve[j]=0;
    }
  *pcnt=0;
  for(int i=2;i<=n;i++)
    if(sieve[i])
      primes[(*pcnt)++]=i; 
}

/**********************************************************
entry point for program
***********************************************************/
void main(){
  long int n, pcnt;
  double start, end;
  scanf("%li",&n);
  n--;

  pcnt=0;
  start = omp_get_wtime();
  erat(n,& pcnt);
  end = omp_get_wtime();
  print(pcnt);
  printf("Elapsed time = %.6f seconds\n\n", end-start);

  // reset primes and sieve.
  for(int i=0; i<(1<<30); i++){
    sieve[i]=0;
    primes[i]=0;
  }

  pcnt=0;
  start = omp_get_wtime();
  erat2(n,& pcnt);
  end = omp_get_wtime();
  print(pcnt);
  printf("Elapsed time = %.6f seconds\n\n", end-start);

}


