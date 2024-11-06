/**
 * Author: Quirino
 * Date: 06/11/2024
 * Description: Chinese Remainder Theorem
 * Time: O(\log{ min(a, b) }) (probably due to extgcd)
 * Status: just copied
 */

// Chinese Remainder Theorem {{{
struct CRT {
  int A, M;
  CRT() : A(0), M(1) {}
  CRT(int A, int M) : A(A), M(M) {}
  CRT operator*(CRT const& C) {
    auto [g, x, y] = ext_gcd(M, C.M);
    if ((A - C.A) % g) A = -1;
    if (A == -1 || C.A == -1) return CRT(-1, 0);
    int L = M/g*C.M;
    int ans = A + (x * (C.A-A))/g % (C.M/g) * M;
    return CRT((ans % L + L) % L, L);
  }

  int count(int r) const {
    if (r < 0) return 0;
    int total = r/M;
    r %= M;
    if (r >= A) total++;
    return total;
  }

  int count(int l, int r) const {
    return count(r) - count(l-1);
  }
};
//}}}