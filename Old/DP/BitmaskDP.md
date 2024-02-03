## Bitmask DP

use a bitmask of chosen itens to be a state of the DP

**Example**:

https://cses.fi/problemset/task/1653/

```cpp
int32_t main(){
    ll n, x; cin >> n >> x;
    vll a(n);

    for(ll i=0; i<n; i++) cin >> a[i];

    // dp[bitmask of selected people] -> {elevator rides, weight occupied}
    vpll dp( (1 << n) , {INF, INF}); 
    dp[0] = {1, 0};

    for(ll mask=0; mask< (1<<n); mask++) {
        for(ll j=0; j<n; j++) {
            if (mask & (1 << j)) {
                ll bit = mask ^ (1 << j);

                // there is room for one more weight
                if (dp[bit].ss + a[j] <= x)
                    dp[mask] = min( dp[mask], {dp[bit].ff, dp[bit].ss + a[j]} );
                
                // add an elevator ride, and create a new one with just one person
                else 
                    dp[mask] = min( dp[mask], {dp[bit].ff + 1, a[j]} );
            }
        }
    }
    cout << dp[(1 << n) - 1].ff << endl;
}
```

### Broken Profile

Solves problem where is needed to count the ways of filling a *n* x *m* grid with dominos/tilings of specific size.

*Example:* Fill *n* x *m* with 2x1 dominos or 1x2 dominos -> https://cses.fi/problemset/task/2181

1 ≤ n ≤ 10 (rows)
1 ≤ m ≤ 1000 (collums)

#### States

**dp[j][p]** -> numbers of ways of filling first *j* columns completely with dominoes (without leaving any block as empty) and leaving the profile *p* for the *j+1* collum.

*j* = collums completely filled.
*p* = bitmask representation of the "profile" for the j+1 collum.

Note that, the (j+1) th column should not contain a complete domino (in the vertical), those types will be included in the dp transition from j+1 to j+2.

<img src="../Aux-Images/BrokenProfile1.png" alt="Valido" width="400"/>
<img src="../Aux-Images/BrokenProfile2.png" alt="Invalido" width="400"/>

#### Transitions

**Initial States:**
```cpp
dp[i = 0][p = 0] = 1
dp[i = 0][p != 0] = 0
```

From a specific **dp[j][q]**, with profile *q* for the *j-th* collum and all the collums before filled, it's possible to generate several **dp[j+1][p]** just by adding vertical and horizontal tiles.

**Final Answer:** dp[m][0]

```cpp
// grid size
ll dp[1010][1 << 11];
ll n, m;
// n is the num of rows, m is the num of collums

// check if i'th bit of q is occupied
bool occupied(ll i, ll q) {
    return q & (1 << (i-1));
}

void solveBlock(ll i, ll j, ll p, ll q) {
    // from profile q -> generate profile p
    // OBS: q represents the profile of the j col, and p represents the profile of the j+1 col when j is filled;
    // i <= 10 (row); j <= 1000 (col)

    // found a new way to fill j, add this possibility
    if (i == n+1) {
        dp[j+1][p] = (dp[j+1][p] + dp[j][q]) % MOD;
        return;
    }

    // skip occupied block
    if ( occupied(i, q) ) {
        solveBlock(i+1, j, p, q);
        return;
    }
    
    // insert vertical tile
    if(i+1 <= n and !occupied(i+1, q)){
        solveBlock(i+2, j, p, q);
    }

    // insert horizontal tile
    if (j+1 <= m) {
        solveBlock(i+1, j, p^(1<<(i-1)), q);
    }
}

int32_t main(){ sws;
    cin >> n >> m;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1; // Initial Condition
    for(ll j=0; j<m; j++) { // each collum
        for(ll q=0; q < (1 << n); q++){ // each collum profile
            solveBlock(1, j, 0, q);
        }
    }
    cout << dp[m][0] << endl;
}   
```