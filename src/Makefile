IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../stb_image

DEPS = $(patsubst %,$(IDIR)/%,$(LDIR))

_OBJ = main.o stb_wrapper.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kpress: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 