#include <assert.h>
#include <stdio.h>

#include "base.h"

static int status = 0;

#define test(got, want, gotfmt, wantfmt) \
	if ((got) != (want)) { \
		fprintf(stderr, "Failure: %s:%d: got " #gotfmt "; want " #wantfmt "\n", \
			__FILE__, __LINE__, (got), (want)); \
		status = 1; \
	} \
	(void)0

static long unsigned int
fill(int k) {
	long unsigned int n = 0;
	while (k--) {
		n |= (1lu << k);
	}
	return n;
}

int
main(void) {
	for (int k = 0; k < sizeof(long unsigned int)*8; k++) {
		test(highestOne(1lu << k), k, %d, %d);

		long unsigned int n = fill(k+1);
		test(highestOne(n), k, %d, %d);
	}

	test(highestOne(0), 0, %d, %d);
	test(highestOne(1), 0, %d, %d);

	return status;
}
