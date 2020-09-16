#include <bits/stdc++.h>
using namespace std;


vector<bool> arr;

vector<int> erat(long long n){
  arr.clear();
  arr.resize(n+1,true);

  for(int i=2;i<=sqrt(n);i++)
    if(arr[i])
      for(int j=i*i; j<=n; j+=i)
        arr[i]=false;
  
  vector<int> ret;
  for(int i=0; i<=n; i++)
    if(arr[i])
      ret.push_back(i);
  return ret;
}

int main(){

  long long n;
  cin >> n;

  vector<int> lst=erat();

  for(int i=0;i<lst.size();i++)
    cout<<lst[i]<<' ';
  cout<<endl;

}

