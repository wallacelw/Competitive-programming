## Desarranjow
Distribui n números de forma que nenhum ocupa o lugar original
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