
| Flag | Descriere                                                                        |
| ---- | -------------------------------------------------------------------------------- |
| `-e` | Everything; afișează toate procesele                                             |
| `-f` | Full-format; afișează mai multe date: UID, PPID, C, STIME, TTY, întreaga comandă |

Exemplu `ps`:
```
    PID TTY          TIME CMD
1389496 pts/7    00:00:00 zsh
1389575 pts/7    00:00:00 ps
```

Exemplu `ps -f`:
```
UID          PID    PPID  C STIME TTY          TIME CMD
andrei   1389496 1338478  0 09:16 pts/7    00:00:00 /run/current-system/sw/bin/zsh
andrei   1389624 1389496  0 09:16 pts/7    00:00:00 ps -f
```