IDIR=../include
ODIR=obj
LDIR=lib
DDIR=../doc
RDIR=../tex
OLDIR=$(ODIR)/lib
ROOT=../


CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)	

doc:	
	cd    $(IDIR) && doxygen -g && doxygen
	mv    $(IDIR)/Doxyfile $(DDIR)/Doxyfile
	mv    $(IDIR)/latex $(DDIR)/latex
	mv    $(IDIR)/html $(DDIR)/html
	
relatorio:
	cd $(RDIR) && pdflatex relatorio.tex
	mv $(RDIR)/relatorio.pdf $(ROOT)/relatorio.pdf

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program
	rm -r $(DDIR)/latex
	rm -r $(DDIR)/html
	rm    $(DDIR)/Doxyfile
	cd    $(RDIR) && (GLOBIGNORE='logoUM.jpg:relatorio.tex'; rm relatorio.*)
	rm    $(ROOT)/relatorio.pdf		