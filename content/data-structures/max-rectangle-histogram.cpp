/**
 * Author: Wallace
 * Date: 13/03/2024
 * Description: solves the problem of finding the maximum rectangle area
 * in a histogram setting (same bottom, different heights).
 * Time: O(n)
 */

// Example Problem: A fence consists of n vertical boards. The width of each board is 1 and their heights may vary.
// You want to attach a rectangular advertisement to the fence. What is the maximum area of such an advertisement?

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
    ll n; cin >> n;
    vector<ll> x;
    for(ll i=0, a; i<n; i++) cin >> a, x.pb(a);
    cout << maxRectangleHistogram(x) << endl;
}  