### Atribute statice cu tip generic

Nu se poate să avem atribute statice cu tip generic.

```java
public class A<T> {
	public static T a;
}
```

Main:
```java
// Kaput
A<Integer>.a = 41;
A<String>.a = "yeet";
```

### Tipul wildcard

Există un tip wildcard `<?>`.

```java

```

### Arhitectura colecțiilor

- Intefață
- Clasă abstractă
- Implementări concrete

Exemplu:

- `List`
- `AbstractList`
- `ArrayListLinkedListVector`
