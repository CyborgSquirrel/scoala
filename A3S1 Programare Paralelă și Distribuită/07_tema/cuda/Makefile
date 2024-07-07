# NVCC_ARGS_EXTRA = -g
NVCC_ARGS = --expt-relaxed-constexpr $(NVCC_ARGS_EXTRA)

# nvcc compile

target/conv-cu: conv.cu
	mkdir -p ./target
	bear -- nvcc $(NVCC_ARGS) ./conv.cu -o ./target/conv-cu
