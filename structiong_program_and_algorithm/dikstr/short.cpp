#include <bits/stdc++.h>
using namespace std;

const int INF = 100000;

int main(void) {
    int N,M; // 頂点の数と辺の数
    cin >> N >> M;
    vector< vector< pair<int, int> > > st(N); // 辺の定義
    vector<int> d(N, INF); // スタート地点からの距離 INF で初期化
    vector<int> prev(N, -1); // 最短経路をたどる際の前の頂点
    stack< pair<int, int> > box; // ヒープを検索する際のコピー領域
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int,int> > > pq; // 優先度付きキュー
    for (int i=0; i<M; i++) {
        int fr, to, dis; // fr から to への距離が dis
        cin >> fr >> to >> dis;
        st[fr].push_back(make_pair(to, dis));
        st[to].push_back(make_pair(fr, dis)); // 両側からアクセスできるようグラフを設定
    }
    int s=0, f=6; // スタート地点とゴールの設定
    d[s] = 0; // 初期化
    for (int i=0; i<N; i++) pq.push(make_pair(d[i], i)); // キューに距離を格納

    // 優先度付きキューがからになるまで処理を実行
    while (!pq.empty()) {
        int now = pq.top().second; // 今から使う頂点
        if (now == f) { // 終了条件
            cout << d[f] << endl;
            return 0;
        }
        pq.pop();
        for (int i=0; i<N; i++) cout << d[i] << ",";
        cout << endl;
        for (auto t : st[now]) { // 頂点に接続しているすべての頂点に対して実行
            int alt = d[now] + t.second; // スタート地点からその頂点までの距離
            int to = t.first; // 頂点の番号
            if (d[to] > alt) { // もしその頂点までの距離が既存のものより小さければ更新
                d[to] = alt;
                prev[to] = now;

                // ヒープから該当するものを見つけて更新
                bool flg = false;
                while (!flg) {
                    int tmp_dis = pq.top().first;
                    int tmp_stm = pq.top().second;
                    pq.pop();
                    if (tmp_stm == to) {
                        flg = true;
                        tmp_dis = alt;
                    }
                    box.push(make_pair(tmp_dis, tmp_stm));
                }
                while (!box.empty()) {
                    pq.push(box.top());
                    box.pop();
                }
            }
        }
    }

    // 以下、デバッグ用

    // 各地点までの距離とルートを表示
    for (int i=0; i<N; i++) {
        cout << "dis: " << d[i] << " ";
        int route = i;
        cout << "route: ";
        while (route != s) {
            cout << route << " ";
            route = prev[route];
        }
        cout << s << " " << endl;
    }

    // 答えの表示
    cout << "from " << s << " to " << f << " costs " << d[f] << endl;
    return 0;
}
