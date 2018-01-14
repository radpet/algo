#include <iostream>
#include <vector>
#include<math.h>
using namespace std;

// vector<int> a = {3, 2, 3, 2, 2, 77, 89, 23, 90, 11};
// vector<int> a = {5,8,13,27,14};
vector<int> a = {1,2,3};


int solve(vector<int> machines, int current){
  if(current >= a.size() ){
    int maxim = 0;
    for (auto x : machines){
      maxim = max(x, maxim);
    }
    return maxim;
  }
  int sol = 9999999;
  for(int i=0;i<machines.size();i++){
    machines[i] +=a[current];
    int cur = solve (machines, current+1);
    machines[i]-=a[current];
    sol = min(cur,sol);
  }

  return sol;

}

int main() {


  int sum = 0;
  vector<int> b = {0,0};
  cout<<solve(b, 0)<<endl;

  return 0;
}
