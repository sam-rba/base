CC = tcc
CFLAGS = -Wall -g
LDFLAGS = -static -Lmusl/lib

base: base.o musl/lib
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $<

musl/lib: musl
	cd musl && ./configure
	make -C musl

clean:
	rm -f *.o base
