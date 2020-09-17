#include <stdio.h>
#include <math.h> 
#include <time.h> 
#include <omp.h>


int n, pcnt;
char sieve[1<<30];
int primes[1<<30];

/************************************************
builds the sieve, NON-parallelized
*************************************************/
void erat(int n, int * pcnt){
  for(int i=2;i<=n;i++)
    sieve[i]=1;
  for(int i=2;i*i<=n;i++)
    if(sieve[i])
      for(int j=i*i;j<=n;j+=i)
        sieve[j]=0;
  *pcnt=0;
  for(int i=2;i<=n;i++)
    if(sieve[i]){
      primes[*pcnt]=i; 
      ++(*pcnt);
    }
}

/************************************************
prints all primes, formatted 
************************************************/
void print(int len){
  int ten=0;
  for(int i=0;i<len;i++){
    if(!(i%10))
      printf("\n%i: ",ten++);
    printf("%i ",primes[i]);
  }
  printf("\n");
}

/************************************************
builds the sieve, Parallelized
*************************************************/
void erat2(int n, int * pcnt){
  #pragma omp parallel for
  for(int i=2;i<=n;i++)
    sieve[i]=1;
  int sqrtn = sqrt((double)n);
  #pragma omp parallel for
  for(int i=2;i <= sqrtn;i++)
    if(sieve[i]){
      #pragma omp parallel for
      for(int j=i*i;j<=n;j+=i)
        sieve[j]=0;
    }
  *pcnt=0;
  #pragma omp parallel for
  for(int i=2;i<=n;i++)
    if(sieve[i]){
      primes[*pcnt]=i; 
      ++(*pcnt);
    }
}

/************************************************
entry point for program
/************************************************/
int main(){
  scanf("%i",&n);
  double start, end;

  pcnt=0;
  //clock_t t1 = clock();
  start = omp_get_wtime();
  erat(n,& pcnt);
  end = omp_get_wtime();
  //t1=clock()-t1;
  printf("Elapsed time = %f seconds\n\n", end-start);
  //print(pcnt);
  //printf("Elapsed time = %f seconds\n\n", ((float)t1) / CLOCKS_PER_SEC);




  pcnt=0;
  // clock_t t2 = clock();
  start = omp_get_wtime();
  erat2(n,& pcnt);
  end = omp_get_wtime();
  // t2=clock()-t2;
  printf("Elapsed time = %f seconds\n\n", end-start);
  //print(pcnt);
  //printf("Elapsed time = %f seconds\n\n", ((float)t1) / CLOCKS_PER_SEC);

}


