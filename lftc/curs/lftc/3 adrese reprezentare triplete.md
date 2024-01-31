Exemplu:

Pentru următorul program:
```
A := B*(C+D)
```

Reprezentarea va fi:

| instr. | operator | arg1 | arg2 |
| ---- | ---- | ---- | ---- |
| ... | ... | ... | ... |
| (51) | + | C | D |
| (52) | * | B | (51) |
| (53) | := | A | (52) |