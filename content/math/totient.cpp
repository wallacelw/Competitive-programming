/**
 * Author: Wallace, CP-algorithms
 * Date: 7/10/2024
 * Description: Optimized using the same complexity as sieve of eratosthenes
 * Time: O(N \log{\log{N}})
 */

// tot[i] -> counts the number of integers [1, n] which are coprime to n
vector<int> totient(int n) {
    vector<int> tot(n + 1);
    iota(tot.begin(), tot.end(), 0);
    for (int i = 2; i <= n; i++) if (tot[i] == i) {
        for (int j = i; j <= n; j += i)
            tot[j] -= tot[j] / i;
    }
    return tot;
}