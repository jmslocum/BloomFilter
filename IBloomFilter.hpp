#ifndef _I_BLOOM_FILTER_HPP_
#define _I_BLOOM_FILTER_HPP_

#include <string>

namespace jms {
  class IBloomFilter {
    public :
    virtual void add(const std::string& s) = 0;
    virtual bool contains(const std::string& s) const = 0;
    virtual void clear() = 0;
    virtual double getProbabilityOfFalsePositive() const = 0;
    virtual unsigned int getCount() const = 0;
    virtual unsigned long int getBitCount() const = 0;

    protected :
    virtual ~IBloomFilter(){};
  };
};

#endif
