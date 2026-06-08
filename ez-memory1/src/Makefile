#IDIR = ../include
CC = gcc
CFLAGS1 = -g -O2 -Wall -Wpedantic -Wdeprecated -Wextra -Werror=return-type 
CFLAGS2 = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra -Wpedantic -Werror=return-type
TARGET1 = ez_memory1
TARGET2 = ez_memory1_debug
ODIR = obj
#LDIR = ../lib
#LIBS =	# Here put libraries to compile against.
BDIR = ../bin

#_DEPS = $(wildcard *.h)
#DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o : %.c #$(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET1) : $(OBJ)
	@$(CC) -o $(BDIR)/$@ $^ $(CFLAGS1) #$(LIBS)

$(TARGET2) : $(OBJ)
	@$(CC) -o $(BDIR)/$@ $^ $(CFLAGS2)

.phony : clean

clean :
	@rm -f $(ODIR)/*.o


