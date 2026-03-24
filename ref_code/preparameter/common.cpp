#include "common.h"

double Ev3NearZero(void) {
	// returns a very small positive value
	return 1/LARGE;
}

double Ev3Infinity(void) {
	// returns a very large positive value
	return LARGE;
}