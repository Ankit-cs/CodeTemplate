#include <bits/stdc++.h>
using namespace std;
struct segmenttree
{
    int n;
    vector<int> st;

    void init(int _n_)
    {
        this->n = _n_;
        st.resize(4 * n, 0);
    }
    int comb(int a, int b) // range sum
    {
        // gcd in a range 
        // max in a range can bwe do with this function 
        return a + b;
    }

    void buildTree(int start, int end, int node, vector<int> &v)
    {
        if (start == end)
        {
            st[node] = v[start];
            return;
        }
        int mid = (start + end) / 2;
        buildTree(start, mid, 2 * node + 1, v);
        buildTree(mid + 1, end, 2 * node + 2, v);
        st[node] = comb(st[node * 2 + 1], st[node * 2 + 2]);
    }
    int query(int start, int end, int l, int r, int node)
    {
        if (start > r || end < l)
            return 0;
        if (start >= l && end <= r)
            return st[node];
        
        int mid = (start + end) / 2;
        int q1 = query(start, mid, l, r, 2 * node + 1);
        int q2 = query(mid + 1, end, l, r, 2 * node + 2);
        return comb(q1, q2);
    }
    void update(int start,int end,int node,int index,int value){
        if(start==end){
            st[node]=value;
            return;
        }
        int mid=(start+end)/2;
        if(index<=mid) update(start,mid,2*node+1,index,value);
        else update(mid+1,end,2*node+2,index,value);

        st[node]=comb(st[node*2+1],st[node*2+2]);
        return;
    }
    void build(vector<int> &v){
    buildTree(0,n-1,0,v);
    }
    int query(int l,int r){
        return query(0,n-1,l,r,0);
    }
    void update (int x,int y){
        update(0,n-1,0,x,y);
    }
};
int main()
{
vector<int>arr{1,2,3,4,5,6,7,8,9,10};
segmenttree tree;
tree.init(10);
tree.build(arr);
cout<<tree.query(1,5)<<"\n";
tree.update(4,-64);
cout<<tree.query(1,5)<<"\n";
    return 0;
}