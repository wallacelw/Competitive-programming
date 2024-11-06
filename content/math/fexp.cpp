/**
 * Author: Quirino
 * Date: 06/11/2024
 * Description: Iterative fast exponential
 * Time: O(\log{e})
 * Status: just copied
 */

// Fast Exponentiation {{{
int fexp(int b, int e) {
  b %= MOD;
  int ans = 1;
  while (e) {
    if (e & 1) (ans *= b) %= MOD;
    e >>= 1;
    (b *= b) %= MOD;
  }
  return ans;
}
//}}}