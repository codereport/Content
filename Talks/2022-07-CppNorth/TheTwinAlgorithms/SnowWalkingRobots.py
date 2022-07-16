# https://godbolt.org/z/TfdGdb61G

from collections import Counter

def count_lrud(s):
    return list(Counter(s).values())

print(count_lrud('LRDLURDLURDULR')) # [4, 4, 3, 3]