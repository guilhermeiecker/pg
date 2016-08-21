CC=g++
CFLAGS=-Wall -std=c++11 -fopenmp
OBJECTS= scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Algorithm4.o Algorithm5.o Algorithm6.o Network.o Link.o Node.o

all: scheduling
	
scheduling: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o scheduling
		
scheduling.o: scheduling.cc
	$(CC) $(CFLAGS) -c scheduling.cc

Algorithm1.o: Algorithm1.cc
	$(CC) $(CFLAGS) -c Algorithm1.cc

Algorithm2.o: Algorithm2.cc
	$(CC) $(CFLAGS) -c Algorithm2.cc
	
Algorithm3.o: Algorithm3.cc
	$(CC) $(CFLAGS) -c Algorithm3.cc
	
Algorithm4.o: Algorithm4.cc
	$(CC) $(CFLAGS) -c Algorithm4.cc

Algorithm5.o: Algorithm5.cc
	$(CC) $(CFLAGS) -c Algorithm5.cc
	
Algorithm6.o: Algorithm6.cc
	$(CC) $(CFLAGS) -c Algorithm6.cc
	
Network.o: Network.cc
	$(CC) $(CFLAGS) -c Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) -c Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) -c Node.cc

clean:
	rm $(OBJECTS) scheduling
