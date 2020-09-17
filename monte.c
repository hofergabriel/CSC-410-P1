#include <stdio.h>
#include <math.h> 
#include <time.h> 
#include <omp.h>
#include <stdlib.h>



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


void main(){
  long long n;
  scanf("%lld", & n);

  double _PI_=monte(n);
  printf("PI: %f\n",_PI_);

}



