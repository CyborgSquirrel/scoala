- `<variabilă> ::= valoare`
- `terminal`
- `valoare_1 | valoare_2`

```bnf
<intreg> ::= <semn> <intreg_fara_semn> | <intreg_fara_semn>
<semn> ::= +|-
<intreg_fara_semn> ::= <cifra> | <cifra> <intreg_fara_semn>
<cifra> ::= 0|1|2|3|4|5|6|7|8|9
```