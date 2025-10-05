CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto
all: sm3_example

sm3_example: sm3_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f sm3_example
