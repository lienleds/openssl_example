CC=g++
CFLAGS=-Wall -Wextra -std=c++11 -I/opt/homebrew/opt/openssl@3/include
LIBS=-L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto

seed_example: seed_example.cpp
	$(CC) $(CFLAGS) -o seed_example seed_example.cpp $(LIBS)

clean:
	rm -f seed_example

.PHONY: clean