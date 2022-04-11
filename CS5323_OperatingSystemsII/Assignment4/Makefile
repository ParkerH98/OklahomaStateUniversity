#==========================
#		Constants
#==========================
CC = gcc
OBJS = assn4.o
EXECS = p t

#==========================
#		Executable
#==========================
assn4.o: assn4.c
	$(CC) -c assn4.c 

p: $(OBJS) 
	clear
	$(CC) -o p $(OBJS)

test:
	# rm *.o $(EXECS)
	gcc assn4.c -o t
	./t bzip.txt 4 lru

#==========================
#		Utilities
#==========================
clean:
	clear
	rm *.o $(EXECS)