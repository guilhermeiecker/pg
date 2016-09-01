CC=g++
CFLAGS=-Wall -std=c++11 -fopenmp
OBJECTS= scheduling.o Algorithm1.o Algorithm2.o Algorithm3.o Algorithm4.o Algorithm5.o Algorithm6.o Network.o Link.o Node.o

OBJECTS1= scheduling1.o Algorithm1.o Network.o Link.o Node.o
OBJECTS2= scheduling2.o Algorithm2.o Network.o Link.o Node.o
OBJECTS3= scheduling3.o Algorithm3.o Network.o Link.o Node.o
OBJECTS4= scheduling4.o Algorithm4.o Network.o Link.o Node.o
OBJECTS5= scheduling5.o Algorithm5.o Network.o Link.o Node.o
OBJECTS6= scheduling6.o Algorithm6.o Network.o Link.o Node.o

all: scheduling
	
scheduling: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o scheduling

scheduling1: $(OBJECTS1)
	$(CC) $(CFLAGS) $(OBJECTS1) -o scheduling1

scheduling2: $(OBJECTS2)
	$(CC) $(CFLAGS) $(OBJECTS2) -o scheduling2
	
scheduling3: $(OBJECTS3)
	$(CC) $(CFLAGS) $(OBJECTS3) -o scheduling3
	
scheduling4: $(OBJECTS4)
	$(CC) $(CFLAGS) $(OBJECTS4) -o scheduling4
	
scheduling5: $(OBJECTS5)
	$(CC) $(CFLAGS) $(OBJECTS5) -o scheduling5
	
scheduling6: $(OBJECTS6)
	$(CC) $(CFLAGS) $(OBJECTS6) -o scheduling6
	
scheduling.o: scheduling.cc
	$(CC) $(CFLAGS) -c scheduling.cc

scheduling1.o: scheduling1.cc
	$(CC) $(CFLAGS) -c scheduling1.cc
	
scheduling2.o: scheduling2.cc
	$(CC) $(CFLAGS) -c scheduling2.cc
	
scheduling3.o: scheduling3.cc
	$(CC) $(CFLAGS) -c scheduling3.cc
	
scheduling4.o: scheduling4.cc
	$(CC) $(CFLAGS) -c scheduling4.cc
	
scheduling5.o: scheduling5.cc
	$(CC) $(CFLAGS) -c scheduling5.cc
	
scheduling6.o: scheduling6.cc
	$(CC) $(CFLAGS) -c scheduling6.cc
	
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

