#ifndef _FIXED_BLOOM_FILTER_HPP_
#define _FIXED_BLOOM_FILTER_HPP_

#include <bitset>
#include <vector>
#include <string>
#include <memory>

#include "IBloomFilter.hpp"

namespace jms {

  class FixedSize {
    public :
    constexpr static std::size_t TINY    = 65535;       // 8K
    constexpr static std::size_t SMALL   = 1048576;     // 128K
    constexpr static std::size_t MEDIUM  = 8388608;     // 1024K
    constexpr static std::size_t LARGE   = 67108864;    // 8M
    constexpr static std::size_t XL      = 536870912;   // 64M
    constexpr static std::size_t XXL     = 1073741824;  // 128M
    constexpr static std::size_t XXXL    = 2147483648;  // 256M 
    constexpr static std::size_t LARGEST = 4294967296;  // 512M
  };

  template <std::size_t N>
  class FixedBloomFilter : public IBloomFilter {
    std::unique_ptr<std::bitset<N>> bitmap;
    unsigned long int m;
    unsigned int c;
    unsigned int k;
    std::vector<uint32_t> seeds;

    public :
    FixedBloomFilter();
    void add(const std::string& s);
    bool contains(const std::string& s) const;
    void clear();
    double getProbabilityOfFalsePositive() const;
    unsigned int getCount() const;
    unsigned long int getBitCount() const;
  };
};

#endif
