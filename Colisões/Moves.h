
Object_transformation changeSpaceshipTranslation(Object_transformation spaceship) {
	// Translação da NAVE
	// Muda a posição quando chega na borda esquerda e direita
	if((spaceship.Tx+spaceship.maxX) > windowXmax) {
		spaceship.Tx = -range;
	} else if((spaceship.Tx+spaceship.minX) < windowXmin) {
		spaceship.Tx = +range;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((spaceship.Ty+spaceship.maxY) > windowYmax) {
		spaceship.Ty = -range;
	} else if((spaceship.Ty+spaceship.minY) < windowYmin) {
		spaceship.Ty = +range;
	}
  return spaceship;
}

Object_transformation changeAsteroidTranslation(Object_transformation asteroid) {
	// Translação do ASTERÓIDE
	// Muda a posição quando chega na borda esquerda e direita
	if((asteroid.Tx+asteroid.maxX) > windowXmax) {
		printf("Lado direito\n");
		asteroid.Tx = -range + asteroid.minX;
	} else if((asteroid.Tx+asteroid.minX) < windowXmin) {
		printf("Lado esquerdo\n");
		asteroid.Tx = +range + asteroid.maxX;
	}
	// Muda a posição quando chega na borda superior e inferior
	if((asteroid.Ty+asteroid.maxY) > windowYmax) {
		printf("Lado de cima\n");
		asteroid.Ty = -range + asteroid.minY;
	} else if((asteroid.Ty+asteroid.minY) < windowYmin) {
		printf("Lado de baixo\n");
		asteroid.Ty = +range + asteroid.maxY;
	}

  return asteroid;
}

Object_transformation clearSpaceshipMoves(Object_transformation spaceship) {
	spaceship.Tx = 0;
	spaceship.Ty = 0;
	spaceship.xStep = 0;
	spaceship.yStep = 0;

  return spaceship;
}

void updateLives(){
	lives--;
	if(lives == 0) {
		printf("Finalização do jogo!\n");

		spaceship = clearSpaceshipMoves(spaceship);
		scene = SCENE_GAMEOVER;
	} else {
		printf("TOMOU DANO\n");
		spaceship = clearSpaceshipMoves(spaceship);
	}
}

void draw() {

	// Nave nas bordas da tela
	spaceship = changeSpaceshipTranslation(spaceship);

	// Asteroides nas bordas da tela
	for(int j = 0; j < ASTEROIDS_ARRAY_QUANTITY; j++) {
		Object_transformation *asteroidsArray = asteroidsArraysArray[j];

		for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) { 
			if(asteroidsArray[i].enable) {
				asteroidsArray[i] = changeAsteroidTranslation(asteroidsArray[i]);
			}
		}
	}
  
  // Verificando colisões
	if(scene == SCENE_GAME) {
		// Verificar pressionamento de teclas
		updateMovesWithPressedKeys();

		for(int j = 0; j < ASTEROIDS_ARRAY_QUANTITY; j++) {
			Object_transformation *asteroidsArray = asteroidsArraysArray[j];

			for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) {
				if(asteroidsArray[i].enable) {
					
					int k;
					for(k = 0; k < bulletsLength; k++) {
						bulletColision = verifyBulletCollision(
							asteroidsArray[i],
							bullets[k]
						);

						if(bulletColision) {
							break;
						}
					}
					
					spaceshipCollision = verifySpaceshipCollision(
						asteroidsArray[i],
						spaceship
					);

					if(bulletColision) {
						printf("Bala colidiu!\n");
						bullets[k].enable = false;

						asteroidsArray = divideAsteroid(i, asteroidsArray);
					}
					if(spaceshipCollision) {
						updateLives();
						break;
					}

				}
			}
		}
	}

  // Movimentando objetos
	if(scene == SCENE_START || scene == SCENE_GAME) {
		
    // Move a bala
		for(int i = 0; i < bulletsLength; i++) {
			if(bullets[i].enable) {
				if(
					bullets[i].Tx > -range && bullets[i].Tx < +range &&
					bullets[i].Ty > -range && bullets[i].Ty < +range
				) {
					bullets[i].Tx += bullets[i].xStep;
					bullets[i].Ty += bullets[i].yStep;

				} else {
					bullets[i].enable = false;
				}
			}
		}

    // Move a Nave
    spaceship.Tx += spaceship.xStep;
    spaceship.Ty += spaceship.yStep;
		spaceship.xStep /= SPACESHIP_DESACCELERATION_FACTOR;
		spaceship.yStep /= SPACESHIP_DESACCELERATION_FACTOR;

		if(abs(spaceship.xStep) < 0.01f && abs(spaceship.yStep < 0.01f)) {
			spaceshipWithAcceleration = false;
		}

    // Move os Asteroids
		for(int j = 0; j < ASTEROIDS_ARRAY_QUANTITY; j++) {
			Object_transformation *asteroidsArray = asteroidsArraysArray[j];

			for(int i = 0; i < ASTEROIDS_LENGTH_ARRAY; i++) { 
				if(asteroidsArray[i].enable) {
					asteroidsArray[i].Tx += asteroidsArray[i].xStep;
					asteroidsArray[i].Ty += asteroidsArray[i].yStep;
				}
			}
		}
	}
}