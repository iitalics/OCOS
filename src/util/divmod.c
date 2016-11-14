typedef unsigned long long ull;
typedef long long ll;

#define UPPER_HALF 0xffffffff00000000

ull __udivmoddi4 (ull n, ull d, ull* rem)
{
  if (!((n & UPPER_HALF) || (d & UPPER_HALF))) {
    /* default to 32-bit division */
    if (rem) *rem = (long) n % (long) d;
    return (long) n / (long) d;
  }

  if (d == 0)
    return 1 / d;

  ull acc = 1;
  while ((ll)d >= 0) {
    d = (d << 1);
    acc = (acc << 1);
  }

  ull q = 0;
  while (acc) {
    if (d <= n) {
      n -= d;
      q += acc;
    }
    d = d >> 1;
    acc = acc >> 1;
  }

  if (rem) *rem = n;
  return q;
}
ull __udivdi3 (ull n, ull d)
{
  return __udivmoddi4(n, d, (ull*) 0);
}
ull __umoddi3 (ull n, ull d)
{
  ull r = 0;
  __udivmoddi4(n, d, &r);
  return r;
}


ll __divdi3 (ll n, ll d)
{
  int neg = 0;
  if (n < 0) {
    n = -n;
    neg = 1;
  }
  if (d < 0) {
    n = -n;
    neg ^= 1;
  }
  ll v = __udivmoddi4(n, d, (ull*) 0);
  return neg ? -v : v;
}

ll __moddi3 (ll n, ll d)
{
  int neg = 0;
  if (n < 0) {
    n = -n;
    neg = 1;
  }
  if (d < 0) {
    n = -n;
    neg ^= 1;
  }
  ull v = 0;
  __udivmoddi4(n, d, &v);
  return neg ? -v : v;
}
