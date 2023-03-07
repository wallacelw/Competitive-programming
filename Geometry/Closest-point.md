## Minimum pair distance

Using **Divide and conquer**, it's possible to split the vector of points into two parts and solve each one separately. When merging, it's sufficient to compare only the *6* closest points for each point which is inside a delimited section. This section is defined by all points between *median.x-d* and *median.x+d*. *d* is the minimum distance of the two parts.  

```cpp
// xs = points sorted by X; ys = points sorted by Y
ll solve(vector<P> xs, vector<P> ys){ // -> O(n log2(n) )
    ll n = xs.size();
    
    // Base case, brute force
    if(n <= 3){
        ll d = xs[0].dist(xs[1]);
        for(ll i=0; i<n; i++)
            for(ll j=i+1; j<n; j++)
                d = min(d, xs[i].dist(xs[j]));
        return d;
    }
    
    // Divide
    ll mid = n/2;
    P median = xs[mid];
    vector<P> xsl(xs.begin(), xs.begin() + mid);
    vector<P> xsr(xs.begin() + mid, xs.end());

    vector<P> ysl, ysr;
    for(auto p : ys){
        if(p.x <= median.x) 
            ysl.push_back(p);
        else 
            ysr.push_back(p);
    }
 
    ll dl = solve(xsl, ysl);
    ll dr = solve(xsr, ysr);

    // Merge !!!
    ll d = min(dl, dr);
 
    vector<P> possible;
    for(auto p : ys){
        if(median.x-d < p.x and p.x < median.x+d)
            possible.push_back(p);
    }
 
    ll m = possible.size();
    for(ll i=0; i<m; i++){
        for(ll j=1; (j<=6 and j+i<m); j++){
            d = min(d, possible[i].dist(possible[i+j]));
        }
    }
 
    return d;
}

bool cmp_by_Y(P a, P b) { 
    return (eq(a.y, b.y) ? a.x < b.x : a.y < b.y); 
}
```