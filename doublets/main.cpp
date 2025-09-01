#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <array>
#include <stack>

using namespace std;

class Trie {
    public:
        bool acc;
        Trie *next[256];

    public:
        Trie(): acc(0) {
            for (int i = 0; i < 256; ++i)
                next[i] = 0;
        }
};

Trie *root;
string dict[26000];
map<string, int> idx;
string buf;
vector<int> G[26000];
stack<int> path;
array<bool, 26000> vis;
array<int, 26000> bfs_tree;
bool has_adj[26000];

void insert(const string &word) {
    Trie *node = root;
    for (const char c: word) {
        if (!node->next[c]) {
            node->next[c] = new Trie;
        }
        node = node->next[c];
    }
    node->acc = 1;
}

void gen_adj(Trie *node, const int w, const int i, bool branching) {
    if (node) {
        if (i == dict[w].length() && node->acc && branching) {
            G[w].push_back(idx.at(buf));
        }

        else if (branching) {
            buf += dict[w][i];
            gen_adj(node->next[dict[w][i]], w, i + 1, 1);
            buf.pop_back();
        }

        else {
            for (int c = 0; c < 256; ++c) {
                if (node->next[c]) {
                    buf += (char)c;
                    gen_adj(node->next[c], w, i + 1, (char)c != dict[w][i]);
                    buf.pop_back();
                }
            }
        }
    } 
}

void bfs(const int u) {
    vis.fill(0);
    bfs_tree.fill(-1);

    queue<int> q;
    q.push(u);
    vis[u] = 1;
    while (!q.empty()) {
        const int x = q.front();
        q.pop();

        if (!has_adj[x]) {
            gen_adj(root, x, 0, 0);
            has_adj[x] = 1;
        }

        for (int y: G[x]) {
            if (!vis[y]) {
                bfs_tree[y] = x;
                vis[y] = 1;
                q.push(y);
            }
        }
    }
}

int main() {
    root = new Trie;
    string str;
    int i = 0;
    while (getline(cin, str)) {
        if (!str.length()) {
            break;
        }

        idx.emplace(str, i);
        dict[i++] = str;
        insert(str);
    }

    bool first = 1;
    while (getline(cin, str)) {
        stringstream ss(str);
        string w1, w2;
        ss >> w1 >> w2;

        if (!first)
            cout << endl;
        first = 0;

        if (!idx.count(w1) || !idx.count(w2)) {
            cout << "No solution." << endl;
            continue;
        }

        int u = idx[w1];
        int v = idx[w2];

        bfs(u);
        if (bfs_tree[v] == -1) {
            cout << "No solution." << endl;
        }

        else {
            while (v != -1) {
                path.push(v);
                v = bfs_tree[v];
            }
          
            while (!path.empty()) {
                cout << dict[path.top()] << endl;
                path.pop();
            }
        }
    }

    return 0;
}
