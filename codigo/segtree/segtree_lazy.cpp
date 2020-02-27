// segtree de soma sem lazy

// vetor inicial A

// update: adiciona val ao range [l,r]
// query: soma do range [l,r]

// complexidades:
// build O(n)
// query O(logn)
// update O(logn)

void build(int node, int start, int end) {
    if(start == end) tree[node] = A[start];
    else {
        int mid = (start + end) / 2;
        
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update_range(int node, int start, int end, int l, int r, int val) {
    
    if (start > end or start > r or end < l)
        return;

    if (start == end) {
        tree[node] += val;
        return;
    }

    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);

    tree[node] = tree[node*2] + tree[node*2+1];
}
