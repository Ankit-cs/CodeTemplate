#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<pair<int, int>> st;

    void init(int _n) {
        this->n = _n;
        st.resize(4 * n, {INT_MAX, -1});  // Initialize with {MAX, -1}
    }

    pair<int, int> comb(pair<int, int> a, pair<int, int> b) {
        if (a.first < b.first) return a;
        if (a.first > b.first) return b;
        return (a.second < b.second) ? a : b; // If values are same, take smaller index
    }

    void buildTree(int start, int end, int node, vector<int> &v) {
        if (start == end) {
            st[node] = {v[start], start}; // Store value and index
            return;
        }
        int mid = (start + end) / 2;
        buildTree(start, mid, 2 * node + 1, v);
        buildTree(mid + 1, end, 2 * node + 2, v);
        st[node] = comb(st[2 * node + 1], st[2 * node + 2]); // Corrected index merging
    }

    pair<int, int> queryTree(int start, int end, int l, int r, int node) {
        if (start > r || end < l) return {INT_MAX, -1};  // Out of range
        if (start >= l && end <= r) return st[node]; // Complete overlap

        int mid = (start + end) / 2;
        auto q1 = queryTree(start, mid, l, r, 2 * node + 1);
        auto q2 = queryTree(mid + 1, end, l, r, 2 * node + 2);
        return comb(q1, q2);
    }

    void updateTree(int start, int end, int node, int index, int value) {
        if (start == end) {
            st[node] = {value, start};  // Update both value and index
            return;
        }
        int mid = (start + end) / 2;
        if (index <= mid)
            updateTree(start, mid, 2 * node + 1, index, value);
        else
            updateTree(mid + 1, end, 2 * node + 2, index, value);

        st[node] = comb(st[2 * node + 1], st[2 * node + 2]); // Ensure index updates correctly
    }

    void build(vector<int> &v) {
        buildTree(0, n - 1, 0, v);
    }

    pair<int, int> query(int l, int r) {
        return queryTree(0, n - 1, l, r, 0);
    }

    void update(int x, int y) {
        updateTree(0, n - 1, 0, x, y);
    }
};

int main() {
    vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SegmentTree tree;
    tree.init(10);
    tree.build(arr);

    cout << tree.query(1, 5).first << " " << tree.query(1, 5).second << "\n"; // Min in range [1,5]
    tree.update(4, -64);  // Update arr[4] to -64
    cout << tree.query(1, 5).first << " " << tree.query(1, 5).second << "\n"; // Min in range [1,5] after update

    return 0;
}
