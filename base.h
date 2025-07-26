/* Usage:
 *
 * #include <stdint.h>
 * #include "base.h"
 */

#define bitsizeof(x) (sizeof(x)*8u)

typedef enum {
	OK,
	FAIL,
} Status;

uint16_t highestOne(uint64_t n);
