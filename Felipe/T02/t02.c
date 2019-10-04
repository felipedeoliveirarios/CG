#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
################################################################################
#	Seção de inclusão e opções do OpenGL
################################################################################
*/

#ifdef _WIN32
    #include "libs/glut.h"
    #include <windows.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#elif __unix__      
    #include <GL/glut.h>
#endif

/*
################################################################################
#	Seção de constantes definidas pelo programador
################################################################################
*/

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DEBUG 1

/*
################################################################################
#	Seção de estruturas de dados
################################################################################
*/
typedef struct vertex2D{
	GLint x;
	GLint y;
} vertex2D;

typedef struct color3i{
	GLint red;
	GLint green;
	GLint blue;
} color3i;

void putPixel(int x, int y, color3i color){
	glBegin(GL_POINTS);
	glColor3ub(color.red, color.green, color.blue);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

/*
Função básica de desenho de retas. Só funciona pra ângulos menores que 45 graus
e caso o vértice inicial tenha x menor que o final.
*/
void drawLine_basic(vertex2D v1, vertex2D v2, color3i color){
	int dx = v2.x - v1.x; // Calcula a distância no eixo X
	int dy = v2.y - v1.y; // Calcula a distância no eixo Y
	int d = 2 * dy - dx; // Calcula o valor inicial da variável de decisão
	int incE = 2 * dy; // Calcula o incremento para a direção E
	int incNE = 2 * (dx - dy); // Calcula o incremento para a direção NE

	int x = v1.x; // Posição inicial x da linha
	int y = v1.y; // Posição inicial y da linha

	glColor3ub(color.red, color.green, color.blue); // Define a cor de desenho.
	glBegin(GL_POINTS); // Inicia o modo de desenho com o OpenGL
	glVertex2i(x, y); // Pinta o pixel inicial

	while (x < v2.x){ // Loop principal. Itera sobre X
		if (d <= 0){ // Análise da variável de decisão
			/* Escolhe E */
			d += incE; // Itera a variável de decisão
			x++; // Percorre a reta em X
		} else {
			/* Escolhe NE */
			d += incNE;	// Itera a variável de decisão.
			x++; // Percorre a reta em X
			y++; // Percorre a reta em Y
		}
		glVertex2i(x, y); // Efetivamente desenha o pixel
	}
	glEnd(); // Finaliza o modo de desenho com o OpenGL
	glFlush(); // Finaliza todas as operações enfileiradas
	
}

/*
Desenha uma linha com inclinação entre 45 e -45 graus. Ou, se preferir, que 
tenha |dx| >= |dy|. Traça a reta iterando sobre X, mas a cada iteração de X 
pode iterar Y para cima ou para baixo. Só funciona quando o vértice inicial tem
a coordenada X menor ou igual à coordenada X do vértice final.
*/
void drawLine_low(int x1, int y1, int x2, int y2, color3i color){
	int dx = x2 - x1; // Calcula a distância no eixo X
	int dy = y2 - y1; // Calcula a distância no eixo Y
	int incY = 1; // Incremento no eixo Y

	if (DEBUG)
		printf("[INFO] DRAWING LINE FROM (%d, %d) to (%d, %d) USING LOW.\n", x1, y1, x2, y2);

	if(dy < 0){ // Caso a reta esteja indo para valores negativos de y...
		incY = -1; // Inverte-se o valor do incremento de Y
		dy = -(dy); // E inverte-se o valor do dy.
	}

	int d = 2 * dy - dx; // Calcula o valor inicial da variável de decisão
	int x; // Posição inicial x da linha
	int y = y1; // Posição inicial y da linha

	// Pré-cálculos. Aceleram a renderização.
	int twodx = 2 * dx; // Variável para recálculo do d
	int twody = 2 * dy; // Variável para recáclulo do d
	
	glColor3ub(color.red, color.green, color.blue);
	glBegin(GL_LINES); // Inicia o modo de desenho com o OpenGL
	for(x = x1; x <= x2; x++){
	/*
	Loop que itera X desde o vértice inicial até o final
	*/ 
		if (DEBUG) printf("[INFO] CALLING glVertex2i(%d, %d).\n", x, y);
		glVertex2i(x, y); // Pinta o pixel atual
		if ((x > WINDOW_WIDTH || x < 0 || y > WINDOW_HEIGHT || y < 0) && DEBUG)
			printf("[WARNING] Drawing pixel off window (%d, %d)\n", x, y);
		if(d > 0) { // Tomada de decisão
			/* 
			Seleciona NE ou SE, de acordo com a inclinação da reta, verificada 
			anteriormente no cálculo do dy. Ou seja, sobe/desce a posição de 
			pintura quando necessário.
			*/
			y += incY; // Itera Y de acordo com a inclinação da reta.
			d -= twodx; // Reduz o valor da variável de decisão com base em dx.
		}
		d += twody; // Aumenta o valor da variável de decisão com base em dy.
	}
	glEnd(); // Finaliza o modo de desenho com o OpenGL
	glFlush(); // Finaliza todas as operações enfileiradas
}

/*
Desenha uma linha com inclinação entre 45 e 90 graus e entre -45 e -90 graus. 
Ou, se preferir, que tenha |dy| >= |dx|. Traça a reta iterando sobre Y, e a 
cada iteração de Y pode iterar o X para frente ou para trás. 
*/
void drawLine_high(int x1, int y1, int x2, int y2, color3i color){
	int dx = x2 - x1; // Calcula a distância no eixo X
	int dy = y2 - y1; // Calcula a distância no eixo Y
	int incX = 1; // Incremento no eixo X

	if (DEBUG)
		printf("[INFO] DRAWING LINE FROM (%d, %d) to (%d, %d) USING HIGH.\n", x1, y1, x2, y2);

	if(dx < 0){ // Caso a reta esteja indo para valores negativos de x...
		incX = -1; // Inverte-se o valor do incremento de X
		dx = -(dx); // E inverte-se o valor do dx.
	}

	int d = 2 * dx - dy; // Calcula o valor inicial da variável de decisão
	int y; // Posição inicial y da linha
	int x = x1; // Posição inicial x da linha

	// Pré-cálculos. Aceleram a renderização.
	int twodx = 2 * dx; // Variável para recálculo do d
	int twody = 2 * dy; // Variável para recáclulo do d

	glColor3ub(color.red, color.green, color.blue);
	glBegin(GL_LINES); // Inicia o modo de desenho com o OpenGL
	for(y = y1; y <= y2; y++){
		/*
		Loop que itera Y à partir do vértice inicial até o vérice final
		*/
		glVertex2i(x, y); // Pinta o pixel atual
		if ((x > WINDOW_WIDTH || x < 0 || y > WINDOW_HEIGHT || y < 0) && DEBUG)
			printf("[WARNING] Drawing pixel off window (%d, %d)\n", x, y);
		if(d > 0) { // Tomada de decisão
			/*
			Seleciona NE ou NO, de acordo com a inclinação da reta, verificada 
			anteriormente no cálculo do dx. Ou seja, move a posição de pintura 
			para a direita ou para a esquerda como for necessário.
			*/
			x += incX; // Itera X de acordo com a inclinação da reta.
			d -= twody; // Reduz o valor da variável de decisão com base em dy.
		}
		d += twodx; // Aumenta o valor da variável de decisão com base em dx.
	}
	glEnd(); // Finaliza o modo de desenho com o OpenGL
	glFlush(); // Finaliza todas as operações enfileiradas
}

/*
Função que desenha uma reta entre dois vértices quaisquer no plano.
*/
void drawLine(vertex2D v1, vertex2D v2, color3i color){
	/*
	Calcula dx e dy para escolher qual função usar e de que forma.
	*/
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;
	if (DEBUG) printf("[INFO] DX = %d; DY = %d.\n", dx, dy);

	if(dx >= dy){ // Decide qual função usar baseado no ângulo da reta.
		/*
		A reta faz ângulo menor ou igual a 45 graus com o eixo X; portanto, a 
		função que itera sobre X pode ser usada sem complicações.
		*/
		if (dx >= 0){ // A reta vai em direção a X positivo.
			/*
			Desenha a reta usando a função para ângulos menores que 45 graus,
			sem complicações.
			*/
			drawLine_low(v1.x, v1.y, v2.x, v2.y, color);
		} else { // A reta vai em direção a X negativo.
			/*
			Inverte a reta, trocando ponto de início com ponto final, garantido
			que a função receba como entrada uma reta que vai de um menor valor
			de X para um maior valor de X.
			*/
			if (DEBUG) printf("[INFO] DX < 0. DRAWING LINE WITH INVERTED VERTEXES.\n");
			drawLine_low(v2.x, v2.y, v1.x, v1.y, color);
		}
	} else {
		/*
		A reta faz ângulo maior que 45 graus com o eixo X. Dito isso, uma 
		função que iterasse sobre X deixaria buracos (pois há mais Y que X para 
		percorrer). Assim, usa-se a função que itera sobre Y.
		*/
		if (dy >= 0){ // A reta vai em direção a Y positivo.
			/*
			Desenha a reta usando a função para ângulos maiores que 45 graus,
			sem complicações.
			*/
			drawLine_high(v1.x, v1.y, v2.x, v2.y, color);
		} else { // A reta vai em direção a Y negativo.
			/*
			Inverte a reta, trocando ponto de início com ponto final, garantido
			que a função receba como entrada uma reta que vai de um menor valor
			de Y para um maior valor de Y.
			*/
			if (DEBUG) printf("[INFO] DY < 0. DRAWING LINE WITH INVERTED VERTEXES.\n");
			drawLine_high(v2.x, v2.y, v1.x, v1.y, color);
		}
	}
}

/*
Função de exibição.
*/
void display(){
	glMatrixMode(GL_MODELVIEW); 
	 glLoadIdentity(); 
	 // Limpa a janela de visualização com a cor de fundo especificada 
	 glClear(GL_COLOR_BUFFER_BIT);
	//Cria os componentes dos eixos.
	vertex2D xAxisLeft = {0, WINDOW_HEIGHT/2};
	vertex2D xAxisRight = {WINDOW_WIDTH, WINDOW_HEIGHT/2};
	vertex2D yAxisTop = {WINDOW_WIDTH/2, 0};
	vertex2D yAxisBottom = {WINDOW_WIDTH/2, WINDOW_HEIGHT};
	color3i xAxisColor = {235, 0, 0};
	color3i yAxisColor = {0, 235, 0};

	vertex2D center = {320, 240}; // Vértice no centro do plano.
	vertex2D o1 = {420, 250};
	vertex2D o2 = {410, 340};
	vertex2D o3 = {310, 340};
	vertex2D o4 = {220, 330};
	vertex2D o5 = {220, 230};
	vertex2D o6 = {230, 140};
	vertex2D o7 = {330, 140};
	vertex2D o8 = {420, 150};
	color3i lineColor = {235, 235, 235};

	// Traça retas à partir do centro até os vértices espalhados pelo plano
	drawLine(center, o1, lineColor);
	drawLine(center, o2, lineColor);
	drawLine(center, o3, lineColor);
	drawLine(center, o4, lineColor);
	drawLine(center, o5, lineColor);
	drawLine(center, o6, lineColor);
	drawLine(center, o7, lineColor);
	drawLine(center, o8, lineColor);

	//Desenha os eixos.
	drawLine(xAxisLeft, xAxisRight, xAxisColor);
	drawLine(yAxisTop, yAxisBottom, yAxisColor);
}

/*
Função de inicialização.
*/
void init() {
	int width = glutGet(GLUT_SCREEN_WIDTH); // Pega a largura da tela
	int height = glutGet(GLUT_SCREEN_HEIGHT); // Pega a altura da tela
	int xpos = 100; // Posição inicial x da janela.
	int ypos = 100; // Posição inicial y da janela.
	if (width != 0 && height != 0){ // As funções retornam 0 caso desconhecido
		// centraliza a janela na tela.
		xpos = (width - WINDOW_WIDTH)/2;
		ypos = (height - WINDOW_HEIGHT)/2;
	}
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition (xpos, ypos);
    glutCreateWindow("Teste de Traçado de Retas");
    glutDisplayFunc(display);
    glClearColor(0,0,0,0); // Define a cor de limpeza da tela.
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); // Estabelece a área de visualização.
    printf("Projection Bounds: (%d, %d, %d, %d).\n", 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glPointSize(1.0f);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
    init();
    glutMainLoop();
}