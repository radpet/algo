#include<stdio.h>

int main(){

    int n;
    scanf("%d", &n);

    int positive = 0;
    int negative = 0;
    int zero = 0;

    for(int i=0;i<n;i++){
        int a;
        scanf("%d", &a);
        if(a==0){
            zero++;
        }

        if(a>0){
            positive++;
        }

        if(a<0){
            negative++;
        }
    }

    double pf = (double) positive / n;
    double nf = (double) negative / n;
    double zf = (double) zero / n;

    printf("%f\n",pf);
    printf("%f\n",nf);
    printf("%f\n",zf);

    return 0;
}