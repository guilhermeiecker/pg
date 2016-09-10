CC=g++
CFLAGS=-Wall -std=c++11

OBJITE= iterative.o Iterative.o Network.o Link.o Node.o
OBJREC= recursive.o Recursive.o Network.o Link.o Node.o

iterative: $(OBJITE)
	$(CC) $(CFLAGS) $(OBJITE) -o iterative

recursive: $(OBJREC)
	$(CC) $(CFLAGS) $(OBJREC) -o recursive

iterative.o: iterative.cc
	$(CC) $(CFLAGS) -c iterative.cc

recursive.o: recursive.cc
	$(CC) $(CFLAGS) -c recursive.cc

Iterative.o: Iterative.cc
	$(CC) $(CFLAGS) -c Iterative.cc

Recursive.o: Recursive.cc
	$(CC) $(CFLAGS) -c Recursive.cc

Network.o: Network.cc
	$(CC) $(CFLAGS) -c Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) -c Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) -c Node.cc

clean:
	rm *.o iterative recursive
