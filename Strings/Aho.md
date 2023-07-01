## Aho Cosarick

```cpp
namespace aho {
    map<char, int> to[MAX];
    int link[MAX], idx = 0, term[MAX], exit[MAX], sobe[MAX];
    vector<int> word[MAX];
    bool vis[MAX]; // avoids recalculation
    int match[MAX];
    // idx+1 of the last char of the pattern match
    // idx = 0 -> no match
    
    void add(string& s, int id) {
        int at = 0;
        for (char c : s) {
            if (to[at].count(c)) at = to[at][c];
            else at = to[at][c] = ++idx;
        }
        term[at]++, sobe[at]++;
        word[at].pb(id);
    }

    void build() { 
        queue<int> q;
        q.push(0);
        link[0] = exit[0] = -1;
        while (q.size()) {
            int i = q.front(); q.pop();
            for (auto [c, j] : to[i]) {
                int l = link[i];
                while (l != -1 and !to[l].count(c)) l = link[l];
                link[j] = l == -1 ? 0 : to[l][c];
                exit[j] = term[link[j]] ? link[j] : exit[link[j]];
                if (exit[j] != -1) sobe[j] += sobe[exit[j]];
                q.push(j);
            }
        }
    }

    ll query(string& s) { // returns number of matches
        memset(vis, 0, sizeof(vis));
        int at = 0, ans = 0;
        int n = (int) s.size();
        for (int i=0; i<n; i++){
            char c = s[i];
            while (at != -1 and !to[at].count(c)) at = link[at];
            at = at == -1 ? 0 : to[at][c];

            int tmp = at;
            while ((tmp > 0 and !vis[tmp])) {
                vis[tmp] = 1;

                for(auto id : word[tmp])
                    match[id] = i+1;

                tmp = exit[tmp];
            }

            ans += sobe[at];
        }
        return ans;
    }
}

void solve() {
    string s; cin >> s;
    int n; cin >> n;
    vector<string> p(n);
    for(int i=0; i<n; i++) {
        cin >> p[i];
        aho::add(p[i], i);
    }
    aho::build();
    aho::query(s);
    for(int i=0; i<n; i++) {
        int pos = aho::match[i];
        if (pos == 0) 
            cout << -1 << endl;
        else 
            cout << pos - p[i].size() + 1 << endl;
    }
}
```