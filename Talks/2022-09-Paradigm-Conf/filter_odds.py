# Godbolt: https://godbolt.org/z/G3GeG799E

def filter_odds(lst):
    res = []
    for e in lst:
        if e % 2:
            res.append(e)
    return res

def filter_odds1(lst):
    return list(filter(lambda e: e % 2, lst))

def filter_odds2(lst):
    return [e for e in lst if e % 2]

lst = [1,2,3,4,5]

print(filter_odds (lst))
print(filter_odds1(lst))
print(filter_odds2(lst))
