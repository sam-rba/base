#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

typedef enum {
	BIN,
	OCT,
	DEC,
	HEX,
} Base;

enum {ARGC = 3};

const char usage[] =
	"Usage: base -<base><base> <n>\n"
	"base ::= b | o | d | x\n"
	"	b - binary\n"
	"	o - octal\n"
	"	d - decimal\n"
	"	x - hexadecimal\n"
	"n ::= a number";

static Status
parseBase(char c, Base *base) {
	switch (c) {
	case 'b': *base = BIN; break;
	case 'o': *base = OCT; break;
	case 'd': *base = DEC; break;
	case 'x': *base = HEX; break;
	default: return FAIL;
	}
	return OK;
}

static Status
parseBin(const char *s, uint64_t *n) {
	*n = 0;
	while (*s != '\0') {
		switch (*s) {
		case '0': *n <<= 1; break;
		case '1': *n = (*n << 1) | 1; break;
		default: return FAIL;
		}
		s++;
	}
	return OK;
}

static Status
parseNum(Base base, const char *s, uint64_t *n) {
	const char *fmt;

	switch (base) {
	case BIN: return parseBin(s, n);
	case OCT: fmt = "%lo"; break;
	case DEC: fmt = "%lu"; break;
	case HEX: fmt = "%lx"; break;
	default: abort();
	}

	return (sscanf(s, fmt, n) == 1) ? OK : FAIL;
}

static void
printBin(uint64_t n) {
	for (int16_t k = highestOne(n); k >= 0; k--) {
		putchar((n & (1lu << k)) ? '1' : '0');
	}
	putchar('\n');
}

static void
printNum(uint64_t n, Base base) {
	switch (base) {
	case BIN: printBin(n); break;
	case OCT: printf("%lo\n", n); break;
	case DEC: printf("%lu\n", n); break;
	case HEX: printf("%lX\n", n); break;
	default: abort();
	}
}

int
main(int argc, char *argv[]) {
	if ((argc != ARGC)) {
		fprintf(stderr, "Wrong number of arguments.\n%s\n", usage);
		return FAIL;
	}
	if (strlen(argv[1]) != 3) {
		fprintf(stderr, "Invalid argument: %s\n%s\n", argv[1], usage);
		return FAIL;
	}

	Base from, to;
	if (parseBase(argv[1][1], &from) != OK) {
		fprintf(stderr, "Invalid base: %c\n%s\n", argv[1][1], usage);
		return FAIL;
	}
	if (parseBase(argv[1][2], &to) != OK) {
		fprintf(stderr, "Invalid base: %c\n%s\n", argv[1][2], usage);
		return FAIL;
	}

	uint64_t n;
	if (parseNum(from, argv[2], &n) != OK) {
		fprintf(stderr, "Invalid number: %s\n", argv[2]);
		return FAIL;
	}

	printNum(n, to);
}
