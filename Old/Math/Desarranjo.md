## Derangement (Desarranjo)

Distribui n números de forma que nenhum ocupa o lugar original.


In combinatorial mathematics, a derangement is a permutation of the elements of a set, such that no element appears in its original position. In other words, a derangement is a permutation that has no fixed points.

#### Counting derangements 

The number of derangements of a set of size n is known as the subfactorial of n or the n-th derangement number or n-th de Montmort number.

A subfactorial is noted as: 

**!n** = (n-1) * ( !(n-1) + !(n-2) ), for n >= 2.

*!1* = 0
*!0* = 1 

```cpp

void process(){
    dp[0]=1;
    dp[1]=0;
    rep(i,2,MAXN){
        dp[i]=(i-1)*(dp[i-1]+dp[i-2]);
        dp[i]%=MOD;
    }
}

```