#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = 
OBJS = assignment1.o
EXECS = p
# HEADER = header.h


#==========================
#		Executable
#==========================
assignment1.o: assignment1.c
	$(CC) $(CFLAGS) -c assignment1.c

p: $(OBJS) 
	clear
	$(CC) $(CFLAGS) -o p $(OBJS)
	
# assignment1.o: assignment1.c $(HEADER)  # step 2
# $(CC) $(CFLAGS) -c assignment1.c


#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)