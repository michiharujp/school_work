#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double k = 38.5; // 1/V
double Is = 2 * 10e-12; // mA
double Vb = 3; // V
double Re = 1; // kΩ

double next(double V) {
    return Is * (exp(k * V) - 1);
}

double nextI(double I) {
    return Is * (exp(k * (Vb - (Re * I))) - 1);
}
double getDiff(double I) {
    return I - nextI(I);
}

int main(void) {
    // 初期値
    double minIe; // mA
    double maxIe; // mA
    cout << "minIeとmaxIeを入力してください" << endl;
    cin >> minIe >> maxIe; // 二つの値の標準入力
    if (getDiff(minIe) > 0) {
        cout << "minIeが大きすぎます。" << endl;
        return 1;
    }
    if (getDiff(maxIe) < 0) {
        cout << "maxIeが小さすぎます。" << endl;
        return 1;
    }
    while (true) {
        double diff = maxIe - minIe;
        double next_x = (maxIe + minIe) / 2;
        if (diff < 10e-5) break;
        else {
            if (getDiff(next_x) > 0) maxIe = next_x;
            else minIe = next_x;
        }
        cout << minIe << " " << maxIe << endl;
    }
    cout << minIe << endl;
    return 0;
}
