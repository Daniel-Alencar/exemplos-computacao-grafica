
void changeSpaceshipTranslation() {
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
}

void changeAsteroidTranslation() {
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
}

void clearSpaceshipMoves() {
	spaceship.Tx = 0;
	spaceship.Ty = 0;
	spaceship.xStep = 0;
	spaceship.yStep = 0;
}

void divideAsteroid() {
  levelDestructionAsteroid++;
  notDivided = false;

  asteroid1.angle = asteroid.angle + 30;
  asteroid1.Tx = asteroid.Tx;
  asteroid1.Ty = asteroid.Ty;
  asteroid1.xStep = cos(convertDegreesToRadians(asteroid1.angle)) * ASTEROID_VELOCITY;
	asteroid1.yStep = sin(convertDegreesToRadians(asteroid1.angle)) * ASTEROID_VELOCITY;

  asteroid2.angle = asteroid.angle - 45;
  asteroid2.Tx = asteroid.Tx;
  asteroid2.Ty = asteroid.Ty;
  asteroid2.xStep = cos(convertDegreesToRadians(asteroid2.angle)) * ASTEROID_VELOCITY;
	asteroid2.yStep = sin(convertDegreesToRadians(asteroid2.angle)) * ASTEROID_VELOCITY;
}

void draw() {
	
	changeSpaceshipTranslation();
	changeAsteroidTranslation();
  
  // Verificando colisões
	if(scene == SCENE_GAME) {
		spaceshipCollision = verifySpaceshipCollision();
		bulletColision = verifyBulletCollision();
		
		if(bulletColision) {
			printf("Bala colidiu!\n");

      if(notDivided) {
        divideAsteroid();
      }
		}
		if(spaceshipCollision) {
			printf("Finalização do jogo!\n");

			clearSpaceshipMoves();
			scene = SCENE_GAMEOVER;
		}
	}

  // Movimentando objetos
	if(scene == SCENE_START || scene == SCENE_GAME) {
		
    // Move a bala
		if(bulletExists) {
			bullet.Tx += bullet.xStep;
			bullet.Ty += bullet.yStep;
		}

    // Move a Nave
    spaceship.Tx += spaceship.xStep;
    spaceship.Ty += spaceship.yStep;

    // Move o Asteroid
    if(levelDestructionAsteroid == 0) {
      asteroid.Tx += asteroid.xStep;
      asteroid.Ty += asteroid.yStep;

    } else if(levelDestructionAsteroid == 1) {
      asteroid1.Tx += asteroid1.xStep;
      asteroid1.Ty += asteroid1.yStep;

      asteroid2.Tx += asteroid2.xStep;
      asteroid2.Ty += asteroid2.yStep;
    }
	}
}