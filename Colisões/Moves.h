
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

void divideAsteroid(ASTEROIDS_TREE *asteroids) {
  levelDestructionAsteroid++;
  notDivided = false;
  asteroids->left = (ASTEROIDS_TREE *)malloc(sizeof(ASTEROIDS_TREE));
  asteroids->right = (ASTEROIDS_TREE *)malloc(sizeof(ASTEROIDS_TREE));

  asteroids->left->asteroid.angle = asteroids->asteroid.angle + 30;
  asteroids->left->asteroid.Tx = asteroids->asteroid.Tx;
  asteroids->left->asteroid.Ty = asteroids->asteroid.Ty;
  asteroids->left->asteroid.xStep = cos(
    convertDegreesToRadians(asteroids->left->asteroid.angle)
  ) * ASTEROID_VELOCITY;
	asteroids->left->asteroid.yStep = sin(
    convertDegreesToRadians(asteroids->left->asteroid.angle)
  ) * ASTEROID_VELOCITY;

  asteroids->right->asteroid.angle = asteroids->asteroid.angle - 45;
  asteroids->right->asteroid.Tx = asteroids->asteroid.Tx;
  asteroids->right->asteroid.Ty = asteroids->asteroid.Ty;
  asteroids->right->asteroid.xStep = cos(
    convertDegreesToRadians(asteroids->right->asteroid.angle)
  ) * ASTEROID_VELOCITY;
	asteroids->right->asteroid.yStep = sin(
    convertDegreesToRadians(asteroids->right->asteroid.angle)
  ) * ASTEROID_VELOCITY;
}

void draw() {
	
	spaceship = changeSpaceshipTranslation(spaceship);
	asteroids.asteroid = changeAsteroidTranslation(asteroids.asteroid);
  
  // Verificando colisões
	if(scene == SCENE_GAME) {
		spaceshipCollision = verifySpaceshipCollision(
      asteroids.asteroid,
      spaceship
    );
		bulletColision = verifyBulletCollision(
      asteroids.asteroid,
      bullet
    );
		
		if(bulletColision) {
			printf("Bala colidiu!\n");

      if(notDivided) {
        divideAsteroid(&asteroids);
      }
		}
		if(spaceshipCollision) {
			lives--;
			if (lives == 0)
			{
				printf("Finalização do jogo!\n");

				spaceship = clearSpaceshipMoves(spaceship);
				scene = SCENE_GAMEOVER;
			}
			else
			{
				printf("TOMO DANO\n");
				spaceship = clearSpaceshipMoves(spaceship);
			}
			
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
      asteroids.asteroid.Tx += asteroids.asteroid.xStep;
      asteroids.asteroid.Ty += asteroids.asteroid.yStep;

    } else if(levelDestructionAsteroid == 1) {
      asteroids.left->asteroid.Tx += asteroids.left->asteroid.xStep;
      asteroids.left->asteroid.Ty += asteroids.left->asteroid.yStep;

      asteroids.right->asteroid.Tx += asteroids.right->asteroid.xStep;
      asteroids.right->asteroid.Ty += asteroids.right->asteroid.yStep;
    }
	}
}