/**
 * Author: Quirino
 * Date: 06/11/2024
 * Description: Another code for extended euclid algorithm for computing gcd and diofantine equations
 * Time: O(\log{ min(a, b) })
 * Status: just copied
 */

// Extended GCD {{{
tuple<int, int, int> ext_gcd(int a, int b) {
  if (b == 0) return {a, 1, 0};
  auto [g, x, y] = ext_gcd(b, a%b);
  return {g, y, x - (a/b) * y};
}

tuple<bool, int, int> dio(int a, int b, int c) {
  auto [g, x, y] = ext_gcd(a, b);
  if (c % g) return {false, -1, -1};
  return {true, x * (c/g), y * (c/g)};
}
//}}}