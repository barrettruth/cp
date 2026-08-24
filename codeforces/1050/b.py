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
    n, m, x, y = map(int, input().split())

    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    print(n + m)


# {{{
def main():
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# }}}

# vim: foldmethod=marker foldlevel=0
