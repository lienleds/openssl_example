CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto

all: sha3_384_example

sha3_384_example: sha3_384_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f sha3_384_example
