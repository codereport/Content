#!/usr/bin/env python3

import numpy as np


def rmmmi(n: int) -> int:
    return np.sum((np.arange(1, n) % 10) * 2 + 1)


n = 100001
print(rmmmi(n))
