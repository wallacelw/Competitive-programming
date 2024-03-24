/**
 * Author: Wallace
 * Date: 24/03/2024
 * Description: By keeping track of the distances sorted using an priority queue of candidates.
 * if an edge can reduce the current min distance, insert into the priority queue.
 * ONLY when the vertice is dequeued and its cost is <= d[u], it is in fact a part of a shortest path
 * Time: O( (V+E) \log{V} )
 */

priority_queue<pll, vector<pll>, greater<pll>> pq; // min pq
vector<vector<pll>> g(MAX);
vector<ll> d(MAX, INF);

void dijkstra(ll start){
    pq.push({0, start});
    d[start] = 0;

    while(!pq.empty()){

        auto [cost, u] = pq.top(); pq.pop();
        if (cost > d[u]) continue;

        for (auto [v, w] : g[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }
}
