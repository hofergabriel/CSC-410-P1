#include <stdio.h>
#include <math.h> 
#include <time.h> 


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
entry point for program
/************************************************/
int main(){
  // read n
  scanf("%i",&n);
  // prime count 
  pcnt=0;

  clock_t t = clock();
  // call prime seive
  erat(n,& pcnt);
  // print the results
  t=clock()-t;

  print(pcnt);
  printf("Elapsed time = %f seconds\n\n", ((float)t) / CLOCKS_PER_SEC);
}


