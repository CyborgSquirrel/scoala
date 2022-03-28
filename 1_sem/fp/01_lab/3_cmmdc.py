def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a%b)

def readnumber(prompt):
    a = int(input(prompt))
    assert (a > 0), 'aoleu, numerele nu pot sa fie <= 0'
    return a

a = readnumber('a = ')
b = readnumber('b = ')

print(f'cmmdc-ul lui {a} si {b} este {gcd(a, b)}')
