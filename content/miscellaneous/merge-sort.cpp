/**
 * Author: Pedro, Wallace
 * Date: 07/07/2024
 * Description: Sort a vector V and compute the number of inversions needed to sort it
 * (the same number of swaps in a bubble sort)
 * Time: O(N) for merge, O(N \log(N)) for merge-sort
*/

ll merge(vector<ll> &v, ll l, ll r) {
    ll i = l, mid = (l+r)/2, j = mid+1, swaps = 0;
    vector<ll> ans;

    while(i <= mid or j <= r) {

        if(j > r or (v[i] <= v[j] and i <= mid)) {
            ans.pb(v[i]);
            i += 1;
        }
        
        else if(i > mid or (v[j] < v[i] and j <= r)){
            ans.pb(v[j]);
            j += 1;
            swaps += (mid-i)+1; 
            // mid-i+1 = elements remaining in the left subarray 
            // (same number of elements that will be swaped to the right)
        }
    }
    
    for(ll k=l; k<=r; k++) v[k] = ans[k-l];

    return swaps;
}

// sort [l, r] (inclusive), 0-idx
ll merge_sort(vector<ll> &v, ll l, ll r){ 
    if(l == r) return 0;

    ll mid = (l+r)/2, swaps = 0;
    swaps += merge_sort(v, l, mid);
    swaps += merge_sort(v, mid+1, r);
    swaps += merge(v, l, r);

    return swaps;
}