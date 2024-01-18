IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=objs
LDIR =../stb_image

DEPS = $(patsubst %,$(IDIR)/%,$(LDIR))

_OBJ = main.o stb_wrapper.o kmeans.o matrix_math.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kpress: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~