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
#include <stdlib.h>

/********************************************************
My square function
*********************************************************/
double sq(double x){
  return x*x;
}

/********************************************************
NON-parallelized Monte Carlo algorithm
*********************************************************/
double monte(long long n){
  long long hits=0; 
  double x, y, pi;
  for(int i=0; i<n; i++)
    hits += sq((double)rand()/((double)RAND_MAX)) + 
      sq((double)rand()/((double)RAND_MAX)) 
      <= 1.0 ? 1 : 0;
  pi = 4.0*hits/(double)n;
  return pi;
}

/********************************************************
Parallelized Monte Carlo algorithm
*********************************************************/
double monte2(long long n){
  long long hits=0; 
  double x, y, pi;
  #pragma omp for
  for(int i=0; i<n; i++){
    hits += sq((double)rand()/((double)RAND_MAX)) + 
      sq((double)rand()/((double)RAND_MAX)) 
      <= 1.0 ? 1 : 0;
  }
  pi = 4.0*hits/(double)n;
  return pi;
}

/********************************************************
Entry point 
*********************************************************/
void main(){
  long long n;
  double start, end, _PI_;
  scanf("%lld", & n);

  printf("Monte Carlo Method NON-parallelized\n");
  start = omp_get_wtime();
  _PI_=monte(n);
  end = omp_get_wtime();

  printf("PI: %f\n",_PI_);
  printf("Elapsed time = %f seconds\n\n", end-start);

  printf("Monte Carlo Method parallelized\n");
  start = omp_get_wtime();
  _PI_=monte2(n);
  end = omp_get_wtime();

  printf("PI: %f\n",_PI_);
  printf("Elapsed time = %f seconds\n\n", end-start);
}

