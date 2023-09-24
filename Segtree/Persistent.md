## Persistent

Sempre que ocorre um update, cria log(N) novas areas e uma nova raiz com id x

```cpp
const ll N = 2e5+10; // max_array_size

// x = time (id da raiz desejada)
// l, r = query range
// lx, rx = internal idx
// query(a, b, x) retorna a query de [a, b] na versao x
// update(i, val, x) faz um update v[i]=val partindo da versao x, criando uma nova versao e retornando seu id

namespace ST {
    ll left[120*N], right[120*N], t[120*N];
    ll idx = 1, null = 0; // null = identity/null value

    ll f(ll a, ll b) {
        return a+b;
    }

    ll build(vector<ll> &v, ll lx=0, ll rx=N-1) { // 0-idx
        ll y = idx++;
        if (lx == rx) {
            if (lx < (ll)size(v)) t[y] = v[lx];
            else t[y] = null;
            return y;
        }
        ll mid = (lx+rx)/2;
        left[y] = build(v, lx, mid);
        right[y] = build(v, mid+1, rx);
        t[y] = f(t[left[y]], t[right[y]]);
        return y;
    }
    
    ll query(ll l, ll r, ll x, ll lx=0, ll rx=N-1) {
        if (l <= lx and rx <= r) return t[x];
        if (r < lx or rx < l) return null;

        ll mid = (lx+rx)/2;
        auto ansl = query(l, r, left[x], lx, mid);
        auto ansr = query(l, r, right[x], mid+1, rx);
        return f(ansl, ansr);
    }

    ll update(ll i, ll val, ll x, ll lx=0, ll rx=N-1) {
        ll y = idx++;
        if (lx == rx) {
            t[y] = val;
            return y;
        }
        ll mid = (lx+rx)/2;
        if (lx <= i and i <= mid) {
            left[y] = update(i, val, left[x], lx, mid);
            right[y] = right[x];
        }
        else {
            left[y] = left[x];
            right[y] = update(i, val, right[x], mid+1, rx);
        }
        t[y] = f(t[left[y]], t[right[y]]);
        return y;
    }
};
```