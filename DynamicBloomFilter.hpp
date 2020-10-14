#ifndef _BLOOM_FILTER_HPP_
#define _BLOOM_FILTER_HPP_

#include "IBloomFilter.hpp"

#include <cstdint>
#include <memory>
#include <vector>

/**
 *  n = max elements expected to be inserted into the filter
 *  p = desired probability of false positives
 *  m = number of bits
 *  c = actual count of added items
 *  k = number of hashes (number of different seeds in this case)
 *
 *  m = (n * ln(p)) / ((ln(2)^2)
 *  k = (m / n) * ln(2)
 *  
 *  worst case error = (1 - (1 - (1 / m)) ^ k*c) ^ k
 */
namespace jms {
  class DynamicBloomFilter : public IBloomFilter {
    unsigned long m;
    unsigned int n;
    double p;
    unsigned int c;
    std::vector<bool> bitmap;
    std::vector<uint32_t> seeds;

    public : 
    explicit DynamicBloomFilter(unsigned int n, double desired_p);
    void add(const std::string& s);
    bool contains(const std::string& s) const;
    void clear();
    double getProbabilityOfFalsePositive() const;
    unsigned int getCount() const;
    unsigned long int getBitCount() const;
  };
};

#endif
