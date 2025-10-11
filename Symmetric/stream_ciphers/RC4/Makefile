CXX = g++
CXXFLAGS = -g -ggdb -fno-standalone-debug -std=c++11 -Wall -Wextra -I/opt/homebrew/include -I/usr/local/include
LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -lssl -lcrypto

TARGET = rc4_example
all: $(TARGET)

$(TARGET): rc4_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)
