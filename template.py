# {{{
import os
import sys
from bisect import bisect_left, bisect_right, insort
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, reduce
from heapq import heapify, heappop, heappush
from itertools import accumulate, combinations, permutations, product
from math import ceil, comb, floor, gcd, inf, isqrt, lcm, perm
from string import ascii_lowercase, ascii_uppercase

sys.setrecursionlimit(10**4)


LOCAL = "LOCAL" in os.environ


def db(*args):
    if LOCAL:
        print(*args, file=sys.stderr)


# }}}


def solve():
    pass


def main():  # {{{
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# }}}

# vim: foldmethod=marker foldlevel=0
