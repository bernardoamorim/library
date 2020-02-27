// segtree de soma sem lazy

// vetor inicial A
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


// adiciona val a idx

void update(int node, int start, int end, int idx, int val) {
    if(start == end) {
        A[idx] += val;
        tree[node] += val;
    }
    else {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid)
        {
            update(2*node, start, mid, idx, val);
        }
        else
        {
            update(2*node+1, mid+1, end, idx, val);
        }

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int query(int node, int start, int end, int l, int r) {
    if(r < start or end < l) {
        return 0;
    }
    if(l <= start and end <= r) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);

    return (p1 + p2);
}
