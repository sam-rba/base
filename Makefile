CC ?= tcc
CFLAGS = -Wall -g
LDFLAGS = -static

base: base.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f base
