## Merge sort

Merge Sort with number of inversions counter.

```cpp
int merge(vector<int> &v, int l, int mid, int r){
    int i=l, j=mid+1, swaps=0;
    vector<int> ans;

    while(i <= mid or j <= r){

        if(j > r or (v[i] <= v[j] and i<=mid)){
            ans.push_back(v[i]);
            i++;
        }
        if(i > mid or (v[j] < v[i] and j <= r)){
            ans.push_back(v[j]);
            j++;
            swaps = swaps + abs(mid+1-i);
        }
    }
    
    for(int i=l; i<=r; i++)
        v[i] = ans[i-l];

    return swaps;
}

int merge_sort(vector<int> &v, vector<int> &ans, int l, int r){
    if(l==r){
        ans[l] = v[l];
        return 0;
    }


    int mid = (l+r)/2, swaps = 0;
    swaps += merge_sort(v, ans, l, mid);
    swaps += merge_sort(v, ans, mid+1, r);
    swaps += merge(ans, l, mid, r);

    return swaps;
}
```

### Updated

```cpp
#include <bits/stdc++.h>
using namespace std;
#define sws cin.tie(0)->sync_with_stdio(0)
 
#define endl '\n'
#define ll long long
#define ld long double
#define vll vector<ll>
#define vld vector<ld>
#define ff first
#define ss second
#define pll pair<ll, ll>
#define tlll tuple<ll, ll, ll>
#define vpll vector<pll>
#define pb push_back
 
#define teto(a, b) ((a+b-1)/(b))
#define LSB(i) ((i) & -(i))
#define db(a) " [ " << #a << " = " << a << " ] "
template <typename... A> void dbg(A const&... a) { ((cerr << db(a)), ...); cerr << endl; }

const int MAX = 2e5+10;
const long long MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const long long LLINF = 0x3f3f3f3f3f3f3f3f;
const long double EPS = 1e-7;
const long double PI = acos(-1);

ll merge(vll &v, ll l, ll r) {
    ll i = l, mid = (l+r)/2, j = mid+1, swaps = 0;
    vll ans;

    while(i <= mid or j <= r){

        if(j > r or (v[i] <= v[j] and i <= mid)) {
            ans.pb(v[i]);
            i++;
        }
        if(i > mid or (v[j] < v[i] and j <= r)){
            ans.pb(v[j]);
            j++;
            swaps += mid+1 - i;
        }
    }
    
    for(ll k=l; k<=r; k++)
        v[k] = ans[k-l];

    return swaps;
}

ll merge_sort(vll &v, ll l, ll r){
    if(l == r) return 0;

    ll mid = (l+r)/2, swaps = 0;
    swaps += merge_sort(v, l, mid);
    swaps += merge_sort(v, mid+1, r);
    swaps += merge(v, l, r);

    return swaps;
}

int32_t main() { sws;
    ll t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        vll x(n);
        for(ll i=0; i<n; i++) cin >> x[i];
        cout << merge_sort(x, 0, n-1) << endl;
        for(ll i=0; i<n; i++) cout << x[i] << " ";
        cout << endl;
    }
}   
```