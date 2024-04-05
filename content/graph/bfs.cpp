/**
 * Author: Wallace
 * Date: 05/04/2024
 * Description: Simple BFS template
 * Time: O(V + E)
*/

vector<vll> g(n);
vector<ll> d(n);
vector<bool> vis(n);

void bfs(ll src, ll sink) {

    queue<ll> q;
    q.push(src);
    d[src] = 0;
    vis[src] = 1;

    while(!q.empty()) {
        auto u = q.front(); q.pop();

        // add here a special break condition if needed, ex:
        if (u == sink) break;

        for(auto v : g[u]) {
            
            // each v is added to queue only once
            // due to checking visited inside for(auto v : g[u]) 
            // and setting vis[v] = 1 before pushing to queue
            if (!vis[v]) {
                vis[v] = 1;
                d[v] = d[u] + 1;
                q.push(v);
            } 

            else { // already added to queue, but there may be a shorter path
                d[v] = min(d[v], d[u] + 1);
            }
        }
    }
}  