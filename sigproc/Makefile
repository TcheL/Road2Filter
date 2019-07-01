
CC := gcc
BINDIR := ../bin
OBJDIR := ../obj
CFLAGS :=
LFLAGS := -lm

.PHONY : ButterCheby ButterCoeff FIRCoeff SpectrAnaly

all : prepto ButterCheby ButterCoeff FIRCoeff SpectrAnaly

prepto :
	mkdir -p $(BINDIR) $(OBJDIR)

ButterCheby :
	$(CC) $@/bwlpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/bwlpf
	$(CC) $@/bwhpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/bwhpf
	$(CC) $@/bwbpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/bwbpf
	$(CC) $@/bwbsf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/bwbsf
	$(CC) $@/cheblpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/cheblpf
	$(CC) $@/chebhpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/chebhpf
	$(CC) $@/chebbpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/chebbpf
	$(CC) $@/chebbsf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/chebbsf

ButterCoeff :
	$(CC) -c $@/liir.c $(CFLAGS) -I$@ -o $(OBJDIR)/liir.o
	ar cr $(OBJDIR)/libiir.a $(OBJDIR)/liir.o
	$(CC) $@/bwlp.c $(CFLAGS) -I$@ -L$(OBJDIR) -liir $(LFLAGS) -o $(BINDIR)/bwlp
	$(CC) $@/bwhp.c $(CFLAGS) -I$@ -L$(OBJDIR) -liir $(LFLAGS) -o $(BINDIR)/bwhp
	$(CC) $@/bwbp.c $(CFLAGS) -I$@ -L$(OBJDIR) -liir $(LFLAGS) -o $(BINDIR)/bwbp
	$(CC) $@/bwbs.c $(CFLAGS) -I$@ -L$(OBJDIR) -liir $(LFLAGS) -o $(BINDIR)/bwbs
	$(CC) $@/rffr.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/rffr
	$(CC) $@/rdf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/rdf

FIRCoeff :
	$(CC) $@/tdlpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/tdlpf
	$(CC) $@/tdhpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/tdhpf
	$(CC) $@/tdbpf.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/tdbpf

SpectrAnaly :
	$(CC) $@/goertzel.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/goertzel
	$(CC) $@/fft.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/fft
	$(CC) $@/extract.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/extract

clean :
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.a

cleanall : clean
	rm -f $(BINDIR)/*

# vim:ft=make:noet
