TARGET = snake

SRCDIR = src
INCDIR = include
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))

GCC = g++
CFLAGS = -g -Wall -I$(INCDIR)
LDFLAGS = -lncurses

all: $(BINDIR)/$(TARGET)

# Compila il target finale
$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(GCC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compila i file sorgente in file oggetto
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	$(GCC) $(CFLAGS) -c -o $@ $<

# Pulisci i file intermedi e l'eseguibile
clean:
	rm -f $(BINDIR)/$(TARGET) $(OBJS)

.PHONY: all clean

