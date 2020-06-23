ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

IDIR = ../include
CFLAGS = -I$(IDIR)
LIBS = -lm -lpng

ODIR = ../obj

_DEPS = KEngine.h uthash.h utarray.h vertex.h material.h texture.h matrix.h geometry.h fragment.h light.h process.h shade.h parse.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o draw.o png_write.o mxaa.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

KEngine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o