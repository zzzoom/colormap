CFLAGS+= -I..
LDFLAGS=-lm

TARGETS=ramps

all: $(TARGETS)

ramps: ramps.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(TARGETS)

