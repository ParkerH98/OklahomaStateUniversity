#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = 
OBJS = parker.o
EXECS = p

#==========================
#		Executable
#==========================
parker.o: parker.c
	$(CC) $(CFLAGS) -c parker.c

p: $(OBJS) 
	clear
	$(CC) $(CFLAGS) -o p $(OBJS)
	
#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)