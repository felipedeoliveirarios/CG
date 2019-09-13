#include <GL/glut.h>
#include <math.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int vertexCount;
int** vx, vy;

void draw(int vertexCount, int** vx, int** vy){
	int i;
	glMatrixMode(GL_MODELVIEW); // Altera o alvo das matrizes de transformação do OpenGL. A constante usada como argumento define o alvo como "apenas o que está sendo desenhado".
	glLoadIdentity(); // Carrega a matriz identidade como a matriz de transformação atual. (limpa a matriz usada anteriormente)
	glClear(GL_COLOR_BUFFER_BIT); // Limpa um buffer. No caso, o buffer das cores da imagem (ou seja, remove a imagem atual da memória e janela).
	glColor3i(235, 235, 235); // Define a cor atual como um tom de cinza claro.
	glBegin(GL_TRIANGLE_STRIP); // Inicia o modo de desenho. No caso, triângulos. A cada três vértices definidos, será desenhado um triângulo na tela, com interseção de 2 vértices.
		for(i = 0; i < vertexCount; i++)
			glVertex2i(vx[i], vy[i]); // Define um vértice dadas as coordenadas x e y.
	glEnd(); // Finaliza o modo de desenho.
	glFlush(); // Executa tudo o que estiver enfileirado no OpenGL.
}

void init(int* vertexCount, int** vx, int** vy){
	int i = 0;
	*vertexCount = rand()%20 + 3;
	vx = malloc(sizeof(int) * *vertexCount);
	vy = malloc(sizeof(int) * *vertexCount);
	for(i = 0; i < vertexCount; i++){
		vx[i] = malloc(sizeof(int));
		vy[i] = malloc(sizeof(int));
		vx[i] = rand()%SCREEN_WIDTH;
		vy[i] = rand()%SCREEN_HEIGHT;
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor usada para limpar a tela. No caso, preto.
}

void windowResize(GLsizei width, GLsizei height){
	if (height == 0) height = 1;
	glViewport(0, 0, width, height); // Define a caixa que corresponde à área dentro da janela que pode ser usada para desenhar.
	glMatrixMode(GL_PROJECTION); // Define o alvo das matrizes de transformação como a câmera.
	glLoadIdentity(); // Define a identidade como a matriz atual de transformação.
	if (width >= height)	{
		gluOrtho2D (0.0f, 640.0f, 0.0f, 480.0f*height/width);
	} else {
		gluOrtho2D (0.0f, 640.0f*width/height, 0.0f, 480.0f);
	}
}

void main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT); 
	glutInitWindowPosition(10,10); 
	glutCreateWindow("Triângulos"); 
	glutDisplayFunc(draw); 
	glutReshapeFunc(windowResize); 
	init(&vertexCount, vx, vy); 
	glutMainLoop(); 
}

