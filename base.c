#include <stdint.h>

#include "base.h"

uint16_t
highestOne(uint64_t n) {
	uint16_t k = bitsizeof(n) - 1u;
	while ((k > 0) && !(n & (1lu << k))) {
		k--;
	}
	return k;
}
