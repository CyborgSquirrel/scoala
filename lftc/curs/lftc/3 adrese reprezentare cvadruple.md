Exemplu:

Pentru următorul program:
```
A := B*(C+D)
```

Reprezentarea va fi:

| operator | arg1 | arg2 | rez |
| ---- | ---- | ---- | ---- |
| ... | ... | ... | ... |
| + | C | D | T1 |
| * | B | T1 | T2 |
| := | T2 |  | A |