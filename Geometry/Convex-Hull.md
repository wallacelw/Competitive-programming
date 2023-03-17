## Andrew's monotone chain convex hull algorithm

**Complexity:** O(n * log (n))

```cpp
vector<P> convex_hull(vector<P>& v){
    vector<P> hull;
    sort(v.begin(), v.end()); // sort by x, then by y
    for(ll rep=0; rep<2; rep++){ // top part, then, bottom part 
        ll old_size = hull.size();
        for(P next : v){
            while(hull.size() - old_size >= 2){
                P prev = hull.end()[-2]; // hull[size - 2]
                P mid = hull.end()[-1]; // hull[size - 1]
                if(prev.cross(mid, next) <= 0) // 0 collinear, <0 mid on the left of next
                    break;
                hull.pop_back(); // stack behaviour
            }
            hull.push_back(next);
        }
        hull.pop_back();
        reverse(v.begin(), v.end());
    }
    return hull;
}
```
