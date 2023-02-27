# Nom de l'application (nom de l'exécutable)
TARGET=carnet

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

MYSQLLIB=`mysql_config --cflags --libs`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) $(MYSQLLIB) -export-dynamic

OBJS= main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) $(MYSQLLIB) -o main.o
    
clean:
	rm -f *.o $(TARGET)