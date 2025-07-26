#include "base.h"

int
highestOne(long unsigned int n) {
	int k = sizeof(n) * 8 - 1;
	while ((k > 0) && !(n & (1lu << k))) {
		k--;
	}
	return k;
}
