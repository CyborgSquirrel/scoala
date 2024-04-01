[[monitor]]

- o singură variabilă condițională
- disciplina este [[signal-and-continue vs signal-and-wait|signal-and-continue]]
- nu este starvation-free

Metode [[variabilă condițională|variabilă condițională]] (toate trebuie apelate într-un context `synchronized`):
- `wait()`
- `notify()`
- `notifyAll()`