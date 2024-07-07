
> [!NOTE]
> Se încadrează în [[clasificarea flynn|clasificarea flynn]], ca fiind SIMT Single Instruction Multiple Threads.


| prefix | executed on | only callable from | notes |
| ---- | ---- | ---- | ---- |
| `__device__` | device | device |  |
| `__global__` | device | host | must return `void` |
| `__host__` | host | host |  |

grid -> block -> thread
- grid compus din block-uri organizate 1D, 2D, 3D
- block compus din thread-uri organizate 1D, 2D, 3D

- `blockIdx`
- `threadIdx`
- `blockDim`

| memory type | per | notes |
| ---- | ---- | ---- |
| global | grid | `cudaMalloc()`, large but slow |
| texture | grid | read only, optimized for 2D access pattern |
| constant | grid | slow but with cache |
| shared | block | 100 times faster than global memory |
| local | thread | but as as slow as global memory |

- `cudaMemcpy()` - așteaptă până se termină copierea
- `cudaMemcpyAsync()` - returnează direct
- `cudaDeviceSynchronize()` - așteaptă până se finalizează toate apelurile cuda

```cpp
__global__ void kernel() {
	// ...
}

int main() {
	{
		int blocks_no = 16;
		int threads_no = 16;
		kernel<<<blocks_no, threads_no>>>();
	}
	{
		// poți folosi dim3 ca să definești
		// block-uri cu mai multe dimensiuni
		dim3 blocks_no(2, 4);
		dim3 threads_no(2, 2, 2);
		kernel<<<blocks_no, threads_no>>>();
	}
	return 0;
}
```