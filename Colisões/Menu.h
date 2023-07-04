
void desenharTexto(float x, float y, const char* texto, bool font_size) {
	glRasterPos2f(x, y);

	for (int i = 0; texto[i] != '\0'; i++) {
		if(font_size) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[i]);
		}
	}
}


void DesenhaTelaInicial(){
	desenharTexto(-5, 0, "Asteroids", true);
	desenharTexto(-10, -5, "Click space to start", false);
}
