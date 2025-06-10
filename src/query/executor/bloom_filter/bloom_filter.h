#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

#include "third_party/murmur3/murmur3.h"

class BloomFilter {
private:
  std::vector<bool> bits;

  size_t num_hashes;

  uint64_t hash(uint64_t key, size_t n) const {
    uint64_t _hash[2];
    MurmurHash3_x64_128(&key, sizeof(key), n, _hash);
    return _hash[0] % bits.size();
  }

public:
  BloomFilter(size_t bitarray_size, size_t num_hashes)
      : num_hashes(num_hashes) {
    bits.resize(bitarray_size, false);
  }

  ~BloomFilter() {
    std::cout << "Bloom filter bitmap:\n";
    print(std::cout);
    std::cout << std::endl;
  }

  void add(uint64_t key) {
    // TODO: implement
  }

  void clear() {
    std::fill(bits.begin(), bits.end(), false);
  }

  bool might_contain(uint64_t key) const {
    // TODO: implement
    return true;
  }

  void print(std::ostream& os) const {
    os << '[';
    for (bool bit : bits) {
      os << (bit ? '1' : '0');
    }
    os << ']';
  }
};
