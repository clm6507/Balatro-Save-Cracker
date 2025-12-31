RM = rm -f

CXX = g++
CXXFLAGS = -O0 -std=c++17

balatro_save_cracker: balatro_save_cracker.o
	$(CXX) $(CXXFLAGS) -o $@ $^

balatro_save_cracker.o: balatro_save_cracker.cpp utils.hpp items.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) balatro_save_cracker.o

realclean: clean
	$(RM) balatro_save_cracker