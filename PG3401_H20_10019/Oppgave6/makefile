# Makefiletemplate

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

_OBJS = Oppgave6.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
        
main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS) -pthread -lrt

.PHONY: clean
clean:
	rm-f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ 
