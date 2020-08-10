# hash-fuzz
Fuzz hashing algos

```
$ clang -fsanitize=fuzzer -std=c++11 djb2.cc -o djb2-fuzzer
$ clang -fsanitize=fuzzer -std=c++11 crc32.cc -o crc32_fuzz
```
