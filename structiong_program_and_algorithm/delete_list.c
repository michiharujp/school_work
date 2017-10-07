#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ２重線形リストのノード（セル）の構造体
typedef struct tagNode {
    struct tagNode *prev; // 前のノードへのポインタ
    struct tagNode *next; // 次のノードへのポインタ
    int data; // ノードのデータ（今回は整数型）
} Node;

// メイン関数
int main (void) {
    int buf;
    Node *firstNode, *lastNode, *newNode;
    firstNode = lastNode = NULL;
    do {
        printf("整数値を入力してください（0を入力すると終了）:");
        scanf ("%d", &buf); //入力された整数値の読み込み
        if (buf) {
            // 新しいノード（セル）の作成．メモリ確保．
            newNode = (Node*)malloc(sizeof(Node));
            newNode->data = buf;
            newNode->next = NULL;

            if (lastNode != NULL) {
                lastNode->next = newNode;
                newNode->prev = lastNode;
                lastNode = newNode;
            } else {
                firstNode = lastNode = newNode;
                newNode->prev = NULL;
            }
        }
    } while (buf != 0);

    Node* thisNode;
    // 一覧を表示する関数
    void showNodes() {
        for (thisNode = firstNode; thisNode != NULL; thisNode = thisNode->next) {
            printf ("%d ", thisNode->data);
        }
        printf ("\n");
    }
    // ノードを削除する関数
    void deleteNode(int buf) {
        bool exist = false;
        bool isFirst, isLast;
        for (thisNode = firstNode; thisNode != NULL; thisNode = thisNode->next) {
            if (thisNode->data == buf) {
                printf("入力された値の中に%dがみつかりました。削除します。\n", buf);
                exist = true;
                isFirst = thisNode->prev == NULL;
                isLast = thisNode->next == NULL;
                // ノードが先頭、末尾、途中かによって処理を分ける
                if (isFirst && isLast) {
                    firstNode = NULL;
                } else if (isFirst) {
                    firstNode = thisNode->next;
                    thisNode->next->prev = NULL;
                } else if (isLast) {
                    thisNode->prev->next = NULL;
                } else {
                    thisNode->prev->next = thisNode->next;
                    thisNode->next->prev = thisNode->prev;
                }
                printf("---現在のデータ一覧---\n");
                showNodes();
                // 削除したノードのメモリを解放
                free(thisNode);
                break;
            }
        }
        // 削除する数字が見つからなかった場合のエラー文
        if (!exist) printf("%dは存在しません\n", buf);
    }
    // データが残っているかどうかを監視する変数
    bool finish = false;
    do {
        printf("削除する値を入力してください（0を入力すると終了）:");
        scanf ("%d", &buf);
        if (finish) printf("もう削除できるデータはありません\n0で終了します\n");
        else if (buf) {
            deleteNode(buf);
            finish = firstNode == NULL;
        }
    } while (buf != 0);

    // 最終結果の表示
    printf("---最終的な結果一覧---\n");
    showNodes();

    // リストの全ノード（セル）を削除
    for (thisNode = firstNode; thisNode != NULL; ) {
        Node* removeNode = thisNode;
        thisNode = thisNode->next;
        free (removeNode);
    }
    return 0;
}
