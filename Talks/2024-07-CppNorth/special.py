# Solution 1
# https://godbolt.org/z/ojoWx3cv6

def isArraySpecial(nums):
    for i in range(len(nums) - 1):
        if nums[i] % 2 == nums[i + 1] % 2:
            return False
    return True

# Solution 2
# https://godbolt.org/z/xvf8joPvb
def isArraySpecial(nums):
    for x, y in zip(nums, nums[1:]):
        if x % 2 == y % 2:
            return False
    return True

# Solution 3
# https://godbolt.org/z/5eb4ro8c7
def isArraySpecial(nums):
    return all(x % 2 != y % 2 for x, y in zip(nums, nums[1:]))

# Solution 4
from dovekie import psi, odd
from operator import ne

def isArraySpecial(nums):
    return all(psi(ne, odd)(x, y) for x, y in zip(nums, nums[1:]))

# Solution 4
from dovekie import psi, odd
from operator import ne

def isArraySpecial(nums):
    return all(map(psi(ne, odd), nums, nums[1:]))

# Solution 5
from dovekie import psi, odd
from operator import ne

def adjacentMap(xs, op):
    return [op(a, b) for a, b in pairwise(xs)]

def isArraySpecial(nums):
    return all(adjacentMap(nums, psi(ne, odd)))

# Solution 6
from dovekie import odd
from operator import ne
from itertools import pairwise

def adjacentMap(xs, op):
    return [op(a, b) for a, b in pairwise(xs)]

def isArraySpecial(nums):
    return all(adjacentMap(map(odd, nums), ne))
