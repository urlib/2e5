#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

template <typename Tp>
inline void read(Tp &x)
{
    x = 0;
    bool neg = 0;

    char c = getchar();
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

typedef unsigned int ui;

const ll INF = 1ll << 32;
const int N = 1e8 + 5;
const int U = 1e8;
const int MAX_PRIME_CNT = 6e6 + 5;

int n;
int p[MAX_PRIME_CNT], tot = 0;

ui sum[MAX_PRIME_CNT];
bitset<N> flag;

inline void init()
{
    for (int i = 2; i <= U; i++)
    {
        if (!flag[i])
        {
            p[tot++] = i;
        }

        for (int j = 0; j < tot; j++)
        {
            if (i * p[j] > U)
            {
                break;
            }

            flag[i * p[j]] = 1;

            if (i % p[j] == 0)
            {
                break;
            }
        }
    }

    sum[0] = p[0];
    for (int i = 1; i < tot; i++)
    {
        sum[i] = sum[i - 1] * p[i];
    }
}

inline ui solve(int n)
{
    int x = upper_bound(p, p + tot, n) - p - 1;
    ui ans = sum[x];

    for (int i = 0; i < tot; i++)
    {
        if (p[i] * p[i] > n)
        {
            break;
        }

        int cur = p[i], t = p[i] * p[i];
        while (t / cur == p[i] && t <= n)
        {
            cur *= p[i];
            t *= p[i];
        }
        ans = ans * (cur / p[i]);
    }

    return ans;
}

int T;

int main()
{
    init();
    read(T);
    for (int _ = 1; _ <= T; _++)
    {
        read(n);
        printf("Case %d: %lld\n", _, solve(n) % INF);
    }
}