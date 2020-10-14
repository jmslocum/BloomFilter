CXX = g++
CXXFLAGS = -O3 -Wall -Wextra --std=c++20
LINK = -lm
OBJS = MurmurHash2.o DynamicBloomFilter.o FixedBloomFilter.o bloom_test.o
EXE = bloom_test

bloom_test : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LINK)

MurmurHash2.o : MurmurHash2.cpp
	$(CXX) -c -O3 $< -o $@

clean : 
	rm -rf $(OBJS)
	rm -rf $(EXE)

