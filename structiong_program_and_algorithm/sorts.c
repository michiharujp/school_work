#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define times 1000 //試行回数
#define N 30000 //データ数
#define execute heapSort //実行したいソートを入れる

//bubbleSort
//shakerSort
//insertionSort
//selectionSort
//heapSort
//bogoSort

int sort[N]; // 対象となる配列

// 二数を入れ替える関数
void swap(int *x, int *y) {
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

// 中身を表示する関数(デバッグ用)
void print() {
    for (int i=0; i<N; i++) {
        printf ("%d ", sort[i]);
    }
    printf ("\n");
}

// ソート済みであるかチェックする関数
bool check() {
    for (int i=0; i<N-1; i++) if (sort[i] > sort[i+1]) return false;
    return true;
}

// 配列の中身をシャッフルする関数
void shuffle() {
    srand ((unsigned int) time(NULL));
    for (int i=0; i<N; i++) {
        int j = rand()%N;
        int tmp = sort[i];
        sort[i] = sort[j];
        sort[j] = tmp;
    }
}

// ソート関数ここから
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
                index = i;
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
            if (le >= n) break;
            if (data[le] > data[tmp]) tmp = le;
            if (ri < n && data[ri] > data[tmp]) tmp = ri;
            if (tmp == m) break;
            swap(&data[tmp], &data[m]);
            m = tmp;
        }
    }
    for (int i=1; i<N; i++) upheap(sort, i);
    for (int i=N-1; i>0; i--) {
        swap(&sort[0], &sort[i]);
        downheap(sort, i);
    }
}

void bogoSort() {
    srand ((unsigned int) time(NULL));
    while (!check()) {
        shuffle();
        print();
    }
}

// ソート関数ここまで

void setData() {
    for (int i=0; i<N; i++) sort[i] = i + 1;
    shuffle();
}

double getTime() {
    clock_t start, end;
    start = clock();
    execute();
    end = clock();
    if (!check) return -100;
    return (end - start)*1000 / (double) CLOCKS_PER_SEC;
}

int main (void) {
    double ti=0;
    double tmp;
    for (int i=0; i<times; i++) {
        setData();
        tmp = getTime();
        ti += tmp;
        printf("%.2f\n", tmp);
    }
    printf("average is : %0.2f\n", ti / times);
    return EXIT_SUCCESS;
}
