#include <bits/stdc++.h>
#include<cmath>
using namespace std;
bool prime[1000000000];

int sq1 = sqrt(1000000000);
int sq2 = sqrt(sq1);

void seive(){
  memset(prime,1,sizeof(prime));

	prime[0] = prime[1] = 0;

	for (long long i = 2; i<=sq2; i++){
		if (prime[i]){
			for (long long j = i*i; j<=sq1; j += i){
				if (prime[j])
					prime[j] = 0;
			}
		}
	}
}

void segmentedSeive(int a, int b){

	int lim = sqrt(b);
	int i, j;
	for (i = 2; i <= lim; i++){
		if (prime[i]){
			for (j = a - a%i; j <= b; j += i)
				if (j>=a && prime[j] && j!=i){
          prime[j] = 0;
        }
		}
	}

}


int main()
{
  seive();

  int t;
  cin>>t;
  int a,b;
  while(t--){
    cin>>a>>b;
    if (b>sq2){
      segmentedSeive(a,b);
    }

		for(int i=a;i<=b;i++){
      if (prime[i]){
        cout<<i<<endl;
      }
    }

		cout<<endl;
  }

	return 0;
}
