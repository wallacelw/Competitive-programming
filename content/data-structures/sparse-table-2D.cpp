/**
 * Author: Wallace
 * Date: 05/11/2024
 * Description: 2D sparse table
 * Time: O(n m \log{n} \log{m}) for precomputing, O(1) per query
 * Status: Tested, but it is slow
 */

// computes the MSB = the floor of log2(i) in O(1)
// MSB(0) = -1
#define MSB(i) (64 - 1 - __builtin_clzll(i))

template<class T>
struct SparseTable2D {

    // the function must be associative !!
    T f(T a, T b) {
        return gcd(a, b);
    }
    T f(vector<T> vec) {
        T ans = {0}; // null value
        for(auto val : vec) ans = f(ans, val);
        return ans;
    }

    ll n, m; // n = rows, m = columns
    ll logn, logm;

    // st[a][b][i][j] covers:
    // rows [i, i + 2^a)
    // columns [j, j + 2^b)
    vector<vector<vector<vector<T>>>> st;

    // 0-idx: a [0, logn], b [0, logm], i [0, n), j [0, m)
    SparseTable2D(vector<vector<T>> &grid) 
        : n(grid.size()), m(grid[0].size()) {

        logn = MSB(n) + 1, logm = MSB(m) + 1;

        st = vector(logn, vector(logm, vector(n, vector(m, T()))));

        // copy original contents
        for(ll i=0; i<n; i++) {
            for(ll j=0; j<m; j++) {
                st[0][0][i][j] = grid[i][j];
            }
        }

        // compute 1D sparse table for each column j
        for(ll a=1; a<logn; a++) {
            for(ll i=0; i + (1 << a) <= n; i++) {
                for(ll j=0; j<m; j++) {
                    st[a][0][i][j] = f(
                        st[a-1][0][i][j],
                        st[a-1][0][i + (1 << (a-1))][j]
                    );
                }
            }
        }

        // compute 1D sparse table compute for each row i
        for(ll b=1; b<logm; b++) {
            for(ll i=0; i<n; i++) {  
                for(ll j=0; j + (1 << b) <= m; j++) {
                    st[0][b][i][j] = f(
                        st[0][b-1][i][j],
                        st[0][b-1][i][j + (1 << (b-1))]
                    );
                }
            }
        }

        // merge 
        for(ll a=1; a<logn; a++) {
            for(ll b=1; b<logm; b++) {
                for(ll i=0; i + (1 << a) <= n; i++) {
                    for(ll j=0; j + (1 << b) <= m; j++) {
                        st[a][b][i][j] = f({
                            st[a-1][b-1][i][j],
                            st[a-1][b-1][i + (1 << (a-1))][j],
                            st[a-1][b-1][i][j + (1 << (b-1))],
                            st[a-1][b-1][i + (1 << (a-1))][j + (1 << (b-1))]
                        });
                    }
                }
            }
        }
    }

    // constant query for functions with Idempotence (overlap friendly)
    // query for i [i1, i2] and j [j1, j2]
    T query(ll i1, ll i2, ll j1, ll j2) { 
        
        ll a = MSB(i2-i1+1), b = MSB(j2-j1+1);

        return f({
            st[a][b][i1][j1],
            st[a][b][i2 - (1 << a) + 1][j1],
            st[a][b][i1][j2 - (1 << b) + 1],
            st[a][b][i2 - (1 << a) + 1][j2 - (1 << b) + 1]
        });
    }
};