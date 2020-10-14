# Bloom Filter

This is an implementation of a Bloom Filter in C++ for my own learning and teaching
purposes. A bloom filter is a probabilistic filter that can tell you that
something is probably in a set, or definitely not in a set. It works
by hashing the input data (Mermer2 hash is popular) several times with different
seeds, and then mapping those hashes to a bitmap (array of bits). It flips
those bits to 1's. Then when checking if something is in the set, it hashes the
input again, and if the hash all matches the 1's in the bitmap, it is probably there,
but if it gets any 0's then it definitely isn't there. 

## DynamicBloomFilter

This implementation accepts the maximum number of items expected to be put into the filter
and the desired error probability, and will automatically size itself. 

## FixedBloomFilter

This implementation is a fixed size determined by one of the pre made sizes shown below. 
This is ideal when you don't know the upper limit and instead want a fixed size of memory
for the bloom filter. 

### Sizes

```
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

```

Of course, your free to add any sizes you want. 

## License

Copyright (c) 2020 James Slocum (jamesslocum.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
