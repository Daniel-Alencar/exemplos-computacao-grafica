#include <time.h>

double convertDegreesToRadians(double degrees) {
	return ((2*M_PI * degrees) / 360);
}

float generateRandomFloat() {
	srand(time(NULL));

	float random = ((float)rand() / RAND_MAX);
	return random;
}
