import math
eps = 1e-7
def find(p, q):
    mid = (p + q) / 2
    dist = (1 - mid) / mid - 2 * math.log(1 / mid)
    if abs(dist) < eps:
        return mid
    elif dist > 0:
        return find(mid, q)
    return find(p, mid)

print(1 - find(0, 1))
