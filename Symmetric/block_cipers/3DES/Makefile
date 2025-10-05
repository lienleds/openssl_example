CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lssl -lcrypto

all: des_ede3_cbc_example

des_ede3_cbc_example: des_ede3_cbc_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f des_ede3_cbc_example
