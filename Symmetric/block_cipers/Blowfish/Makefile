# Blowfish Encryption Example Makefile

# Adjust these paths if you use Intel Mac (usually /usr/local instead of /opt/homebrew)
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lssl -lcrypto
TARGET = blowfish_example
SRC = blowfish_example.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean