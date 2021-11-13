CFLAGS = -Wall
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex2_q1

all: $(PROG) test

$(PROG).o: $(PROG).c
	@$(ECHO)
	$(CC) $(CFLAGS) -c factors.c -o factors.o
	$(CC) $(CFLAGS) -c $(PROG).c -o $(PROG).o

factors.o: factors.c
	@$(ECHO)
	$(CC) $(CFLAGS) -c factors.c -o factors.o

factors: factors.o
	$(CC) $(CFLAGS) factors.o -o factors

$(PROG): $(PROG).o factors
	$(CC) $(CFLAGS) $(PROG).o -o $(PROG)

test: $(PROG)
	./$(PROG) 11 24 36 7 5 > out.log

clean:
	rm -rf $(PROG) *.log *.o *.tx
