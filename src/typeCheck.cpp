#include <limits.h>





int numPlaces(int n)
{
	if (n < 0) n = (n == INT_MIN) ? INT_MAX: -n;
	if (n < 10) return 1;
	if (n < 100) return 2;
	if (n < 1000) return 3;
	if (n < 10000) return 4;
	if (n < 100000) return 5;
	if (n < 1000000) return 6;
	if (n < 10000000) return 7;
	if (n < 100000000) return 8;
	if (n < 1000000000) return 9;
	// Since  2^31 - 1 is the cap, this is going to asympotically faster
	// Than any use of for loops, recursion, or logrithms. I know its not
	// pretty, but its fast.

	return 10;
}
