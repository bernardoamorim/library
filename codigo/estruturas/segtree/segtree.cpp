// segtree de soma sem lazy

// vetor inicial A
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


// adiciona val a idx

void update(ll node, ll start, ll end, ll idx, ll val) {
    if(start == end) {
        A[idx] += val;
        tree[node] += val;
    }
    else {
        ll mid = (start + end) / 2;
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

void update_range(ll node, ll start, ll end, ll l, ll r, ll val) {
    
    if (start > end or start > r or end < l)
        return;

    if (start == end) {
        tree[node] += val;
        return;
    }

    ll mid = (start + end) / 2;
    update_range(node*2, start, mid, l, r, val);
    update_range(node*2 + 1, mid + 1, end, l, r, val);

    tree[node] = tree[node*2] + tree[node*2+1];
}

ll query(ll node, ll start, ll end, ll l, ll r) {
    if(r < start or end < l) {
        return 0;
    }
    if(l <= start and end <= r) {
        return tree[node];
    }

    ll mid = (start + end) / 2;
    ll p1 = query(2*node, start, mid, l, r);
    ll p2 = query(2*node+1, mid+1, end, l, r);

    return (p1 + p2);
}
