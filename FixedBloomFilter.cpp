#include "FixedBloomFilter.hpp"
#include "MurmurHash2.h"

#include <random>
#include <algorithm>
#include <cmath>

namespace jms {
  template <std::size_t N>
  FixedBloomFilter<N>::FixedBloomFilter() : 
    bitmap{std::make_unique<std::bitset<N>>()}, m{N}, c{0}, k{4}, seeds{} {

    std::random_device rd;  
    std::mt19937 rand(rd()); 
    std::uniform_int_distribution<std::size_t> distrib(0, UINT32_MAX);

    for (unsigned int i = 0; i < k; i++) {
      seeds.push_back(distrib(rand));
    }
  }

  template <std::size_t N>
  void FixedBloomFilter<N>::add(const std::string& s) {
    const void* ptr = reinterpret_cast<const void*>(s.data()); 

    std::for_each(seeds.begin(), seeds.end(), [=, this](const uint32_t& seed) {
        uint32_t h = MurmurHash2(ptr, s.size(), seed);
        bitmap->set(h%m);
    });

    c++;
  }

  template <std::size_t N>
  bool FixedBloomFilter<N>::contains(const std::string& s) const {
    const void* ptr = reinterpret_cast<const void*>(s.data()); 

    return std::all_of(seeds.begin(), seeds.end(), [=, this](const uint32_t& seed) {
        uint32_t h = MurmurHash2(ptr, s.size(), seed);
        return (*bitmap)[h%m];
    });
  }

  template <std::size_t N>
  void FixedBloomFilter<N>::clear() {
    bitmap->reset();
    c = 0;
  }

  template <std::size_t N>
  double FixedBloomFilter<N>::getProbabilityOfFalsePositive() const {
    double d = 1.0 - (1.0 / static_cast<double>(m));
    d = pow(d, (static_cast<double>(k) * c));
    d = 1.0 - d;
    d = pow(d, static_cast<double>(k));
    return d;
  }

  template <std::size_t N>
  unsigned int FixedBloomFilter<N>::getCount() const {
    return c;
  }

  template <std::size_t N>
  unsigned long int FixedBloomFilter<N>::getBitCount() const {
    return m;
  }

  template class FixedBloomFilter<FixedSize::TINY>;
  template class FixedBloomFilter<FixedSize::SMALL>;
  template class FixedBloomFilter<FixedSize::MEDIUM>;
  template class FixedBloomFilter<FixedSize::LARGE>;
  template class FixedBloomFilter<FixedSize::XL>;
  template class FixedBloomFilter<FixedSize::XXL>;
  template class FixedBloomFilter<FixedSize::XXXL>;
  template class FixedBloomFilter<FixedSize::LARGEST>;
};
