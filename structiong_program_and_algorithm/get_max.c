#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double maximum_liner(double *, int);
void list(double *, int);

int main(void){
    int n,tmp;
    //nを変えて表示させる
    double *array, max, msec;
    clock_t start, end;
    tmp = 0;
    printf("n,time\n");
    for (int i=0; i<=50; i++) {
        tmp += 1e6;
        n = tmp;
        array = (double *)malloc(n * sizeof(double));
        srand((unsigned)time(NULL));
        for (int i=0; i<n; i++) {
            array[i] = (double)rand() / (double)RAND_MAX;
        }

        start = clock();
        max = maximum_liner(array,n);                  /*最大値を求める関数呼び出し*/
        end = clock();
        msec = (end - start)*1000 / (double) CLOCKS_PER_SEC;
        printf("%d, %.4f\n", n, msec);
        //printf("Maximum number is %lf\n",max);
        //printf("%d個 %.2f milisec.\n",n,
    }
    return EXIT_SUCCESS;
}

//一覧表示
void list(double *array, int n) {
    for (int i=0; i<n; i++) printf("%lf\n", array[i]);
}

//線形探索
double maximum_liner(double *array, int n) {
    double tmp = 0;
    for (int i=0; i<n; i++) {
        if (array[i] > tmp) {
            tmp = array[i];
        }
    }
    return tmp;
}
