CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto

all: chacha20_poly1305_example

chacha20_poly1305_example: chacha20_poly1305_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f chacha20_poly1305_example
