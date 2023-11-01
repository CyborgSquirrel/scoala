O [[gramatică independentă de context; gramatică de tip 2|gramatică independentă de context]] $G=(N,\Sigma,P,S)$ este *ambiguă*, dacă și numai dacă există cel puțin un cuvânt $w$ care admite doi arbori de derivare distincți; altfel gramatica este *neambiguă*.

exemplu de gramatică ambiguă:
```
E -> E + E
E -> E * E
E -> q
```

`q + q + q`
poate avea cel puțin doi arbori cred
TODO: exemplu la arbori îîîîîîîîîîîîîîîîîîî

exemplu de gramatică neambiguă:
```
A -> aA
A -> b
```

```
E -> E + T
E -> T
T -> T * F
T -> F
F -> q
```