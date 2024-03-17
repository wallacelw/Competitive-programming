/** 
 * Author: Wallace
 * Date: 17/03/2024
 * Description: This second version may be slower due to dynamic allocation, queue, etc
 * but it's more readable, more memory efficient
 * Time: General Case, O(V^2 E); 
 * Unit Capacity, O((V+E) \sqrt{E});
 * Bipartite and unit capacity, O( (V+E) \sqrt{V})
 * Status: tested! https://www.spoj.com/submit/FASTFLOW/, 0.32s, plug it in (F)
 */

struct Dinic {
    struct Edge {
        ll to, flow, cap, rev;
    };
    
    vector<vector<Edge>> g;
    vector<ll> level, vis;
    ll src, sink, sz, maxFlow;

    Dinic(ll n) {
        src = n+1, sink = n+2, sz = n+3;
        g.assign(sz, vector<Edge>());
        level.assign(sz, 0);
        vis.assign(sz, 0);
        maxFlow = 0;
    }
    
    void addEdge(ll u, ll v, ll c, ll rc = 0) {
        ll id1 = (ll) g[u].size();
        ll id2 = (ll) g[v].size();
        g[u].pb( Edge({v, 0, c, id2}) );
        g[v].pb( Edge({u, 0, rc, id1}) );
    }
    
    bool bfs() { // creates layered subgraph
        for(ll i=0; i<sz; i++) {
            level[i] = -1; // not visited
        }
        level[src] = 0;
        queue<ll> q; q.push(src); 
        while(!q.empty()) {
            ll u = q.front(); q.pop();
            if (u == sink) break;
            for(auto [v, flow, cap, rev] : g[u]) {
                if (flow >= cap or level[v] != -1) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return (level[sink] == -1 ? false : true);
    }
    
    ll dfs(ll u, ll minFlow){
        if(u == sink) return minFlow;
        for(ll &i = vis[u]; i<(ll)g[u].size(); i++){
            auto &[v, flow, cap, rev] = g[u][i];
            
            if(flow >= cap or level[u]+1 != level[v]) continue;
            
            ll newFlow = min(minFlow, cap - flow);
            ll adjustedFlow = dfs(v, newFlow);

            if(adjustedFlow > 0){
                flow += adjustedFlow;
                g[v][rev].flow -= adjustedFlow;
                return adjustedFlow;
            }
        }
        return 0;
    }
    
    ll compute(bool resetFlow = true){
        if (resetFlow) {
            for(ll i=0; i<sz; i++) {
                for(auto &[v, flow, cap, rev] : g[i]) {
                    flow = 0;
                }
            }
            maxFlow = 0;
        }
        while(bfs()){
            for(ll i=0; i<sz; i++) vis[i] = 0;
            while(ll inc = dfs(src, INT32_MAX)) maxFlow += inc;
        }
        return maxFlow;
    }
};