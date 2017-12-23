#include <sylib/math.h>

using namespace sylib;

double pi2pi (double rad)
{/*{{{*/
	while (M_PI < rad) {
		rad -= 2 * M_PI;
	}
	while (rad < -M_PI) {
		rad += 2 * M_PI;
	}

	return rad;
}/*}}}*/
