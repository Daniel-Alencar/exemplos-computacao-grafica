#include "Structs.h"

int asteroidsDeepLevel = 4;

int ASTEROIDS_LENGTH_ARRAY = (int) pow(2, asteroidsDeepLevel) - 1;
Object_transformation *asteroidsArray = 
(Object_transformation*) malloc(sizeof(Object_transformation) * ASTEROIDS_LENGTH_ARRAY);

void clearAsteroidsEnables() {
	for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) {
		asteroidsArray[i].enable = false;
	}
}

int getLeftChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2 - 1;
}

int getRightChildrenIndex(int asteroidIndex) {
	asteroidIndex += 1;
	return asteroidIndex * 2;
}

void divideAsteroid(int asteroidIndex) {

	int left = getLeftChildrenIndex(asteroidIndex);
	int right = getRightChildrenIndex(asteroidIndex);
	printf("Left: %d e Right: %d\n", left, right);

	// Habilitando/Desabilitando asteroides
	asteroidsArray[asteroidIndex].enable = false;

	if(left < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[left].enable = true;
		// Setando posições para o filho esquerdo
		asteroidsArray[left].angle = asteroidsArray[asteroidIndex].angle + 30;
		asteroidsArray[left].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[left].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[left].xStep = cos(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[left].yStep = sin(
			convertDegreesToRadians(asteroidsArray[left].angle)
		) * ASTEROID_VELOCITY;
	}

	if(right < ASTEROIDS_LENGTH_ARRAY) {
		asteroidsArray[right].enable = true;
		// Setando posições para o filho direito
		asteroidsArray[right].angle = asteroidsArray[asteroidIndex].angle - 30;
		asteroidsArray[right].Tx = asteroidsArray[asteroidIndex].Tx;
		asteroidsArray[right].Ty = asteroidsArray[asteroidIndex].Ty;
		asteroidsArray[right].xStep = cos(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
		asteroidsArray[right].yStep = sin(
			convertDegreesToRadians(asteroidsArray[right].angle)
		) * ASTEROID_VELOCITY;
	}

}