#!/usr/bin/env python3

import cupy as cp


def rmmmi(n: int) -> int:
    return cp.sum((cp.arange(1, n) % 10) * 2 + 1)


n = 100001
print(rmmmi(n))
