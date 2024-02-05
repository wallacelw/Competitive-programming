/**
 * Author: Wallace
 * Date: 04/02/2024
 * Description: if low[v] >= tin[u], u is an articulation points
 * The root is a corner case 
 * Time: O(V+E)
 */

vector<vll> g(MAX);
ll timer = 1;
ll low[MAX], tin[MAX], isAP[MAX];
// when vertex i is removed from graph
// isAP[i] is the quantity of new disjoint components created
// isAP[i] >= 1 {i is a Articulation Point} 
void dfs(ll u, ll p = -1) {
    low[u] = tin[u] = timer++;

    for(auto v : g[u]) if (v != p) {
        if (tin[v]) // visited
            low[u] = min(low[u], tin[v]);
        else { // not visited
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            
            if (low[v] >= tin[u])
                isAP[u]++;
        }
    }

    // corner case: root
    if (p == -1 and isAP[u]) isAP[u]--;
}

void findAP(ll n) {
    for(ll i=1; i<=n; i++) if (!tin[i])
        dfs(i);
}