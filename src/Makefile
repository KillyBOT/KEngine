ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

IDIR = ../include
CFLAGS = -I$(IDIR)
LIBS = -lm -lpng -ljpeg -lpthread

ODIR = ../obj

_DEPS = KEngine.h uthash.h utarray.h vertex.h material.h texture.h matrix.h geometry.h fragment.h light.h process.h shade.h parse.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = lex.obj.o obj.tab.o lex.mtl.o mtl.tab.o main.o draw.o png_write.o jpg_read.o msaa.o matrix.o material.o texture.o matrix_op.o vertex.o shape.o box.o geometry.o fragment.o rasterize.o vshade.o gshade.o fshade.o light.o ref_phong.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

KEngine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

lex.obj.c: obj.l obj.tab.h
	flex -o lex.obj.c -P obj_yy obj.l

obj.tab.c: obj.y
	bison -p obj_yy -d obj.y

obj.tab.h: obj.y
	bison -p obj_yy -d obj.y
	mv obj.tab.h ../include

lex.mtl.c: mtl.l mtl.tab.h
	flex -o lex.mtl.c -P mtl_yy mtl.l

mtl.tab.c: mtl.y
	bison -p mtl_yy -d mtl.y

mtl.tab.h: mtl.y
	bison -p mtl_yy -d mtl.y
	mv mtl.tab.h ../include

clean:
	rm lex.*.c
	rm *.tab.c
	rm *.tab.h
	rm -f $(ODIR)/*.o

run: KEngine
	./KEngine box.obj test.png
