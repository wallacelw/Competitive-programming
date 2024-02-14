/**
 * Author: Wallace
 * Date: 14/02/2024
 * Description: Also counts the numbers of shortest paths, the minimum and maximum number 
 * of edges transversed in any shortest path. 
 * Time: O( (V+E) \log{V} )
 * Status: Tested (https://cses.fi/problemset/result/8472340/)
 */

priority_queue<pll, vector<pll>, greater<pll>> pq; // min pq
vector<vector<pll>> g(MAX);
vector<ll> d(MAX, INF), ways(MAX, 0), mx(MAX, -INF), mn(MAX, INF);
// INF = INT64_MAX

void dijkstra(ll start){
    pq.push({0, start});
    ways[start] = 1;
    d[start] = mn[start] = mx[start] = 0;

    while( !pq.empty() ){
        auto [p1, u] = pq.top(); pq.pop();
        if (p1 > d[u]) continue;
        for(auto [v, p2] : g[u]){
            // reset info, shorter path found, previous ones are discarted
            if (d[u] + p2 < d[v]){
                d[v] = d[u] + p2;
                ways[v] = ways[u];
                mx[v] = mx[u]+1;
                mn[v] = mn[u]+1;

                pq.push({d[v], v});
            }
            // same distance, different path, update info
            else if (d[u] + p2 == d[v]) { 
                ways[v] = (ways[v] + ways[u]) % MOD;
                mn[v] = min(mn[v], mn[u]+1);
                mx[v] = max(mx[v], mx[u]+1);
            }
        }
    }
}