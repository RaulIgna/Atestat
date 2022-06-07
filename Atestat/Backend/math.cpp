#include "math.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include <assert.h>	


namespace MATH {
	int RandomNumber(int low, int high) {
		assert(low < high);
		return rand() % high + low;
	}
}