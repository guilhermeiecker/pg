CC=g++
CFLAGS=-Wall -std=c++11

OBJNET= network.o Network.o Link.o Node.o

network: $(OBJNET)
	$(CC) $(CFLAGS) $(OBJNET) -o network

network.o: network.cc
		$(CC) $(CFLAGS) -c network.cc

Network.o: Network.cc
	$(CC) $(CFLAGS) -c Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) -c Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) -c Node.cc

clean:
	rm *.o network
