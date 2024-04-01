MLP: Rust \
Specificare in: EBNF \
Specificare limbaj: https://doc.rust-lang.org/stable/reference/introduction.html

Atomi lexicali:

- identificatori
- literali
- cuvinte cheie (cuvinte rezervate)
- operatori (aritmetici, relationali)
- separatori

_1_ identificatori: \
_b_ de lungime oarecare nedepasind 250 caractere

_2_ tabela de simboluri: \
_b_ separat pentru identificatori si constante

_3_ organizarea tabelelor de simboluri: \
_c_ tabel de dispersie (hash)

eroare lexicala: daca nu gaseste in TS

```
program = { struct } "fn" "main" "(" ")" bloc_instr.

struct = "struct" id "{" { struct_membru ";" } "}".
struct_membru = id ":" path.

bloc_instr = "{" { instr } "}".

instr =
    ";"
  | instr_if
  | instr_while
  | instr_declarare ";"
  | instr_asignare ";"
  | instr_afisare ";".

instr_if = "if" expr bloc_instr.

instr_while = "while" expr bloc_instr.

instr_declarare =
  "let" [ "mut" ] id [ ":" path ] "=" expr.

instr_asignare =
  id "=" expr.

instr_afisare =
  "println!" "(" parametri_apel ")".

expr =
    path
  | lit
  | path "(" parametri_apel ")"
  | expr "." id "(" parametri_apel ")"
  | expr "." id
  | expr binop expr
  | unop expr
.

unop = "!" | "&" | "&mut".
binop =
    "+" | "-" | "*" | "/" | "%"
  | "<" | ">" | "<=" | ">=" | "==" | "!=".

parametri_apel = | expr "," parametri_apel | expr.

lit =
    lit_str
  | lit_int
  | lit_float
  | lit_struct.

lit_struct = id "{" { lit_struct_membru "," } "}".
lit_struct_membru = id ":" expr.

lit_str =
  "\""
  {
      alfa_mic
    | alfa_maj
    | cifra
    | "{" | "}" | " " | "="
  }
  "\"".

lit_int = lit_bin | lit_oct | lit_dec | lit_hex.

lit_float = lit_dec "." [ lit_dec ].

lit_bin = "0b" cifra_bin { cifra_bin }.
lit_oct = "0o" cifra_oct { cifra_oct }.
lit_dec =      cifra_dec { cifra_dec }.
lit_hex = "0x" cifra_hex { cifra_hex }.

cifra_bin = "0" | "1".
cifra_oct = "0" | "1" | ... | "7".
cifra_zec = "0" | "1" | ... | "9".
cifra_hex =
    "0" | "1" | ... | "9"
  | "a" | "b" | "c" | "d" | "e" | "f"
  | "A" | "B" | "C" | "D" | "E" | "F".

path = id { "::" id }.

id = id_start { id_continue } | "_" id_continue { id_continue }.
id_start = alfa_mic | alfa_maj.
id_continue = alfa_mic | alfa_maj | cifra | "_".

alfa_mic = "a" | "b" | ... | "z".
alfa_maj = "A" | "B" | ... | "Z".
cifra = "1" | "2" | ... | "9".
```
