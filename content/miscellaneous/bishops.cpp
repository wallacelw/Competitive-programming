/**
 * Author: Wallace, cp-algo
 * Date: 07/05/2024
 * Description: Count the number of ways k bishops can be placed on an n $\times$ n chessboard
 * so that no two bishops attack each other.
 * Time: O(n^3)
 * Status: Tested (https://cses.fi/problemset/result/9199691/)
*/

// Solution Notes:
// Give a odd index to black diagonals, and even index to white diagonals
// by symmetry, index the '/' diagonals. 
// dp[i][j] -> the number of ways to place j bishops considering the first i diagonals of the same color
// squares(d) -> how many squares are in this diagonal of index i
using mint = Z<MOD>;

ll squares(ll d) {
    if (d & 1) return d/4 * 2 + 1;
    else return (d-1)/4 * 2 + 2;
}

int32_t main(){ sws;
    ll n, k; cin >> n >> k;

    vector<vector<bool>> vis(2*n, vector<bool>(2*n, false));
    vector<vector<mint>> tab(2*n, vector<mint>(2*n, 0));
    
    function<mint (ll, ll)> dp = [&](ll i, ll j) -> mint {
        if (j >= 2*n) return 0;
        if (j == 0) return 1;
        if (i <= 0) return 0;

        if (vis[i][j]) return tab[i][j];
        vis[i][j] = 1;

        mint ans = dp(i-2, j) + dp(i-2, j-1) * (squares(i) - (j-1));
        return tab[i][j] = ans;
    };

    mint ans = 0;
    for(ll j=0; j<=k; j++) {
        ans += dp(2*n-1, j) * dp(2*n-2, k-j);
    }

    cout << ans << endl;
}