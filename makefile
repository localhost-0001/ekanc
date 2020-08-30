TARGET=ekanc

# compiler
CC=$(CROSS)gcc
# debug
DEBUG=-g
# optimisation
OPT=-O2
# warnings
WARN=-Wall

AR=$(CROSS)ar

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) 

GTKLIB=`$(CROSS)pkg-config --cflags --libs gtk+-3.0` 

# linker
LD=$(CROSS)gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -lncurses -ltinfo -lpthread -lcurses

OBJS=	ekan.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

ekan.o: ekan.c
	$(CC) -c $(CCFLAGS) ekan.c $(GTKLIB) -o ekan.o

clean:
	rm -f *.o $(TARGET) 
