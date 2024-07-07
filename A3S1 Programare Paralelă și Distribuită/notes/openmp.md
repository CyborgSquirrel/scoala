- folosește modelul fork-join de execuție paralelă

O variabilă poate fi:
- **shared**, accesibilă în orice thread
- **private**, accesibilă doar în thread-ul în care a fost definită
	- **firstprivate**, valoare inițială e preluată din afară?
	- **lastprivate**, valoarea finală este salvată?

`#pragma omp directive ...`

- `int omp_get_num_threads()` - returnează numărul de thread-uri care se execută în regiunea paralelă curentă
- `int omp_get_thread_num()` - returnează numărul thread-ului care a apelat funcția
- `int omp_get_max_threads()` - returnează numărul maxim de thread-uri
- `int omp_get_thread_limit()` - returnează numărul maxim de thread-uri ... din nou?
- `int omp_get_num_procs()` - returnează numărul de procesoare

**Master thread-ul** este cel cu numărul 0.

Astea:
- `#pragma omp for`
- `#pragma omp section`
- `#pragma omp single`

Au:
- distribuire automată între thread-uri
- barieră implicită la ieșire, decât dacă se specifică `nowait`

Schedule:
- `static`
- `dynamic`
- `guided`

![[Pasted image 20240204170424.png]]