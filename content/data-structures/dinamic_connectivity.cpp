/**
 * Author: Lucas Sala
 * Date: 24/10/2024
 * Description: Solves dynamic connectivity problems offline with DSU rollback
 * Time: O(N * LOG(n)^2)
 * Status: Tested (https://codeforces.com/gym/100551/problem/A)
 */

struct dsu {
	vector<int> p, sz;
	vector<vector<pair<int&, int>>> st;

    int conj;

	dsu(int n) : p(n), sz(n, 1) { 
		iota(p.begin(), p.end(), 0);
        conj = n;
	}

	void checkpoint() { st.push_back({}); }
	
	void rollback() {
		while(st.back().size()) {
			auto [end, val] = st.back().back(); st.back().pop_back();
			end = val;
		}
		st.pop_back();
	}

    inline void update(int& x, int y) {
        st.back().push_back({x, x});
        x = y;
    }

	int find(int a) { return a == p[a] ? a : find(p[a]); }

	void join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
        update(conj,conj-1);
		if (sz[a] < sz[b]) swap(a, b);
		update(sz[a],sz[a]+sz[b]);
        update(p[b],a);
	}
};

const int MAX = 3e5+5;

int ans[MAX], tp[MAX];
dsu gp(MAX-1);

vector<pair<int,int>> tree[4*MAX];

void put(int l, int r, int a, int b, int lt = 0, int rt = MAX-1, int x = 1){
    if(lt > r or rt < l){
        return;
    }
    if(l <= lt and rt <= r){
        tree[x].push_back({a,b});
        return;
    }

    int meio = (lt+rt)/2;
    put(l,r,a,b,lt,meio,2*x);
    put(l,r,a,b,meio+1,rt,2*x+1);
}

void dfs(int l, int r, int x){
    gp.checkpoint();
    for(auto [a,b] : tree[x]){
        gp.join(a,b);
    }
    if(l == r){
        ans[l] = gp.conj;
        gp.rollback();
        return;
    }

    int meio = (l+r)/2;
    dfs(l,meio,2*x);
    dfs(meio+1,r,2*x+1);
    gp.rollback();
}