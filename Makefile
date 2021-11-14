IDIR=include
CC=gcc
WARNINGS= -Wall -Wextra -Wshadow -Wswitch-enum -Wstack-protector -Wdate-time -Walloc-zero -Walloca -Wimplicit-function-declaration
LIBS=-lm -lulfius 
CFLAGS=-I$(IDIR) -D_XOPEN_SOURCE_EXTENDED $(LIBS)

ODIR=src
LDIR =/usr/local/lib


_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =main.o endpoints.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(WARNINGS) -c -o $@ $< $(CFLAGS) 

WorkHorse: $(OBJ)
	$(CC) $(WARNINGS) -o $@ $^ $(CFLAGS) 
debug: CFLAGS += -DDEBUG -g
debug: WorkHorse

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm WorkHorse
