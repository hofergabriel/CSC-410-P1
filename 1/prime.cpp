#include <bits/stdc++.h>
using namespace std;

int n, pcnt;
bool sieve[1<<9];
int primes[1<<9];

void erat(int n, int & pcnt){
  for(int i=2;i<=n;i++)
    sieve[i]=true;
  for(int i=2;i*i<=n;i++)
    if(sieve[i])
      for(int j=i*i;j<=n;j+=i)
        sieve[j]=0;
  pcnt=0;
  for(int i=2;i<=n;i++)
    if(sieve[i]){
      primes[pcnt]=i; 
      pcnt++;
    }
}

void print(int len){
  for(int i=0;i<len;i++)
    cout<<primes[i]<<' ';
  cout<<endl;
}

int main(){
  cin >> n;
  pcnt=0;
  erat(n,pcnt);
  print(pcnt);
}


