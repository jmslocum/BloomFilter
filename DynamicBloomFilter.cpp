#include "DynamicBloomFilter.hpp"
#include "MurmurHash2.h"

#include <cmath>
#include <random>
#include <algorithm>

namespace jms {
  DynamicBloomFilter::DynamicBloomFilter(unsigned int n, double desired_p) :  m{0}, n{n}, 
      p{desired_p}, c{0}, bitmap{}, seeds{} {
   
    m = static_cast<unsigned long>(abs((n * log(p)) / (pow(log(static_cast<double>(2.0)), 2.0))));
    unsigned int k = (static_cast<double>(m) / n) * log(2.0);

    std::random_device rd;  
    std::mt19937 rand(rd()); 
    std::uniform_int_distribution<unsigned int> distrib(0, UINT32_MAX);

    for (unsigned int i = 0; i < k; i++) {
      seeds.push_back(distrib(rand));
    }

    bitmap = std::vector<bool>(m, false);
  }

  void DynamicBloomFilter::add(const std::string& s) {
    const void* ptr = reinterpret_cast<const void*>(s.data()); 

    std::for_each(seeds.begin(), seeds.end(), [=, this](const uint32_t& seed) {
        uint32_t h = MurmurHash2(ptr, s.size(), seed);
        bitmap[h%m] = true;
    });

    c++;
  }

  bool DynamicBloomFilter::contains(const std::string& s) const {
    const void* ptr = reinterpret_cast<const void*>(s.data()); 

    return std::all_of(seeds.begin(), seeds.end(), [=, this](const uint32_t& seed) {
        uint32_t h = MurmurHash2(ptr, s.size(), seed);
        return bitmap[h%m];
    });
  }

  void DynamicBloomFilter::clear() {
    std::fill(bitmap.begin(), bitmap.end(), false);
    c = 0;
  }


  double DynamicBloomFilter::getProbabilityOfFalsePositive() const {
    double d = 1.0 - (1.0 / static_cast<double>(m));
    d = pow(d, (static_cast<double>(seeds.size()) * c));
    d = 1.0 - d;
    d = pow(d, static_cast<double>(seeds.size()));
    return d;
  }

  unsigned int DynamicBloomFilter::getCount() const {
    return c;
  }

  unsigned long int DynamicBloomFilter::getBitCount() const {
    return m;
  }
};
