## Combinatorics Theory

### Lucas' Theorem

By definition, *n choose k* **($C ^n_k$)** is equal to:

    n! / (k! * (n-k)!), 0 <= k <= n
    0, otherwise


    C(n, k) mod p = C(n_i, k_i) * C(n_i-1, k_i-1) * ... * C(n_0, k_0) mod p

**Whereas:**

*n_i* and *k_i* are the i-th digit of their respective numbers written in base *p*. All terms need to smaller than *p* by definition.

**Example:**

    10 in base 3 = 1*3^2 + 0*3^1 + 1*3^0
    n_2 = 1
    n_1 = 0
    n_0 = 1

### Stars and Bars 

Also called "sticks and stones", "balls and bars", and "dots and dividers"

$ x_1 + x_2 + ... + x_n = m $

**Example: (n = 3, m = 7)**

★ ★ ★ ★ | ★ | ★ ★

*n* Groups;
*n-1* Bars;
*m* Stars;

**Solution**

*C(n+m-1, n-1) = (n+m-1)! / ( (n-1)! (m)! )*

**Proof**

Elements = Bars + Stars = (n-1) + m = n+m-1;
Repetition of Bars = n-1
Repetition of Stars = m

Therefore, it's a simple *permutation with repetition*.

$ P^{(n+m-1)}_{(n-1,m)} = C (n+m-1, m)$

### Burside Lemma

necklaces with *n* pearls and *k* colors:

$\frac{1}{n} \sum_{i=1}^n k^{\gcd(i, n)}$