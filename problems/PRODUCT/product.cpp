#include<iostream>
using namespace std;

int a[32];
int n;

int max(int a,int b){
  return a>b?a:b;
}

// O(2^n)
int slow(){
  int result = 0;
  for(int subset=1;subset < (1<<n);subset++){
    int current = 1;
    for(int mask = 31;mask>=0;mask--){
      bool bit = subset & (1<<mask);
      if(bit){
        current*=a[mask];
      }
    }
    result = max(result,current);
  }


  return result;
}


int main(){
  cin>>n;

  for(int i=0;i<n;i++){
    cin>>a[i];
  }
  cout<<slow()<<endl;
}
