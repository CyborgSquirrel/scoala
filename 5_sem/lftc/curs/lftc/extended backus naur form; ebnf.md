
> [!NOTE]
> Punctul `.` este folosit ca sfârșit de regulă.

- `variabilă = valoare.`
- `"terminal"`
- `[ valoare ]` - opțional
- `{ valoare }` - de oricâte ori
- `valoare_1 | valoare_2`

```ebnf
intreg = [ semn ] cifra { cifra }.
semn = "+"|"-".
cifra = "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9".
```