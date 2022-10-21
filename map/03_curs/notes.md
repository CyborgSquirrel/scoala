## Excepții

### Derivare

Dacă o excepție este derivată din `RuntimeException`, nu trebuie să se specifice în antetul funcției că ea poate arunca acea excepție.

### Prindere

```java
try {
	// ...
} catch (ArithmeticException | NullPointerException ex) {
	// ...
} catch (IOException ex)  {
	// ...
}
```
