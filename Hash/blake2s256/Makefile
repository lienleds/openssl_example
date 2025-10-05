CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto

all: blake2s256_example

blake2s256_example: blake2s256_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f blake2s256_example
