#include <stdio.h>
#include <math.h> 
#include <time.h> 
#include <omp.h>
#include <stdlib.h>



/********************************************************
NON-parallelized Monte Carlo algorithm
*********************************************************/
double monte(long long n){
  long long hits=0; 
  double x, y, pi;
  for(int i=0; i<n; i++){
    x = (double)rand() / ((double)RAND_MAX);
    y = (double)rand() / ((double)RAND_MAX);
    if(x*x + y*y <= (double)1.0) hits++;
  }
  pi = 4*hits/(double)n;
  return pi;
}

/********************************************************
Parallelized Monte Carlo algorithm
*********************************************************/
double monte2(long long n){
  long long hits=0; 
  double x, y, pi;
  #pragma omp parallel
  for(int i=0; i<n; i++){
    x = (double)rand() / ((double)RAND_MAX);
    y = (double)rand() / ((double)RAND_MAX);
    if(x*x + y*y <= (double)1.0) hits++;
  }
  pi = 4*hits/(double)n;
  return pi;
}

/********************************************************
Entry point
*********************************************************/
void main(){
  long long n;
  double start, end, _PI_;
  scanf("%lld", & n);

  /********************************************************/
  printf("Monte Carlo Method NON-parallelized\n");

  start = omp_get_wtime();
  _PI_=monte(n);
  end = omp_get_wtime();

  printf("PI: %f\n",_PI_);
  printf("Elapsed time = %f seconds\n\n", end-start);

  /********************************************************/
  printf("Monte Carlo Method parallelized\n");

  start = omp_get_wtime();
  _PI_=monte2(n);
  end = omp_get_wtime();

  printf("PI: %f\n",_PI_);
  printf("Elapsed time = %f seconds\n\n", end-start);
}






