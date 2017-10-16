#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10
#define PRINT 1 // Nが大きな値の時は0にする
#define CHECK 1

int sort[N];

void swap(int *x, int *y) {
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void print() {
    for (int i=0; i<N; i++) {
        printf ("%d ", sort[i]);
    }
    printf ("\n");
}

void printH(int k) {
    for (int i=0; i<k; i++) {
        printf ("%d ", sort[i]);
    }
    printf ("\n");
}

void bubbleSort() {
    int tmp;
    for (int i=1; i<N; i++)
        for (int j=0; j<N-i; j++)
            if (sort[j] > sort[j+1]) swap(&sort[j], &sort[j+1]);
}

void shakerSort() {
    int top=0,bot=N-1;
    while(true) {
        int index;
        index = top;
        for (int i=top; i<bot; i++) {
            if (sort[i] > sort[i+1]) {
                swap(&sort[i], &sort[i+1]);
                index = i;
            }
        }
        bot = index;
        if (top == bot) break;

        index = bot;
        for (int i=bot; i>top; i--) {
            if (sort[i] < sort[i-1]) {
                swap(&sort[i], &sort[i-1]);
                index - i;
            }
        }
        top = index;
        if (top == bot) break;
    }
}

void insertionSort() {
    int i,j;
    int tmp;
    for (i=1; i<N; i++) {
        tmp = sort[i];
        if (sort[i-1] > tmp) {
            j = i;
            do {
                sort[j] = sort[j-1];
                j--;
            } while (j > 0 && sort[j-1] > tmp);
            sort[j] = tmp;
        }
    }
}

void selectionSort() {
    int min;
    for (int i=0; i<N; i++) {
        min = i;
        for (int j=i+1; j<N; j++) {
            if (sort[j] < sort[min]) min = j;
        }
        swap(&sort[i], &sort[min]);
    }
}

void heapSort() {
    int getParent(int i) { return ((i + 1) / 2 - 1); }
    int getLeft(int i) { return ((i + 1) * 2 - 1); }
    int getRight(int i) { return ((i + 1) * 2); }
    void upheap(int *data, int n) {
        while(n > 0) {
            int m = getParent(n);
            if (data[m] < data[n]) swap(&data[m], &data[n]);
            else break;
            n = m;
        }
    }
    void downheap(int *data, int n) {
        int m = 0;
        int tmp = 0;
        while(true) {
            int le = getLeft(m);
            int ri = getRight(m);
            if (ri > n) break;
            if (data[le] > data[tmp]) tmp = le;
            if (data[ri] > data[tmp]) tmp = ri;
            if (tmp == m) break;
            swap(&data[tmp], &data[m]);
            m = tmp;
        }
    }
    for (int i=1; i<N; i++) upheap(sort, i);
    for (int i=N-2; i>0; i--) {
        swap(&sort[0], &sort[i]);
        downheap(sort, i);
    }
}


void xxxSort() {
}

int main (void) {
    int i, j, t;
    srand ((unsigned int) time(NULL));
    // Fisher-Yatesアルゴリズムで1~Nのランダムな数列を構築する
    for (i=0; i<N; i++) {
        sort[i] = i + 1;
    }
    for (i=N-1; i>0; i--) {
        j = rand()%(i+1);
        t = sort[i];
        sort[i] = sort[j];
        sort[j] = t;
    }
    if (PRINT) print();

    heapSort();

    if (PRINT) print();
    /*

       clock_t start, end;
       start = clock();
       printf ("Sort start...");
    // ソートを行う関数の呼び出し
    xxxSort ();
    printf("Sort end.\n");
    end = clock();

    if (PRINT) {
    for (i=0; i<N; i++) {
    printf ("%d ", sort[i]);
    }
    printf ("\n");
    }
    printf("Elapsed time: %.2f milisec.\n", 
    (end - start)*1000 / (double) CLOCKS_PER_SEC);

    if (CHECK) {
    for (i=0; i<N-1; i++) {
    if (sort[i] > sort[i+1]) {
    printf ("*** Not sorted ***\n"); break;
    }
    }
    }
    */
    return EXIT_SUCCESS;
}

