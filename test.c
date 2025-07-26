#include <stdint.h>
#include <stdio.h>

#include "base.h"

static Status status = OK;

#define test(got, want, gotfmt, wantfmt) \
	if ((got) != (want)) { \
		fprintf(stderr, "Failure: %s:%d: got " #gotfmt "; want " #wantfmt "\n", \
			__FILE__, __LINE__, (got), (want)); \
		status = FAIL; \
	} \
	(void)0

static uint64_t
fill(uint16_t k) {
	uint64_t n = 0u;
	while (k--) {
		n |= (1lu << k);
	}
	return n;
}

int
main(void) {
	uint64_t n;
	for (uint16_t k = 0u; k < bitsizeof(n); k++) {
		test(highestOne(1lu << k), k, %d, %d);

		n = fill(k+1u);
		test(highestOne(n), k, %d, %d);
	}

	test(highestOne(0u), 0u, %d, %d);
	test(highestOne(1u), 0u, %d, %d);

	return status;
}
