Fie $s$ un [[semafor|semafor]], și $c(s)$ o structură de date, care conține thread-urile care așteaptă la acesta.

- într-un **semafor slab**, $c(s)$ este o mulțime, deci thread-urile pot trece $P(s)$ în altă ordine decât s-a apelat acesta
- într-un **semafor puternic**, $c(s)$ este o coadă FIFO, deci thread-urile trec de $P(s)$ în aceeași ordine în care s-a apelat acesta