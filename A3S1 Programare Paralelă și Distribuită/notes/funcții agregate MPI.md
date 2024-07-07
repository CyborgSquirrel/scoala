[[message passing interface; MPI]]

| function | description |
| ---- | ---- |
| `MPI_Bcast(buf, count, type, root, comm)` | trimite mesajul tuturor proceselor din grup |
| `MPI_Scatter(send_buf, send_count, send_type, recv_buf, recv_count, recv_type, root, comm)` | trimite câte un chunk al mesajului fiecărui proces din grup |
| `MPI_Gather(send_buf, send_count, send_type, recv_buf, recv_count, recv_type, root, comm)` | fiecare proces trimite câte un chunk, și chunk-urile se reunesc |
| `MPI_Reduce(send_buf, recv_buf, count, type, operation_type, root, comm)` |  |
| `MPI_Scatterv(send_buf, send_counts, displacements, send_type, recv_buf, recv_count, recv_type, root, comm)` |  |
| `MPI_Gatherv(send_buf, send_count, send_type, recv_buf, recv_counts, displacements, recv_type, root, comm)` |  |


> [!NOTE]
> Pentru `MPI_Scatter` și `MPI_Gather`, `send_count` este numărul de elemente care va fi trimis către fiecare proces, iar `recv_count` este numărul de elemente care ar putea să încapă în `recv_buf`.

![[Pasted image 20240205114815.png]]