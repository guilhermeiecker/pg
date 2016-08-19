CC=g++
CFLAGS=-c -Wall -std=c++11 -fopenmp

all: scheduling
	
tester: network-tester.o Network.o Link.o Node.o
	$(CC) network-tester.o Network.o Link.o Node.o -o tester
	
scheduling: scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Algorithm4.o Algorithm5.o Algorithm6.o Network.o Link.o Node.o
	$(CC) scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Algorithm4.o Algorithm5.o Algorithm6.o Network.o Link.o Node.o -o scheduling -fopenmp

network-tester.o: network-tester.cc
	$(CC) $(CFLAGS) network-tester.cc
		
scheduling.o: scheduling.cc
	$(CC) $(CFLAGS) scheduling.cc

Algorithm1.o: Algorithm1.cc
	$(CC) $(CFLAGS) Algorithm1.cc

Algorithm2.o: Algorithm2.cc
	$(CC) $(CFLAGS) Algorithm2.cc
	
Algorithm3.o: Algorithm3.cc
	$(CC) $(CFLAGS) Algorithm3.cc
	
Algorithm4.o: Algorithm4.cc
	$(CC) $(CFLAGS) Algorithm4.cc

Algorithm5.o: Algorithm5.cc
	$(CC) $(CFLAGS) Algorithm5.cc
	
Algorithm6.o: Algorithm6.cc
	$(CC) $(CFLAGS) Algorithm6.cc
	
Network.o: Network.cc
	$(CC) $(CFLAGS) Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) Node.cc

clean:
	rm *.o scheduling
	
ct:
	rm *.o tester
