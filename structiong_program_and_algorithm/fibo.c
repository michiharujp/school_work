#include<stdio.h>
#include <time.h>

// recurive fibo
int fibo1(int n) {
    if (n == 0 || n == 1) return 1;
    else return fibo1(n-1) + fibo1(n-2);
}

// liner fibo
int fibo2(int n) {
    if (n == 0 || n == 1) return 1;
    int x=1,y=1,z;
    for (int i=2; i<n; i++) {
        z = x + y;
        x = y;
        y = z;
    }
    return z;
}

// define A and memo
int A[4] = {1,1,1,0};
int C[4];

// multiple matrix
int* times(int* A, int* B) {
    int D[4];
    D[0] = (*(A+0)) * (*(B+0)) + (*(A+1)) * (*(B+2));
    D[1] = (*(A+0)) * (*(B+1)) + (*(A+1)) * (*(B+3));
    D[2] = (*(A+2)) * (*(B+0)) + (*(A+3)) * (*(B+2));
    D[3] = (*(A+2)) * (*(B+1)) + (*(A+3)) * (*(B+3));
    for (int i=0; i<4; i++) C[i] = D[i];
    return C;
}

// calculate A^n
int* getA(int n) {
    int* B;
    if (n == 1) return A;
    if (n % 2 == 0) {
        B = getA(n/2);
        return times(B, B);
    } else {
        B = getA((n-1)/2);
        return times(times(B, B), A);
    }
}

// use maxrix fibo
int fibo3(int n) {
    int* An;
    An = getA(n - 1);
    return ((*An) + (*(An+1)));
}

int main(void) {

    int n = 1,ans;
    double msec;
    clock_t start, end;
    int* An;

    while(msec < 1000) {
        n++;
        start = clock();
        ans = fibo1(n);
        end = clock();
        msec = (end - start)*1000 / (double) CLOCKS_PER_SEC;
        printf("%lf msec\n",msec);
    }
    printf("if n = %d it costs more than 1s\n",n);
    printf("ans = %d\n", ans);

    return 0;
}
