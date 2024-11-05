/**
 * Author: Wallace
 * Date: 04/11/2024
 * Description: By precomputing, for each position, and, for each power of two, the value of a range, 
 * Anwer quickly any query with assossiative operations. 
 * Using power before index, makes the implementation more cache friendly and much faster.
 * Time: O(n \log{n}) for precomputing, O(1) or O(\log{n}) per query
 * Status: Tested (https://judge.yosupo.jp/submission/247103, https://judge.yosupo.jp/submission/247104)
 */

// computes the MSB = the floor of log2(i) in O(1)
// MSB(0) = -1
#define MSB(i) (64 - 1 - __builtin_clzll(i)) // long long

template<class T>
struct SparseTable {

    // the function must be associative !!! 
    T f(T a, T b) {
        return min(a, b);
    }

    ll n, logn;
    vector<vector<T>> st; // st[a][i] covers range [i, i+2^a)

    // 0-idx: [0, n)
    SparseTable(vector<T> &v) : n(v.size()) {
        logn = MSB(n) + 1;

        st = vector(logn, vector(n, T()));

        for(ll i=0; i<n; i++) {
            st[0][i] = v[i];
        }

        for(ll a=1; a<logn; a++) {
            for(ll i=0; i + (1 << a) <= n; i++) {
                st[a][i] = f(
                    st[a-1][i],
                    st[a-1][i + (1 << (a-1))]
                );
            }
        }
    }

    // constant query for functions with Idempotence (overlap friendly)
    T query(ll l, ll r) { // query for [l, r] in O(1)
        if (l == r) return st[0][l];
        ll a = MSB(r-l+1);
        return f(
            st[a][l], 
            st[a][r - (1 << a) + 1]
        );
    }

    // logarithmic query for functions without Idempotence
    T query(ll l, ll r) { // query for [l, r] in O(log(n))
        T ans = {INF}; // define the correct default null value here !!
        for(ll a=logn-1; a>=0; a--) {
            if ((1 << a) <= (r-l+1)) {
                ans = f(ans, st[a][l]);
                l += 1 << a;
            }
        }
        return ans;
    }
};