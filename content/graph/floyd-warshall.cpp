/**
 * Author: Wallace
 * Date: 14/02/2024
 * Description: By using an auxiliar vertice, check if a smaller path
 * exists between a pair (u, v) of vertices, if so, update minimum distance.
 * Time: O(V^3)
 */

// N < sqr3(1e8) = 460
ll N = 200;

// d[u][v] = INF (no edge)
vector<vll> d(N+1, vll(N+1, INF));

void floydWarshall() { // O(N^3)
    for(ll i=1; i<=N; i++) d[i][i] = 0;

    for(ll aux=1; aux<=N; aux++)
        for(ll u=1; u<=N; u++)
            for(ll v=1; v<=N; v++)
                if (d[u][aux] < INF and d[v][aux] < INF)
                    d[u][v] = min(d[u][v], d[u][aux] + d[v][aux]);
}