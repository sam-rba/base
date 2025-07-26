CC = tcc
CFLAGS = -Wall -g
LDFLAGS = -static -Lmusl/lib

SRC = base.c
OBJ = $(SRC:.c=.o)

base: $(OBJ) main.o musl/lib
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) main.o

.c.o:
	$(CC) -c $(CFLAGS) $<

musl/lib: musl
	cd musl && ./configure
	make -C musl

.PHONY: clean
clean:
	rm -f *.o base

.PHONY: test
test: base test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o test $(OBJ) test.o
	./test
	awk -f test.awk tests
	@echo Success
