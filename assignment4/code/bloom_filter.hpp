#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <cstdint>  // uint64_t

#include <bitset>

#include "murmurhash.hpp"

template <typename Key>
struct BloomHash {
  std::size_t operator()(Key key, unsigned int seed) const {
    // implement using murmur3_32
		return 0;
  }
};

template <typename Key, unsigned int m, typename Hash = BloomHash<Key>>
class BloomFilter {
 public:
  explicit BloomFilter(unsigned int num_hashes);

  BloomFilter(std::initializer_list<Key> init, unsigned int num_hashes);

  template <typename It>
  BloomFilter(It first, It last, unsigned int num_hashes);

  bool insert(const Key& key);

  bool contains(const Key& key) const;

  uint64_t approx_size() const;

  template <typename It>
  double false_positive_rate(It positive_begin, It positive_end,
                             It negative_begin, It negative_end) const;

  double space_ratio(uint64_t num_elements);

 private:
  std::bitset<m> data_;
  unsigned int k_;
};

#endif  // BLOOM_FILTER_HPP
