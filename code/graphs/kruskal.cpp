// Kruskal
//
// Generates MST from the edges vector ed
// and returns its total weigh w
//
// Uses DSU

// Time complexity: O(m log(n))

int n; // n of nodees

vector<pair<int,ii> > > edg;
vector<int> par;
vector<int> sz;

void build(){
	for(int i=1;i<=n;++i){
	   par[i]=i; 
	   sz[i]=1;
	}
}	
int find(int v){
	if(x==par[x])
    return x;
    else
    return sz[x]=find(par[x]);
}
void unite(int a, int b){
	a=find(a); b=find(b);
    if(sz[a]<sz[b]) swap(a,b);
    par[b]=a;
    sz[a]+=sz[b];
}

int kruskal() {
	int w = 0;
	build();
	sort(edg.begin(), edg.end());

	for(auto x : edg) {
		int u = edg.s.f, v = edg.s.s;
		if(find(u) != find(v)) {
			w += x.f;
			unite(u,v);
		}
	}
	return w;
}
