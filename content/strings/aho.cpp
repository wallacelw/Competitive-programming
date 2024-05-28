const int A = 26;
int to[N][A];
int ne = 2, fail[N];
vector<int> term[N];
vector<int> g[N];
 
void add(string str, int id){
    int p = 1;
    for(auto c: str){
        int ch = c - 'a'; // !
        if(!to[p][ch]) to[p][ch] = ne++;
        p = to[p][ch];
    }
    term[p].push_back(id);
}
 
int compress(int x){
    if(term[x].size() > 0 or x == 1){
        return x;
    }
    return fail[x] = compress(fail[x]);
}
 
void init(){
    for(int i = 0; i < ne; i++) fail[i] = 1;
    queue<int> q; q.push(1);
    int u, v;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < A; i++){
            if(to[u][i]){
                v = to[u][i]; q.push(v);
                if(u != 1){
                    fail[v] = to[ fail[u] ][i];
                }
            }
            else if(u != 1) to[u][i] = to[ fail[u] ][i];
            else to[u][i] = 1;
        }
        g[fail[u]].push_back(u);
    }
