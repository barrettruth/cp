# {{{
import sys
from bisect import bisect_left, bisect_right, insort
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, reduce
from heapq import heapify, heappop, heappush
from itertools import accumulate, combinations, permutations, product
from math import comb, gcd, inf, isqrt, lcm, perm
from string import ascii_lowercase, ascii_uppercase

input = sys.stdin.readline

sys.setrecursionlimit(10**4)


def db(*args):
    print(*args, file=sys.stderr)


# }}}


def solve():
    n, m = map(int, input().split())
    first = {input()[0] for _ in range(n)}
    ok = True
    for _ in range(m):
        if not set(input().strip().lower()) <= first:
            ok = False
    print("YES" if ok else "NO")


# {{{
def main():
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# }}}

# vim: foldmethod=marker foldlevel=0
