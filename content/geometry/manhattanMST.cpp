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

template<class T> struct Point {
    T x, y;

    typedef Point P;
    explicit Point(T xx=0, T yy=0) : x(xx), y(yy) {}
    P operator-(P p) const { return P(x-p.x, y-p.y); }
};

typedef Point<ll> P;

vector<array<ll, 3>> manhattanMST(vector<P> ps) {
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
				P d = ps[i] - ps[j];
				if (d.y > d.x) break;
				edges.pb({d.y + d.x, i, j});
			}
			sweep[-ps[i].y] = i;
		}
		for (P& p : ps) if (k & 1) p.x = -p.x; else swap(p.x, p.y);
	}
	return edges;
}
