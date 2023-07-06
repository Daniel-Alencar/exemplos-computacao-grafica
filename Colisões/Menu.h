
void drawText(const char* text, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
}

void DrawInitialScreen(const char *string){
	const char* text = string;

	// Obtém as dimensões da janela
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	// Define o tamanho do texto
	float textSizeX = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text);
	// Calcula as coordenadas para centralizar o texto
	float textPosScreenX = windowWidth / 2 - textSizeX / 2;
	float textPosX = ((textPosScreenX) * 2 * range) / (windowWidth);

	// printf("windowWidth: %d\n", windowWidth);
	// printf("textSizeX: %f\n", textSizeX);
	// printf("Posição X: %f\n", textPosX);

	// Desenha o texto centralizado
	glColor3f(redValue, greenValue, blueValue);
	drawText(text,-range+textPosX + 1.5, -5);
}
