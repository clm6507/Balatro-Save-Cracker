RM = rm -f

CXX = g++
CXXFLAGS = -O0 -std=c++17 -g

immolate: immolate.o
	$(CXX) $(CXXFLAGS) -o $@ $^

immolate.o: immolate.cpp immolate.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) immolate.o

realclean: clean
	$(RM) immolate