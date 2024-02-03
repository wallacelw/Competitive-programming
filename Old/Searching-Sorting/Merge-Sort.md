## Merge sort

Merge Sort with number of inversions counter.

Directly updates the *v* vector. Also return the number of swaps (inversions).

**O(N log(N))**

```cpp

// O(N)
ll merge(vll &v, ll l, ll r) {
    ll i = l, mid = (l+r)/2, j = mid+1, swaps = 0;
    vll ans;

    while(i <= mid or j <= r) {

        if(j > r or (v[i] <= v[j] and i <= mid)) {
            ans.pb(v[i]);
            i += 1;
        }

        else if(i > mid or (v[j] < v[i] and j <= r)){
            ans.pb(v[j]);
            j += 1;
            swaps += (mid-1)+1; // mid-i+1 = elements remaining in the left subarray (same number of elements that will be swaped to the right)
        }
    }
    
    for(ll k=l; k<=r; k++) v[k] = ans[k-l];

    return swaps;
}

// O(N log2(N))
ll merge_sort(vll &v, ll l, ll r){
    if(l == r) return 0;

    ll mid = (l+r)/2, swaps = 0;
    swaps += merge_sort(v, l, mid);
    swaps += merge_sort(v, mid+1, r);
    swaps += merge(v, l, r);

    return swaps;
}
```