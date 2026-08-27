# {{{
import sys
from bisect import bisect_left, bisect_right, insort
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, reduce
from heapq import heapify, heappop, heappush
from itertools import accumulate, combinations, permutations, product
from math import comb, gcd, inf, isqrt, lcm, perm
from string import ascii_lowercase, ascii_uppercase

sys.setrecursionlimit(10**4)


def db(*args):
    print(*args, file=sys.stderr)


# }}}


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    cnt = [0] * (n + 1)
    for v in a:
        cnt[v] += 1

    if any(c % k for c in cnt):
        print(0)
        return

    cap = [c // k for c in cnt]

    ans = 0

    F = [0] * (n + 1)

    l = 0
    for r, v in enumerate(a):
        F[v] += 1

        while F[v] > cap[v]:
            F[a[l]] -= 1
            l += 1

        ans += r - l + 1

    print(ans)


def main():  # {{{
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# }}}

# vim: foldmethod=marker foldlevel=0
