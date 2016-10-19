#include<iostream>
#include<stdio.h>
using namespace std;

int seq[100001];
int n,q;

int find(int num){

  int low = 0;
  int high = n;

  while(low <= high){
    long current = (low+high) >> 1;
    if(seq[current]==num){
      int last;
      for(last = current;last>=0 && seq[last]==num;last--);
      return last+1;
    }
    if(seq[current]>num){
      high = current - 1;
    }else{
      low = current + 1;
    }
  }
  return -1;
}

int main(){
  scanf("%d %d",&n,&q);
  //cin>>n>>q;
  int a;
  for(int i=0;i<n;i++){
    scanf("%d",&seq[i]);
    //cin>>seq[i];
  }
  while(q--){
    //cin>>a;
    scanf("%d",&a);
    printf("%d\n",find(a));
    //cout<<find(a)<<endl;

  }

}
