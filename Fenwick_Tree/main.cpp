#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class FenwickTree {
public:
    vector<int> s;

    FenwickTree(int n) {
        s.resize(n);
    }

    void update(int pos, int dif) {
        while (pos < s.size()) {
            s[pos] += dif;
            pos |= pos + 1;
        }
    }

    int query(int pos) {
        int res = 0;
        while (pos > 0) {
            res += s[pos - 1];
            pos &= pos - 1;
        }
        return res;
    }

    int lower_bound(int sum) {
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= s.size() && s[pos + pw - 1] < sum) {
                pos += pw;
                sum -= s[pos - 1];
            }
        }
        return pos;
    }
};

class Solution {
public:
    int timeIndex = 0;
    vector<vector<pair<int, int>>> adjacency;
    vector<int> tin, tout, depth;
    FenwickTree fenwick;
    vector<int> values;

    Solution() : fenwick(0) {}

    void dfs(int node, int parent) {
        tin[node] = timeIndex++;
        for (auto edge : adjacency[node]) {
            int next = edge.first;
            int weight = edge.second;
            if (next == parent) continue;
            depth[next] = 1 + depth[node];
            values[next] = weight;
            dfs(next, node);
        }
        tout[node] = timeIndex++;
    }

    vector<int> treeQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
        adjacency.resize(n);
        tin.resize(n);
        tout.resize(n);
        values.resize(n);
        depth.resize(n);

        for (auto &edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            int weight = edge[2];
            adjacency[u].push_back({v, weight});
            adjacency[v].push_back({u, weight});
        }

        fenwick = FenwickTree(2 * n);
        depth[0] = 0;
        dfs(0, -1);

        for (int i = 0; i < n; i++) {
            fenwick.update(tin[i], values[i]);
            if (tout[i] != 2 * n) {
                fenwick.update(tout[i], -values[i]);
            }
        }

        vector<int> result;
        for (auto &query : queries) {
            if (query[0] == 1) {
                int x = query[1] - 1;
                int y = query[2] - 1;
                int newValue = query[3];
                if (depth[x] < depth[y]) {
                    swap(x, y);
                }
                fenwick.update(tin[x], newValue - values[x]);
                fenwick.update(tout[x], values[x] - newValue);
                values[x] = newValue;
            } else {
                int node = query[1] - 1;
                result.push_back(fenwick.query(tin[node] + 1));
            }
        }

        return result;
    }
};
