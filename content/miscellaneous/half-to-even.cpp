/**
 * Author: Wallace
 * Date: 07/05/2024
 * Description: How to round a long double with the rule of "rounding half to even".
 * Time: O(1)
*/

// 1e6 -> round considering 6 decimal places
ans *= 1e6;
ans = nearbyintl(ans);
ans /= 1e6;
