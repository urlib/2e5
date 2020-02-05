#pragma GCC optimize(2)
#pragma GCC optimize(3)

#include "bits/stdc++.h"

#define mem(x) memset((x), 0, sizeof((x)))
#define il __attribute__((always_inline))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#if __cplusplus > 201403L
#define R
#else
#define R register
#endif

#if __cplusplus >= 201103L
#define C constexpr
#else
#define C const
#endif

namespace _c
{
C double pi = 3.141592653589793;
namespace min
{
C int i8 = -128;
C int i16 = -32768;
C int i = -2147483647 - 1;
C ll l = -9223372036854775807LL - 1;
} // namespace min
namespace max
{
C int i8 = 127;
C int i16 = 32767;
C int i = 2147483647;
C ll l = 9223372036854775807LL;
} // namespace max
} // namespace _c

namespace _f
{
template <typename Tp>
inline Tp gcd(Tp x, Tp y)
{
    while (y != 0)
    {
        Tp t = x % y;
        x = y;
        y = t;
    }
    return x;
}
template <typename Tp>
inline Tp abs(const Tp &a)
{
    return a > 0 ? a : -a;
}
template <typename Bp, typename Ep>
inline Bp pow(Bp a, Ep b)
{
    R Bp res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}
template <typename Bp, typename Ep, typename Mp>
inline Mp pow(Bp a, Ep b, const Mp &m)
{
    a %= m;
    R Mp res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = ((ll)res * a) % m;
        }
        a = ((ll)a * a) % m;
        b >>= 1;
    }
    return res % m;
}
} // namespace _f

namespace io
{
template <typename Tp>
inline void read(Tp &x)
{
    static bool neg;
    static char c;
    x = 0, neg = 0, c = getchar();
    for (; !isdigit(c); c = getchar())
    {
        if (c == '-')
        {
            neg = 1;
        }
    }
    for (; isdigit(c); c = getchar())
    {
        x = x * 10 + c - '0';
    }
    if (neg)
    {
        x = -x;
    }
}
template <typename Tp>
inline Tp read()
{
    R Tp res;
    read(res);
    return res;
}
template <typename Tp>
inline void readln(const Tp first, const Tp last)
{
    for (R Tp it = first; it != last; it++)
    {
        read(*it);
    }
}
template <typename Tp>
inline void _write(Tp x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
    {
        _write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename Tp>
inline void write(const Tp &x, const char &sep = ' ')
{
    _write(x);
    putchar(sep);
}
template <typename Tp>
inline void writeln(const Tp &x)
{
    write(x, '\n');
}
template <typename Tp>
inline void writeln(const Tp first, const Tp last, const char &sep = ' ', const char &ends = '\n')
{
    for (R Tp it = first; it != last; it++)
    {
        write(*it, sep);
    }
    putchar(ends);
}
#if __cplusplus >= 201103L
template <typename Tp, typename... Args>
inline void read(Tp &x, Args &... args)
{
    read(x);
    read(args...);
}
#endif
} // namespace io

C int N = 20;
C int _U = N + 1;

C int U = N + 5;
C int SIZE = 1 << _U;

int n, m, t;
int wx[U], wy[U];
int cover_x[SIZE], cover_y[SIZE], cnt[SIZE];

bitset<SIZE> fx, fy;
vector<int> x, y;

inline void solve(int n, int *wx, int *cover_x, bitset<SIZE> &fx, vector<int> &x)
{
    for (R int s = 0; s < (1 << n); s++)
    {
        fx[s] = 1;

        int sum = 0;
        for (R int i = 0; i < n; i++)
        {
            if (s & (1 << i))
            {
                cover_x[s] |= cover_x[s ^ (1 << i)];
                sum += wx[i];
                fx[s] = fx[s] & fx[s ^ (1 << i)];
            }
        }

        if (fx[s] && cnt[s] <= cnt[cover_x[s]])
        {
            x.emplace_back(sum);
        }
        else
        {
            fx[s] = 0;
        }
    }
}

char str[U];

inline void init()
{
    for (R int s = 0; s < (1 << 20); s++)
    {
        cnt[s] = cnt[s >> 1] + (s & 1);
    }
}

int main()
{
    init();

    io::read(n, m);
    for (R int i = 0; i < n; i++)
    {
        scanf("%s", str);
        for (R int j = 0; j < m; j++)
        {
            if (str[j] == '1')
            {
                cover_x[1 << i] |= (1 << j);
                cover_y[1 << j] |= (1 << i);
            }
        }
    }

    io::readln(wx, wx + n);
    io::readln(wy, wy + m);

    io::read(t);

    solve(n, wx, cover_x, fx, x);
    solve(m, wy, cover_y, fy, y);

    sort(x.begin(), x.end());

    ll ans = 0;
    for (const auto &val : y)
    {
        ans += x.end() - lower_bound(x.begin(), x.end(), t - val);
    }
    io::writeln(ans);
}