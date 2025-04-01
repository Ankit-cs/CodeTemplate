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

    // walk function for tc of exactly logn instead of logn^2
    int walk(int start,int end,int node,int sum,int wantsum){
        if(start==end) return start;
        int mid=(start+end)/2;
        if(sum+st[2*node+1]>=wantsum) return walk(start,mid,2*node+1,sum,wantsum);
        return walk(mid+1,end,2*node+2,sum+st[2*node+1],wantsum);
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
int n,q;
cin>>n>>q;
segmenttree tree;
tree.init(n);
for(int i=0;i<n;i++) tree.update(i,1);
vector<int>a(n);
for(auto & i:a) cin>>i;
for(int i=0;i<q;i++){
    int x;cin>>x;
   int idx=tree.walk(x);
   tree.update(idx,0);
   cout<<a[idx]<<" ";
}
cout<<"/n";
    return 0;
}
// current time ocmplexity is O((logn)^2)
/*
 int left=0;int right=n-1;int ans=n-1;
    while(left<=right){
        int mid=(left+right)/2;
        if(tree.query(0,mid)>=x){
            ans=mid;
            right=mid-1;
        }
        left=mid+1;
    }
    cout<<a[ans]<<" ";
    tree.update(ans,0);*/