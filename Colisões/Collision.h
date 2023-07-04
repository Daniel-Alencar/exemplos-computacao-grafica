
int orientation(Point p, Point q, Point r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) {
		// Os pontos são colineares
		return 0;
	} else if (val > 0) {
		// Sentido horário
		return 1;
	} else {
		// Sentido anti-horário
		return 2;
	}
}

int onSegment(Point p, Point q, Point r) {
	if (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
			q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y)) {
		// q está no segmento pr
		return 1;
	}
	return 0;
}

int doIntersect(Point p1, Point q1, Point p2, Point q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// Caso geral
	if (o1 != o2 && o3 != o4) {
		// As linhas se intersectam
		return 1;
	}

	// Casos especiais
	if (o1 == 0 && onSegment(p1, p2, q1)) {
		// p2 está em p1q1
		return 1;
	}
	if (o2 == 0 && onSegment(p1, q2, q1)) {
		// q2 está em p1q1
		return 1;
	}
	if (o3 == 0 && onSegment(p2, p1, q2)) {
		// p1 está em p2q2
		return 1;
	}
	if (o4 == 0 && onSegment(p2, q1, q2)) {
		// q1 está em p2q2
		return 1;
	}

	// As linhas não se intersectam
	return 0;
}

bool detectColision(GLfloat x1, GLfloat y1, GLfloat r1,
										 GLfloat x2,GLfloat y2,GLfloat r2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float distance = std::sqrt(dx*dx + dy*dy);

	if (distance > r1 + r2) {
		// Circulos são disjuntos
		return false;
	}

	if (distance < std::abs(r1 - r2)) {
		// Um círculo está contido dentro de outro
		return false;
	}

	if (distance == 0 && r1 == r2) {
		// Os círculos são idênticos
		return true;
	}

	// Os círculos se intersectam
	return true;
}

bool verifyIntersects() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 10; j++) {
			Point nave_point1 = { 
				pointsNave[i].x + Tx, pointsNave[i].y + Ty 
			};
			Point nave_point2 = { 
				pointsNave[(i+1)%3].x + Tx, pointsNave[(i+1)%3].y + Ty 
			};
			Point asteroid_point1 = { 
				pointsAsteroid[j].x + Tx_Asteroid, pointsAsteroid[j].y + Ty_Asteroid 
			};
			Point asteroid_point2 = { 
				pointsAsteroid[(j+1)%10].x + Tx_Asteroid, 
				pointsAsteroid[(j+1)%10].y + Ty_Asteroid 
			};

			if(doIntersect(
				nave_point1, nave_point2,
				asteroid_point1, asteroid_point2
			)) {
				return true;
			}
		}
	}
	return false;
}

bool verifyBullet() {
  for(int j = 0; j < 10; j++) {
    Point asteroid_point1 = { 
      pointsAsteroid[j].x + Tx_Asteroid, pointsAsteroid[j].y + Ty_Asteroid 
    };
    Point asteroid_point2 = { 
      pointsAsteroid[(j+1)%10].x + Tx_Asteroid, 
      pointsAsteroid[(j+1)%10].y + Ty_Asteroid 
    };

    Point bulletPoint1 = {Tx_bullet, Ty_bullet};
    Point bulletPoint2 = {Tx_bullet * 1.1f, Ty_bullet * 1.1f};

    if(doIntersect(
      bulletPoint1, bulletPoint2,
      asteroid_point1, asteroid_point2
    )) {
      return true;
    }
  }
  return false;
}