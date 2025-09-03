// https://open.kattis.com/problems/knapsack

#include <iostream>

using namespace std;

int main() {
    int M[101][101];
    memset(M[0], 0, 101);
  
    int N, W;
    int w[101];
    int v[101];
  
    while (cin >> W >> N) {
        for (int i = 0; i < N; ++i)
            cin >> v[i + 1] >> w[i + 1];
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j <= W; ++j) {
                if (w[i] > j)
                    M[i][j] = M[i - 1][j];
                else
                    M[i][j] = max(M[i - 1][j], v[i] + M[i - 1][j - w[i]]);
            }
        }

        int c = W;
        int a = 0;
        bool p[2000];
        memset(p, 0, 2000);
        for (int i = N; i >= 1; --i)
            if (M[i][c] != M[i - 1][c]) {
                c -= w[i];
                p[i - 1] = 1;
                ++a;
            }

        cout << a << endl;
        for (int i = 0; i < N; ++i)
            if (p[i])
                cout << i << ' ';
    }
  
    return 0;
}
