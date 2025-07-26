CC = tcc
CFLAGS = -Wall -g
LDFLAGS = -static -Lmusl/lib

PREFIX = $(HOME)/.local/bin

SRC = base.c
OBJ = $(SRC:.c=.o)

base: $(OBJ) main.o musl/lib
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) main.o

.PHONY: clean
clean:
	rm -f *.o base

.PHONY: test
test: base test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o test $(OBJ) test.o
	./test
	awk -f test.awk tests
	@echo Success

.PHONY: install
install: base
	mkdir -p $(PREFIX)
	cp -f base $(PREFIX)

.c.o:
	$(CC) -c $(CFLAGS) $<

musl/lib: musl
	git submodule update --init musl
	cd musl && ./configure
	make -C musl
