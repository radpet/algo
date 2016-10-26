#include<iostream>
#include<algorithm>
using namespace std;

int a[32];
int n;

int max(int a,int b){
  return a>b?a:b;
}

// O(2^n)
int slow(){
  int result = a[0];
  for(int subset=2;subset < (1<<n);subset++){
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

// O(nlogn)
int fast(){
  sort(a,a+n);
  int nc = 0;
  for(int i=0;i<n;i++){
    nc = nc +  (a[i]<0);
  }
  int sol = 1;

  if(nc%2==0){
    for(int i=0;i<n;i++){
      sol*=a[i];
    }
  }else{
    for(int i=0;i<n-1;i++){
      if(a[i]<0 && a[i+1]>0){
        continue;
      }
      sol*=a[i];
    }
    sol*=a[n-1];
  }

  return sol;
}


// O(n)
int faster(){
  int nc = 0;
  int ln = 1;
  int lni = -1;
  for(int i=0;i<n;i++){
    nc = nc +  (a[i]<0);
    if(a[i]<0){
      if(ln == 1){
        ln = a[i];
        lni = i;
      }
      if (ln<a[i]){
        ln = a[i];
        lni = i;
      }
    }
  }
  int sol = 1;

  if(nc%2==0){
    for(int i=0;i<n;i++){
      sol*=a[i];
    }
  }else{
    for(int i=0;i<n-1;i++){
      if(i==lni){
        continue;
      }
      sol*=a[i];
    }
    if(n-1 != lni){
      sol*=a[n-1];
    }

  }

  return sol;
}


int main(){
  cin>>n;

  for(int i=0;i<n;i++){
    cin>>a[i];
  }
  //cout<<slow()<<endl;
  //cout<<fast()<<endl;
  cout<<faster()<<endl;
}
