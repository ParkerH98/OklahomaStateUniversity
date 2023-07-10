#==========================
#		Constants
#==========================
CC = gcc
OBJS = parker.o
EXECS = p t

#==========================
#		Executable
#==========================
parker.o: parker.c
	$(CC) -c parker.c 

p: $(OBJS) 
	clear
	$(CC) -o p $(OBJS)

test:
	# rm *.o $(EXECS)
	gcc parker.c -o t
	./t _bzip.txt 5 fifo

#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)