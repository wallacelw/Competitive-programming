/**
 * Author: Wallace
 * Date: 05/11/2024
 * Description: Simple 2D prefix sum 0-idx
 * Time: O(N * M) to build, O(1) to query
 */

template<class T>
struct PS2D {

    ll n, m;
    vector<vector<T>> ps;

    // 0-idx
    PS2D(vector<vector<T>> &grid) 
        : n(grid.size()), m(grid[0].size()) {

        ps = grid;

        for(ll i=0; i<n; i++) {
            for(ll j=0; j<m; j++) {

                if (i > 0) ps[i][j] += ps[i-1][j];
                if (j > 0) ps[i][j] += ps[i][j-1];

                if (i > 0 and j > 0) 
                    ps[i][j] -= ps[i-1][j-1];
            }
        }
    }

    ll query(ll i1, ll i2, ll j1, ll j2) {
        ll sum = ps[i2][j2];
        if (i1 > 0) sum -= ps[i1-1][j2];
        if (j1 > 0) sum -= ps[i2][j1-1];
        if (i1 > 0 and j1 > 0) sum += ps[i1-1][j1-1];
        return sum;
    }
};