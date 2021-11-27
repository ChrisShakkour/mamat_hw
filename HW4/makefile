
CC=gcc
CFLAGS= -g -Wall -std=c99
CCLINK=$(CC)
OBJS=grades.o
EXEC=libgrades.so
RM=rm -Rf *.o $(EXEC)

# Linking stage:
libgrades.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o $(EXEC) -llinked-list -L.

# Compilation stages:
grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c

# Clean env
clean:
	$(RM)
