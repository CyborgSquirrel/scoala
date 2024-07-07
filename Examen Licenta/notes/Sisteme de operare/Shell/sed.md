
| Flag | Descriere                       |
| ---- | ------------------------------- |
| `-E` | Folosește sintaxă regex extinsă |

| Comandă                  | Descriere                                                          |
| ------------------------ | ------------------------------------------------------------------ |
| `d`                      | delete pattern                                                     |
| `s/regexp/replacement/`  | substitute first occurrence of `regexp` in line with `replacement` |
| `s/regexp/replacement/g` | substitute all occurences `regexp` with `replacement`              |
| `y/source/dest/`         | transliterate characters from `source` to `dest`                   |

```bash
# run {"compiler": "bash"}

sed '1d' <( printf 'dont delete me pls\nI will remain' )
# I will remain

sed 's/Romania/a society/' <( echo 'we live in Romania' )
# we live in a society

sed 'y/d/l/' <( echo 'dingus doom' )
# lingus loom

sed -E 's/(Romania) society/\1/' <( echo 'we live in Romania society' )
# we live in Romania
```