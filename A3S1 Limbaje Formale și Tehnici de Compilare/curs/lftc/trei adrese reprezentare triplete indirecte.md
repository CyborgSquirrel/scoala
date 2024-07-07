Exemplu:

Pentru următorul program:
```
A := B*(C+D)
```

Reprezentarea va fi:

| nr. de ordine a operației | nr. operației |
| ---- | ---- |
| 51 | 131 |
| 52 | 132 |
| 53 | 133 |
<br>

| nr. operației | operator | arg1 | arg2 |
| ---- | ---- | ---- | ---- |
| ... | ... | ... | ... |
| (131) | + | C | D |
| (132) | * | B | (131) |
| (133) | := | A | (132) |