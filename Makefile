CC=g++
CFLAGS=-c -Wall -std=c++11

all: scheduling

scheduling: scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Network.o Link.o Node.o
	$(CC) scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Network.o Link.o Node.o -o scheduling

scheduling.o: scheduling.cc
	$(CC) $(CFLAGS) scheduling.cc

Algorithm1.o: Algorithm1.cc
	$(CC) $(CFLAGS) Algorithm1.cc

Algorithm2.o: Algorithm2.cc
	$(CC) $(CFLAGS) Algorithm2.cc

Algorithm3.o: Algorithm3.cc
	$(CC) $(CFLAGS) Algorithm3.cc
	
Network.o: Network.cc
	$(CC) $(CFLAGS) Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) Node.cc

clean:
	rm *.o scheduling
