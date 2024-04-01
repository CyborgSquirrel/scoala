[[message passing interface; MPI]]

|  | blocking | non-blocking |
| ---- | ---- | ---- |
| send | `MPI_Send(buf, count, type, dest, tag, comm)` | `MPI_Isend(buf, count, type, dest, tag, comm, request)` |
| receive | `MPI_Recv(buf, count, type, source, tag, comm, status)` | `MPI_Irecv(buf, count, type, source, tag, comm, request)` |
| probe | `MPI_Probe(source, tag, comm, &status)` | `MPI_Iprobe(source, tag, comm, &flag, &status)` |
| wait |  | `MPI_Wait(&request, &status)` |
| test |  | `MPI_Test(&request, &flag, &status)` |


> [!NOTE]
> `tag` este ca un fel de id al mesajului.
