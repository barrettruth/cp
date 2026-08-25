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
    n, m = map(int, input().split())

    rules = [(0, 0)]

    for _ in range(n):
        x, y = map(int, input().split())
        rules.append((x, y))

    ans = 0

    for i in range(1, len(rules)):
        pos_delta = rules[i][0] - rules[i - 1][0]
        size_delta = rules[i][1] - rules[i - 1][1]

        if (pos_delta & 1) == (size_delta & 1):
            ans += pos_delta
        else:
            ans += pos_delta - 1

    ans += m - rules[-1][0]

    print(ans)


# {{{
def main():
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# }}}

# vim: foldmethod=marker foldlevel=0
