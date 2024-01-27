## Convex Hull Trick 

Used for DP otimizations that has values converted to lines

**Solves:**

    ax + b
    cx^2 + ax + b (ignore cx^2 if c is independent)

```cpp
// Convex Hull Trick Dinamico
//
// Para float, use LLINF = 1/.0, div(a, b) = a/b
//
// update(x) atualiza o ponto de intersecao da reta x
// overlap(x) verifica se a reta x sobrepoe a proxima
// add(a, b) adiciona reta da forma ax + b
// query(x) computa maximo de ax + b para entre as retas
// se quiser computar o minimo, eh soh fazer (-a)x + (-b)
//
// O(log(n)) amortizado por insercao
// O(log(n)) por query

struct Line {
	mutable ll a, b, p;
	bool operator<(const Line& o) const { return a < o.a; }
	bool operator<(ll x) const { return p < x; }
};

struct DynamicCHT : multiset<Line, less<>> {
	ll div(ll a, ll b) { 
		return a / b - ((a ^ b) < 0 and a % b);
	}
	
	void update(iterator x) {
		if (next(x) == end()) x->p = LLINF;
		else if (x->a == next(x)->a) x->p = x->b >= next(x)->b ? LLINF : -LLINF;
		else x->p = div(next(x)->b - x->b, x->a - next(x)->a);
	}

	bool overlap(iterator x) {
		update(x);
		if (next(x) == end()) return 0;
		if (x->a == next(x)->a) return x->b >= next(x)->b;
		return x->p >= next(x)->p;
	}
		
	void add(ll a, ll b) {
		auto x = insert({a, b, 0});
		while (overlap(x)) erase(next(x)), update(x);
		if (x != begin() and !overlap(prev(x))) x = prev(x), update(x);
		while (x != begin() and overlap(prev(x))) 
			x = prev(x), erase(next(x)), update(x);
	}
	
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
};
```
