
| Variabilă | Descriere                                                     |
| --------- | ------------------------------------------------------------- |
| `"$*"`    | Toate argumentele, concatenate cu primul caracter din `$IFS`. |
| `"$@"`    | Toate argumentele, ca string-uri separate.                    |
| `$?`      | Return code-ul ultimii comenzi.                               |

# Exemplu $*

Dacă rulăm acest script cu următoarele argumente:
>`arg1 'arg2 cu spații' arg3`

Vom obține:
- Pentru `"$*"`:
  ```
  arg1-arg2 cu spații-arg3
	```
- Pentru `$*`:
  ```
  arg1 arg2 cu spații arg3
	```

```bash
# run {"compiler": "bash"}

IFS='-'
echo 'Args written with kebab case:'
echo "$*"
echo $*
```

# Exemplu cu $* și $@

Dacă rulăm acest script cu următoarele argumente:

>`arg1 'arg2 cu spații' arg3`

Atunci vom obține următoarele rezultate:
- Pentru `"$*"`:
  ```
  arg1 arg2 cu spații arg3
	```
- Pentru `"$@"`:
  ```
  arg1
  arg2 cu spații
  arg3
	```
- Pentru `$*` și `$@`:
  ```
  arg1
  arg2
  cu
  spații
  arg3
	```

```bash
# run {"compiler": "bash"}

echo '= Cu citare ='

echo '== Exemplu "$*" =='
for arg in "$*"; do
	echo "$arg"
done

echo '== Exemplu "$@" =='
for arg in "$@"; do
	echo "$arg"
done

echo '= Fără citare ='

echo '== Exemplu $* =='
for arg in $*; do
	echo "$arg"
done

echo '== Exemplu $@ =='
for arg in $@; do
	echo "$arg"
done

```