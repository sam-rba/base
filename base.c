#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Base {
	BIN,
	OCT,
	DEC,
	HEX,
};

const char usage[] =
	"Usage: base -<base><base> <n>\n"
	"base ::= b | o | d | h | x\n"
	"	b - binary\n"
	"	o - octal\n"
	"	d - decimal\n"
	"	h, x - hexadecimal\n"
	"n ::= a number";

static int
parseBase(char c, enum Base *base) {
	switch (c) {
	case 'b': *base = BIN; break;
	case 'o': *base = OCT; break;
	case 'd': *base = DEC; break;
	case 'h': case 'x': *base = HEX; break;
	default: return 1;
	}
	return 0;
}

static int
parseBin(const char *s, long unsigned int *n) {
	if (strstr(s, "0b") || strstr(s, "0B")) {
		s += 2;
	}
	*n = 0;
	while (*s != '\0') {
		switch (*s) {
		case '0': *n <<= 1; break;
		case '1': *n = (*n << 1) | 1; break;
		default: return 1;
		}
		s++;
	}
	return 0;
}

static int
parseNum(enum Base base, const char *s, long unsigned int *n) {
	const char *fmt;

	switch (base) {
	case BIN: return parseBin(s, n);
	case OCT: fmt = "%lo"; break;
	case DEC: fmt = "%lu"; break;
	case HEX: fmt = "%lx"; break;
	default: abort();
	}

	return sscanf(s, fmt, n) != 1;
}

static int
highestOne(long unsigned int n) {
	int k = sizeof(n) * 8 - 1;
	while (!(n & (1 << k))) {
		k--;
	}
	return k;
}

static void
printBin(long unsigned int n) {
	for (int k = highestOne(n); k >= 0; k--) {
		putchar((n & (1 << k)) ? '1' : '0');
	}
}

static void
printNum(long unsigned int n, enum Base base) {
	switch (base) {
	case BIN: printBin(n); break;
	case OCT: printf("%lo\n", n); break;
	case DEC: printf("%lu\n", n); break;
	case HEX: printf("%lx\n", n); break;
	default: abort();
	}
}

int
main(int argc, char *argv[]) {
	if ((argc != 3)) {
		fprintf(stderr, "Wrong number of arguments.\n%s\n", usage);
		return 1;
	}
	if (strlen(argv[1]) != 3) {
		fprintf(stderr, "Invalid argument: %s\n%s\n", argv[1], usage);
		return 1;
	}

	enum Base from, to;
	if (parseBase(argv[1][1], &from) != 0) {
		fprintf(stderr, "Invalid base: %c\n%s\n", argv[1][1], usage);
		return 1;
	} else if (parseBase(argv[1][2], &to) != 0) {
		fprintf(stderr, "Invalid base: %c\n%s\n", argv[1][2], usage);
		return 1;
	}

	long unsigned int n;
	if (parseNum(from, argv[2], &n) != 0) {
		fprintf(stderr, "Invalid number: %s\n", argv[2]);
		return 1;
	}

	printNum(n, to);
}
