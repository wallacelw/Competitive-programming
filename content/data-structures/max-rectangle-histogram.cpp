/**
 * Author: Wallace
 * Date: 13/03/2024
 * Description: solves the problem of finding the maximum rectangle area
 * in a grid setting (different widths, different heights)
 * Time: O(n m)
 * Status: Tested (https://cses.fi/problemset/result/8723636/)
 */

// Example Problem: You are given a map of a forest where some squares are empty and some squares have trees.
// What is the maximum area of a rectangular building that can be placed in the forest so that no trees must be cut down?

ll maxRectangleHistogram(vector<ll> x) { // O(n)
    
    // add an end point with heigth 0 to compute the last rectangles
    x.pb(0);

    ll area = 0;
    ll n = x.size();
    stack<pll, vector<pll>> st; // {maxLeft, height for this rectangle}

    for(ll i=0; i<n; i++) {
        ll h = x[i];
        ll maxLeft = i;

        while(!st.empty() and st.top().ss >= h) {
            auto [maxLeft2, h2] = st.top(); st.pop();

            // compute the area of the de-stacked rectangle
            area = max(area, (i-maxLeft2)*h2 );

            // extend current rectangle width with previous
            maxLeft = maxLeft2;
        }

        st.push({maxLeft, h});
    }

    return area;
}

int32_t main(){ sws;
    ll n, m; cin >> n >> m;
 
    vector<vector<ll>> grid(n, vector<ll>(m));
 
    // convert the problem into N histogram subproblems, O(n m)
    for(ll i=0; i<n; i++) {
        for(ll j=0; j<m; j++) {
            char c; cin >> c;
            if (c == '*') grid[i][j] = 0;
            else if (i == 0) grid[i][j] = 1;
            else grid[i][j] = grid[i-1][j] + 1;
        }
    }
 
    ll area = 0;
    for(ll i=0; i<n; i++) {
        area = max(area, maxRectangleHistogram(grid[i]));
    }
 
    cout << area << endl;
} 