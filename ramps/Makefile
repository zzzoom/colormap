CFLAGS+= -I..

TARGETS=ramps

all: $(TARGETS)

ramps: ramps.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(TARGETS)

