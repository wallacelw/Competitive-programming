/**
 * Author: Wallace
 * Date: 05/04/2024
 * Description: Simple BFS template
 * Time: O(V + E)
*/

int32_t main(){ sws;
    // compute distance from source
    vector<vll> g(n);
    vector<ll> d(n);
    vector<bool> vis(n);

    ll start = 1;
    queue<ll> q;
    q.push({0, start});
    d[start] = 0;

    while(!q.empty()) {
        auto u = q.front(); q.pop();

        for(auto v : g[u]) {
            if (vis[v]) continue; 
            vis[v] = 1;

            d[v] = d[u] + 1;
            q.push(v);
            // each v is added to queue only once
            // due to checking visited inside for(auto v : g[u]) 
            // and setting vis[v] = 1 before pushing to queue
        }
    }
}  