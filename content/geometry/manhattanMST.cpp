/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-11-02
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Description: Given N points, returns up to 4*N edges, which are guaranteed
 * to contain a minimum spanning tree for the graph with edge weights w(p, q) =
 * |p.x - q.x| + |p.y - q.y|. Edges are in the form (distance, src, dst). Use a
 * standard MST algorithm on the result to find the final MST.
 * Time: O(N \log N)
 * Status: Stress-tested
 */


// import point struct (constructor and -operator)

vector<array<ll, 3>> manhattanMST(vector<point> ps) {
    vector<ll> id(size(ps));
    iota(id.begin(), id.end(), 0);
    vector<array<ll, 3>> edges;
    for(ll k=0; k<4; k++) {
        sort(id.begin(), id.end(), [&](ll i, ll j) {
            return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;
        });

        map<ll, ll> sweep;
        for (ll i : id) {
            for (auto it = sweep.lower_bound(-ps[i].y); it != sweep.end(); sweep.erase(it++)) {
                ll j = it->ss;
                point d = ps[i] - ps[j];
                if (d.y > d.x) break;
                edges.pb({d.y + d.x, i, j});
            }
            sweep[-ps[i].y] = i;
        }
        for (point& p : ps) if (k & 1) p.x = -p.x; else swap(p.x, p.y);
    }
    return edges;
}
