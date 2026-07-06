IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -std=c99 -g -O2 -Wall -Wpedantic -Wdeprecated -Wextra -Werror=return-type 
TARGET = main

ODIR = obj
#LDIR = ../lib
#LIBS =	# Here put libraries to compile against.
BDIR = ../bin

_DEPS = $(wildcard *.h)
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o : %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJ)
	@$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) #$(LIBS)

.phony : clean

clean :
	@rm -f $(ODIR)/*.o


