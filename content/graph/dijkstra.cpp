/**
 * Author: Wallace
 * Date: 14/02/2024
 * Description: By keeping track of the distances sorted using an priority queue,
 * transverse only using the smallest distances.
 * Time: O( (V+E) \log{V} )
 */

priority_queue<pll, vector<pll>, greater<pll>> pq; // min pq
vector<vector<pll>> g(MAX);
vector<ll> d(MAX, INF);

void dijkstra(ll start){
    pq.push({0, start});
    d[start] = 0;

    while( !pq.empty() ){
        auto [p1, u] = pq.top(); pq.pop();
        if (p1 > d[u]) continue;
        for(auto [v, p2] : g[u]){
            if (d[u] + p2 < d[v]){
                d[v] = d[u] + p2;
                pq.push({d[v], v});
            }
        }
    }
}
