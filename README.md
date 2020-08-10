# hash-fuzz
Fuzz hashing algos

```
$ clang -fsanitize=fuzzer -std=c++11 djb2.cc -o djb2-fuzzer
$ clang -fsanitize=fuzzer -std=c++11 crc32.cc -o crc32_fuzz
$ sudo apt -y install dpdk-dev
$ clang -fsanitize=fuzzer -std=c++11 toeplitz.cc -o tfuzz -I /usr/include/dpdk
```

Collisions are logged to `<AlgorithmName-collisions.txt>`
