[[testare white-box; testare structurală]]

| Hieroglifă | Descifrare                      | Descriere                                                                                                                                                                                  |
| ---------- | ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **apc**    | all path coverage               | fiecare [[CFG drum independent\|drum independent]] trebuie executat cel puțin odată                                                                                                        |
| **sc**     | source coverage                 | fiecare [[nod de instrucțiune\|instrucțiune]] trebuie executată cel puțin odată                                                                                                            |
| **dc**     | decision coverage               | pentru fiecare [[nod de decizie\|decizie]], trebuie executată fiecare ramificație (true, false) cel puțin odată                                                                            |
| **cc**     | condition coverage              | fiecare [[condiție]], din fiecare decizie, trebuie să ia fiecare dintre valorile posibile (true, false) cel puțin odată                                                                    |
| **dcc**    | decision and condition coverage | decision coverage + condition coverage; fiecare [[nod de decizie\|decizie]] și fiecare [[condiție\|condiție]] trebuie să ia fiecare dintre valorile posibile (true, false) cel puțin odată |
| **mcc**    | multiple condition coverage     | toate combinațiile posibile ale valorilor de ieșire din toate [[condiție\|condițiile]] dintr-o [[nod de decizie\|decizie]] trebuie executate cel puțin odată (produs cartezian)            |
| **lc**     | loop coverage                   | $n$ - numărul maxim de parcurgeri al buclei; se fac $0$, $1$, $2$, $m$ ($m<n$), $n-1$, $n$, $n+1$ parcurgeri ale buclei                                                                    |
