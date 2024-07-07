def g(x, n, y, i):
    if i <= n:
        y[i] = x[i]
        g(x, n, y, i+1)
    else:
        print(c(z))


def transformare(x, n, y, m, z, k):
    if n == 0:
        g(y, m, z, 1)
        k = m
    else:
        y[m+1] = x[n]
        transformare(x, n-1, y, m+1, z, k)


def c(list_: list | dict):
    if isinstance(list_, list):
        return {
            i+1: x for i, x in enumerate(list_)
        }
    elif isinstance(list_, dict):
        items = list(list_.items())
        items.sort(key=lambda a: a[0])
        return [a[1] for a in items]
    else:
        raise ValueError()


x = c([1, 2, 3, 4, 5])  ; n = len(x)
y = c([6, 7, 8, 9, 10]) ; m = len(y)
z = c([0, 0, 0, 0, 0])  ; k = len(z)

transformare(x, n, y, m, z, k)
