#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = 
OBJS = parker.o
EXECS = p l

#==========================
#		Executable
#==========================
parker.o: parker.c
	$(CC) $(CFLAGS) -c parker.c

p: $(OBJS) 
	clear
	$(CC) $(CFLAGS) -o p $(OBJS)

l: $(OBJS) 
	clear
	$(CC) $(CFLAGS) -o l $(OBJS) -pthread -lrt
		
#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)