/**
 * Author: Wallace
 * Date: 04/11/2024
 * Description: By precomputing, for each position, and, for each power of two, the value of a range, 
 * Anwer quickly any query with assossiative operations.
 * Time: O(n \log{n}) for precomputing, O(1) or O(\log{n}) per query
 * Status: Tested (https://judge.yosupo.jp/submission/247093, https://judge.yosupo.jp/submission/247097)
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
    vector<vector<T>> st; // st[i][a] covers range [i, i+2^a)

    // 0-idx: [0, n)
    SparseTable(vector<T> &v) : n(v.size()) {
        logn = MSB(n) + 1;

        st = vector(n, vector(logn, T()));

        for(ll i=0; i<n; i++) {
            st[i][0] = v[i];
        }

        for(ll a=1; a<logn; a++) {
            for(ll i=0; i + (1 << a) <= n; i++) {
                st[i][a] = f(
                    st[i][a-1],
                    st[i + (1 << (a-1))][a-1]
                );
            }
        }
    }

    // constant query for functions with Idempotence (overlap friendly)
    T query(ll l, ll r) { // query for [l, r] in O(1)
        if (l == r) return st[l][0];
        ll a = MSB(r-l+1);
        return f(
            st[l][a], 
            st[r - (1 << a) + 1][a]
        );
    }

    // logarithmic query for functions without Idempotence
    T query(ll l, ll r) { // query for [l, r] in O(log(n))
        T ans = {0}; // define the correct default null value here !!
        for(ll a=logn-1; a>=0; a--) {
            if ((1 << a) <= (r-l+1)) {
                ans = f(ans, st[l][a]);
                l += 1 << a;
            }
        }
        return ans;
    }
};