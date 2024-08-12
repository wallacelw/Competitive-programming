/**
 * Author: Wallace
 * Date: 11/08/2024
 * Description: By precomputing for each position and each power of two the value of a range, 
 * Anwer quickly any query.
 * Time: O(n \log{n}) for precomputing, O(1) or O(\log{n}) per query
 * Status: Tested (https://judge.yosupo.jp/submission/227649, https://judge.yosupo.jp/submission/227651)
 */

// computes the MSB = the floor of log2(i) in O(1)
// MSB(0) = -1
#define MSB(i) (64 - 1 - __builtin_clzll(i))

template<class T>
struct SparseTable {

    // the function must be associative !!! 
    T f(T a, T b) {
        return min(a, b);
    }

    ll n, m;
    vector<vector<T>> st; // st[j][i] covers range [i, i+2^j)

    // 0-idx: [0, n)
    SparseTable(vector<T> &v) : n(v.size()), st({v}) {
        m = MSB(n);

        for(ll k=1; k<=m; k++) {
            st.emplace_back(n);
            for(ll i=0; i + (1LL << k) <= n; i++) {
                st[k][i] = f(
                    st[k-1][i], 
                    st[k-1][i + (1LL << (k-1))]
                );
            }
        }
    }

    // constant query for functions with Idempotence (overlap friendly)
    T query(ll l, ll r) { // query for [l, r] in O(1)
        if (l == r) return st[0][l];
        ll k = MSB(r-l+1);
        return f(
            st[k][l], 
            st[k][r - (1LL << k) + 1]
        );
    }

    // logarithmic query for functions without Idempotence
    T query(ll l, ll r) { // query for [l, r] in O(log)
        T ans = {}; // define the correct default null value here
        for(ll k=m; k>=0; k--) {
            if ((1LL << k) <= (r-l+1)) {
                ans = f(ans, st[k][l]);
                l += 1LL << k;
            }
        }
        return ans;
    }
};