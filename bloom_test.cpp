#include "DynamicBloomFilter.hpp"
#include "FixedBloomFilter.hpp"

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <set>

using std::string;
using std::cout;
using std::cerr;
using std::fstream;
using std::set;

using jms::IBloomFilter;
using jms::FixedBloomFilter;
using jms::DynamicBloomFilter;
using jms::FixedSize;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <word_set_filename> <test_filename>\n";
    cerr << "load lines into a bloom filter for a test\n";
    return 1;
  }

  string filename{argv[1]};

  fstream input(filename, std::ios::in);
  //DynamicBloomFilter bloomFilter{52875, 0.01};
  FixedBloomFilter<FixedSize::SMALL> bloomFilter{};
  set<string> verificationSet;

  cout << "BloomFilter is " << ((bloomFilter.getBitCount() * sizeof(bool)) / 8.0) / 1024.0 << " K bytes\n";

  string line;
  while(!input.eof()) {
    input >> line;
    bloomFilter.add(line);
    verificationSet.insert(line);
  }

  input.close();
  
  cout << "Bloom Filter loaded with " << bloomFilter.getCount() << " words\n";
  cout << "Error probability: " << bloomFilter.getProbabilityOfFalsePositive() << "\n";

  filename = string{argv[2]};
  input = fstream{filename, std::ios::in};

  double good = 0.0, bad = 0.0, total = 0.0;
  while(!input.eof()) {
    input >> line;

    if (bloomFilter.contains(line) == verificationSet.contains(line)) {
      good += 1.0;
    }
    else {
      bad += 1.0;
    }

    total += 1.0;
  }

  input.close();

  cout << "Bloom Filter matched verification set " << ((good / total) * 100.0) << "%\n";
  cout << "Actual Error Probability: " << (bad / total) << "\n";


  return 0;
}
