/**
 * Author: Wallace
 * Date: 03/11/2024
 * Description: 0/1 knapsack, each item can be taken only once, items have value and cost
 * Time: O(n*k)
 * Status: 
*/

ll dp[n+1][k+1];

// reset dp
for(ll i=0; i<=n; i++) {
    for(ll c=0; c<=k; c++) {
        dp[i][c] = -INF;
    }
}
dp[i][c] = 0;

// start from index 1
for(ll i=1; i<=n; i++) {
    for(ll c=0; c<=k; c++) {
        dp[i][c] = max(dp[i][c], dp[i-1][c]);

        if (c + cost[i] <= k) {
            dp[i][c + cost[i]] = max(
                dp[i][c + cost[i]], 
                dp[i-1][c] + val[i]
            );
        }
    }
}