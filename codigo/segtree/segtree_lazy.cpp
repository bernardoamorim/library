// segtree de soma sem lazy

// vetor inicial A

// update: adiciona val ao range [l,r]
// query: soma do range [l,r]

// complexidades:
// build O(n)
// query O(logn)
// update O(logn)

void build(ll node, ll start, ll end) {
    if(start == end) tree[node] = A[start];
    else {
        ll mid = (start + end) / 2;
        
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    if(lazy[node] != 0) { 
        tree[node] += (end - start + 1) * lazy[node];    
        if(start != end) {
            lazy[node*2] += lazy[node];                  
            lazy[node*2+1] += lazy[node];              
        }
        lazy[node] = 0;                                  
    }
    if(start > end or start > r or end < l) return;

    if(start >= l and end <= r) {
        
        tree[node] += (end - start + 1) * val;
        if(start != end) {
   
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(node*2, start, mid, l, r, val);      
    update_range(node*2 + 1, mid + 1, end, l, r, val);  
    tree[node] = tree[node*2] + tree[node*2+1];        
}


ll query_range(ll node, ll start, ll end, ll l, ll r) {
    if(start > end or start > r or end < l) return 0;
       
    if(lazy[node] != 0) {

        tree[node] += (end - start + 1) * lazy[node];       
        if(start != end) {
            lazy[node*2] += lazy[node];        
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;                
    }

    if(start >= l and end <= r) return tree[node];

    ll mid = (start + end) / 2;
    ll p1 = query_range(node*2, start, mid, l, r);        
    ll p2 = query_range(node*2 + 1, mid + 1, end, l, r); 

    return (p1 + p2);
}
