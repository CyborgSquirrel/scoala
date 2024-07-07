# String-uri

| Operație             | Explicație                      |
| -------------------- | ------------------------------- |
| `-n STRING`          | Lungimea lui `STRING` este != 0 |
| `-z STRING`          | Lungimea lui `STRING` este = 0  |
| `STRING1 = STRING2`  | String-urile sunt egale         |
| `STRING1 != STRING2` | String-urile sunt diferite      |
# Întregi

| Operație                 | Explicație             |
| ------------------------ | ---------------------- |
| `INTEGER1 -eq INTEGER2`  | Întregii sunt egali    |
| `INTEGER1 -ne  INTEGER2` | Întregii sunt diferiți |
| `INTEGER1 -gt INTEGER2`  | >                      |
| `INTEGER1 -ge INTEGER2`  | >=                     |
| `INTEGER1 -lt INTEGER2`  | <                      |
| `INTEGER1 -le INTEGER2`  | <=                     |
# Fișiere

| Operație  | Explicație                                        |
| --------- | ------------------------------------------------- |
| `-e FILE` | `FILE` există                                     |
| `-s FILE` | `FILE` există și are dimensiune >0                |
| `-d FILE` | `FILE` există și este un director                 |
| `-f FILE` | `FILE` există și este un fișier obișnuit          |
| `-L FILE` | `FILE` există și este un symlink                  |
| `-h FILE` | `FILE` există și este un symlink (la fel ca `-L`) |
| `-p FILE` | `FILE` există și este un FIFO                     |
| `-r FILE` | `FILE` există și poate fi citit de utilizator     |
| `-w FILE` | `FILE` există și poate fi scris de utilizator     |
| `-x FILE` | `FILE` există și poate fi executat de utilizator  |
