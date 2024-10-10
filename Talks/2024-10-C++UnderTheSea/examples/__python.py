#!/usr/bin/env python3


def rmmmi(n: int) -> int:
    return sum((i % 10) * 2 + 1 for i in range(1, n))


n = 100001
print(rmmmi(n))
