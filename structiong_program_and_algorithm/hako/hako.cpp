#include <bits/stdc++.h>
using namespace std;

const int BD_Y = 5;
const int BD_X = 4;

struct board {
    char a[BD_Y][BD_X]; // 盤面
    char b[BD_Y][BD_X]; // 盤面 同一形状のものを同一記号にしたもの
    int count; // 手数
    struct board *next; // 盤面の後を指す
    struct board *left; // 二分探索木の左
    struct board *right; // 二分探索木の右
    struct board *parent; // 一手前の盤面を指す
};

struct koma {
    int height;
    int width;
    char name;
};

int N; // 駒の数
koma komas[100];
char girl; // 箱入り娘を示す文字
struct board *current_node; // 現在の盤面
struct board *last_node; //リストの最後
struct board *top_node; // 二分探索木の根
int cnt; // 現在の手数
int board_count; // 記憶している盤面の数

unordered_map<char, char> type_map;

void printBoard(struct board *bd) {
    cout << "----" << endl;
    cout << "[" << bd->count << "]" << endl;
    for (int i=0; i<BD_Y; i++) {
        for (int j=0; j<BD_X; j++) cout << bd->a[i][j];
        cout << endl;
    }
}

struct board *up(struct board *a, int h, int w, char c) {
    struct board *nxt_bd;
    for (int i=0; i<BD_Y-h; i++) {
        for (int j=0; j<BD_X-w+1; j++) {
            for (int k=0; k<w; k++) {
                if (a->a[i][j+k] != '*') goto next;
                for (int m=0; m<h; m++) {
                    if (a->a[i+m+1][j+k] != c) goto next;
                }
            }
            // 可能であれば新盤面を返す
            nxt_bd = (struct board *)malloc(sizeof(struct board));
            for (int k=0; k<BD_Y; k++) {
                for (int m=0; m<BD_X; m++) nxt_bd->a[k][m] = a->a[k][m];
            }
            for (int k=0; k<w; k++) {
                nxt_bd->a[i][j+k] = c;
                nxt_bd->a[i+h][j+k] = '*';
            }
            nxt_bd->count = a->count + 1;
            nxt_bd->parent = a;
            return nxt_bd;
next:
            continue;
        }
    }
    return NULL;
}


struct board *down(struct board *a, int h, int w, char c) {
    struct board *nxt_bd;
    for (int i=0; i<BD_Y-h; i++) {
        for (int j=0; j<BD_X-w+1; j++) {
            for (int k=0; k<w; k++) {
                if (a->a[i+h][j+k] != '*') goto next;
                for (int m=0; m<h; m++) {
                    if (a->a[i+m][j+k] != c) goto next;
                }
            }
            // 可能であれば新盤面を返す
            nxt_bd = (struct board *)malloc(sizeof(struct board));
            for (int k=0; k<BD_Y; k++) {
                for (int m=0; m<BD_X; m++) nxt_bd->a[k][m] = a->a[k][m];
            }
            for (int k=0; k<w; k++) {
                nxt_bd->a[i][j+k] = '*';
                nxt_bd->a[i+h][j+k] = c;
            }
            nxt_bd->count = a->count + 1;
            nxt_bd->parent = a;
            return nxt_bd;
next:
            continue;
        }
    }
    return NULL;
}

struct board *left(struct board *a, int h, int w, char c) {
    struct board *nxt_bd;
    for (int i=0; i<BD_Y-h+1; i++) {
        for (int j=0; j<BD_X-w; j++) {
            for (int k=0; k<h; k++) {
                if (a->a[i+k][j] != '*') goto next;
                for (int m=0; m<w; m++) {
                    if (a->a[i+k][j+m+1] != c) goto next;
                }
            }
            // 可能であれば新盤面を返す
            nxt_bd = (struct board *)malloc(sizeof(struct board));
            for (int k=0; k<BD_Y; k++) {
                for (int m=0; m<BD_X; m++) nxt_bd->a[k][m] = a->a[k][m];
            }
            for (int k=0; k<h; k++) {
                nxt_bd->a[i+k][j] = c;
                nxt_bd->a[i+k][j+w] = '*';
            }
            nxt_bd->count = a->count + 1;
            nxt_bd->parent = a;
            return nxt_bd;
next:
            continue;
        }
    }
    return NULL;
}

struct board *right(struct board *a, int h, int w, char c) {
    struct board *nxt_bd;
    for (int i=0; i<BD_Y-h+1; i++) {
        for (int j=0; j<BD_X-w; j++) {
            for (int k=0; k<h; k++) {
                if (a->a[i+k][j+w] != '*') goto next;
                for (int m=0; m<w; m++) {
                    if (a->a[i+k][j+m] != c) goto next;
                }
            }
            // 可能であれば新盤面を返す
            nxt_bd = (struct board *)malloc(sizeof(struct board));
            for (int k=0; k<BD_Y; k++) {
                for (int m=0; m<BD_X; m++) nxt_bd->a[k][m] = a->a[k][m];
            }
            for (int k=0; k<h; k++) {
                nxt_bd->a[i+k][j] = '*';
                nxt_bd->a[i+k][j+w] = c;
            }
            nxt_bd->count = a->count + 1;
            nxt_bd->parent = a;
            return nxt_bd;
next:
            continue;
        }
    }
    return NULL;
}

// 比較用盤面の生成
void make_board_for_compare(struct board *bd) {
    for (int i=0; i<BD_Y; i++) {
        for (int j=0; j<BD_X; j++) bd->b[i][j] = type_map[bd->a[i][j]];
    }
}

int compare_board(struct board *a, struct board *b) {
    for (int i=0; i<BD_Y; i++) {
        for (int j=0; j<BD_X; j++) {
            int tmp = a->b[i][j] - b->b[i][j];
            if (tmp > 0) return 1;
            else if (tmp < 0) return -1;
        }
    }
    return 0;
}

// 同一の盤面が過去にあったかを見つける
bool is_unique(struct board *bd) {
    make_board_for_compare(bd);
    struct board *p;
    p = top_node;
    while(true) {
        int tmp = compare_board(p, bd);
        if (tmp == 0) {
            return false;
        } else if (tmp == 1) {
            if (p->right == NULL) {
                p->right = bd;
                break;
            }
            p = p->right;
        } else if (tmp == -1) {
            if (p->left == NULL) {
                p->left = bd;
                break;
            }
            p = p->left;
        }
    }
    return true;
}

// 新規なら追加、そうでないならメモリ解放
void append(struct board *bd) {
    if (bd == NULL) return;
    if (is_unique(bd)) {
        bd->left = NULL;
        bd->right = NULL;

        last_node->next = bd;
        bd->next = NULL;
        last_node = bd;
        board_count++;

        // printBoard(bd);
        if (bd->count != cnt) cnt = bd->count;

        if (
                bd->a[3][1] == girl &&
                bd->a[3][2] == girl &&
                bd->a[4][1] == girl &&
                bd->a[4][2] == girl
           ) {
            cout << "found" << endl;
            while (true) {
                printBoard(bd);
                bd = bd->parent;
                if (bd == NULL) break;
            }
            cout << "min is " << cnt << endl;
            exit(0);
        }
    } else {
        free(bd);
    }
}

void move(struct board *bd, int h, int w, char c) {
    struct board *tmp;

    tmp = up(bd, h, w, c);
    append(tmp);
    tmp = down(bd, h, w, c);
    append(tmp);
    tmp = left(bd, h, w, c);
    append(tmp);
    tmp = right(bd, h, w, c);
    append(tmp);
}

main() {
    cin >> N;

    // 駒の入力
    for (int i=0; i<N; i++) {
        cin >> komas[i].height;
        cin >> komas[i].width;
        cin >> komas[i].name;
        type_map[komas[i].name] = komas[i].name;
        for (int j=0; j<i; j++) {
            if (komas[i].height == komas[j].height &&
                    komas[i].width == komas[j].width) {
                type_map[komas[i].name] = komas[j].name;
                break;
            }
        }
        if (komas[i].height == 2 && komas[i].width == 2) girl = komas[i].name;
    }

    struct board start;
    for (int i=0; i<BD_Y; i++) {
        for (int j=0; j<BD_X; j++) cin >> start.a[i][j];
    }
    make_board_for_compare(&start);
    start.count = 0;
    start.next = NULL;
    start.right = NULL;
    start.left = NULL;
    start.parent = NULL;

    current_node = &start;
    last_node = &start;
    top_node = &start;

    cnt = 0;
    board_count = 1;

    while (true) {
        for (int i=0; i<N; i++) {
            move(current_node, komas[i].height, komas[i].width, komas[i].name);
        }
        current_node = current_node->next;
        if (current_node == NULL) break;
    }

    cout << "solution not found" << endl;

    return 0;
}
