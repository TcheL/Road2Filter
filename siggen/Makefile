
CC := gcc
BINDIR := ../bin
OBJDIR := ../obj
CFLAGS :=
LFLAGS := -lm

.PHONY : Periodic Other Random

all : prepto Periodic Other Random

prepto :
	mkdir -p $(BINDIR) $(OBJDIR)

Periodic :
	$(CC) $@/parabolic.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/parabolic
	$(CC) $@/sawtooth.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/sawtooth
	$(CC) $@/sine.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/sine
	$(CC) $@/sines.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/sines
	$(CC) $@/square.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/square
	$(CC) $@/triangle.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/triangle

Other :
	$(CC) $@/impulsetrain.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/impulsetrain
	$(CC) $@/step.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/step
	$(CC) $@/fm.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/fm
	$(CC) $@/fmline.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/fmline

Random :
	$(CC) $@/noise.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/noise
	$(CC) $@/pinkgen.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/pinkgen
	$(CC) $@/bernrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/bernrv
	$(CC) $@/brownrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/brownrv
	$(CC) $@/cauchyrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/cauchyrv
	$(CC) $@/laplacerv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/laplacerv
	$(CC) $@/gaussrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/gaussrv
	$(CC) $@/stdgaussrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/stdgaussrv
	$(CC) $@/uniformrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/uniformrv
	$(CC) $@/exponentialrv.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/exponentialrv
	$(CC) $@/telegraph.c $(CFLAGS) $(LFLAGS) -o $(BINDIR)/telegraph

clean :
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.a

cleanall : clean
	rm -f $(BINDIR)/*

# vim:ft=make:noet
