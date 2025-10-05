CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lssl -lcrypto

all: aes_ccm_example

aes_ccm_example: aes_ccm_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f aes_ccm_example
