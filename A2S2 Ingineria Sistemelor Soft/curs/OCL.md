Bazat pe logica de ordinul întâi.

Tipuri primitive:
- `Integer`
- `UnlimitedNatural`
- `Real`
- `Boolean`
- `String`

Tipuri specifice:
- `OclAny`
- `OclVoid`
- `OclInvalid`
- `OclMessage`

Tipuri colecție:
- `Collection`
- `Set`
- `OrderedSet`
- `Sequence`
- `Bag`
- `Enumeration`
- `TupleType`

`oclIsTypeOf(type: Classifier): Boolean` - e aceeași clasă sau o subclasă
`oclIsKindOf(type: Classifier): Boolean` - e aceeași clasă

`oclType(): Classifier` - returnează tipul
`oclAsType(): T` - cast
`oclIsNew(): Boolean` - verifică dacă obiectul a fost creat în timpul execuției metodei
`oclIsUndefined(): Boolean` - verifică dacă obiectul există
`oclIsValid(): Boolean` - verifică dacă obiectul este valid (adică dacă tipul obiectului nu este `OclInvalid`)

# Operații pe colecții:
## Mărime
- `size(): Integer`
- `isEmpty(): Boolean`
- `notEmpty(): Boolean`
## Query
- `count(object: T): Boolean`
- `includes(object: T): Boolean`
- `excludes(object: T): Boolean`
- `includesAll(c: Collection): Boolean`
- `excludesAll(c: Collection): Boolean`
## Conversie
- `asSet(): Set(T)`
- `asOrderedSet(): OrderedSet(T)`
- `asBag(): Bag(T)`
- `asSequence(): Sequence(T)`

# Iterator

# Navigare
- multiplicitatea capătului opus minim 1 => clasificatorul de la capătul opus
- multiplicitatea capătului opus maxim 1 => `Set` sau `OrderedSet`
- navigare mai mulți pași => `Bag`


Adaugi `@pre` după un obiect, ca să ai valoarea precedentă a lui.

```
context Clasă
	inv invClasă: self.a >= 0
```

```
context Clasă::subtract(n: Integer)
	pre subtractPre: self.a >= 0
	post subtractPost: self.a = self.a@pre - n
```

```
let nPositive: Boolean = n >= 0 in ...
def aPositive: Boolean = self.a >= 0
```