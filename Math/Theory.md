## Basic Knowledge

    "a is divisible by b" or
    "a is a multiple of b" or
    "b is a divisor of a" or
    "b is a factor of a" or
    "b divides a" ( b|a )
    => a % b == 0

    "a1, a2 are divisible by b"
    => gcd(a1, a2) % b == 0

    "a is divisible by b1 and b2"
    => a % lcm(b1, b2) == 0

    "a is divisible by b and b is divisible by c"
    => a % b == 0
    => b % c == 0
    => a % c == 0 (transitivity)

### Greatest Common Divisor (GCD) 

    gcd(a) = a
    gcd(a, b, c) = gcd( gcd(a, b), c ) 
    gcd(a, b) = (a*b) / lcm(a, b)

### Least Commom Multiple (LCM)

    lcm(a) = a
    lcm(a, b, c) = lcm( lcm(a, b), c ) 
    lcm(a, b) = (a*b) / gcd(a, b)

### Observation

std-c++17 implements gcd() function, which works correcly for negative numbers as well.

**For negatives numbers, the following is true:**

    gcd(a,b) = gcd(−a,−b) = gcd(−a,b) = gcd(a,−b)

## Closed Formulas related to divisors of a number

Let **n** be a number represented by it's prime factors $p_i$ and respective exponents $e_i$:

**d(n) = k = t = number of divisors**

![Quantidade](../../Aux-Images/CntDivisors.png)
![Soma](../../Aux-Images/SumDivisors.png)
![Produto](../../Aux-Images/ProductDivisors.png)

## Binomial Coeficients

By definition, *n choose k* **($C ^n_k$)** is equal to:

    n! / (k! * (n-k)!), 0 <= k <= n
    0, otherwise

### Lucas' Theorem

    C(n, k) mod p = C(n_i, k_i) * C(n_i-1, k_i-1) * ... * C(n_0, k_0) mod p

**Whereas:**

*n_i* and *k_i* are the i-th digit of their respective numbers written in base *p*. All terms need to smaller than *p* by definition.

**Example:**

    10 in base 3 = 1*3^2 + 0*3^1 + 1*3^0
    n_2 = 1
    n_1 = 0
    n_0 = 1