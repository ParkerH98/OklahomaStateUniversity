#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = 
OBJS = assignment2.o
EXECS = p
# HEADER = header.h


#==========================
#		Executable
#==========================
assignment2.o: assignment2.c
	$(CC) $(CFLAGS) -c assignment2.c

p: $(OBJS) 
	clear
	$(CC) $(CFLAGS) -o p $(OBJS)
	
# assignment2.o: assignment2.c $(HEADER)  # step 2
# $(CC) $(CFLAGS) -c assignment2.c


#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)