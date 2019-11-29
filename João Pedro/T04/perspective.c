// GRUPO 3

// JOÃO PEDRO SILVA SOUSA
// CÁSSIO HENRIQUE PEREIRA COELHO
// ANTÔNIO SIDNEI MOREIRA CIRQUEIRA
// THIAGO DA SILVA FAGUNDES
// FELIPE DEO OLIVEIRA RIOS


/*
################################################################################
#   Seção de inclusão e opções do OpenGL
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

#include <stdlib.h>
#include <stdio.h>

/*
################################################################################
#   Seção de constantes definidas pelo programador
################################################################################
*/

#define GL_SILENCE_DEPRECATION
#define WINDOW_WIDTH 640 // Largura da janela
#define WINDOW_HEIGHT 480 // Altura da janela
#define DEBUG 1 // Ativa/Desativa os prints de debug

/*
################################################################################
#   Seção de estruturas de dados
################################################################################
*/
typedef struct vertex2D{
    GLint x;
    GLint y;
} vertex2D;

typedef struct vertex3D{
    GLint x;
    GLint y;
    GLint z;
} vertex3D;

typedef struct color3i{
    GLint r;
    GLint g;
    GLint b;
} color3i;

typedef struct matrix{
    float* data;
    int rows;
    int cols;
} mtx;

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
    
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_POINTS); // Inicia o modo de desenho com o OpenGL
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

    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_POINTS); // Inicia o modo de desenho com o OpenGL
    for(y = y1; y <= y2; y++){
        /*
        Loop que itera Y à partir do vértice inicial até o vérice final
        */
        if (DEBUG) printf("[INFO] CALLING glVertex2i(%d, %d).\n", x, y);
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

    if(abs(dx) >= abs(dy)){ // Decide qual função usar baseado no ângulo da reta.
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

vertex2D vtx3d2d (vertex3D v, GLfloat f) {
    vertex2D ret;
    ret.x = (f/(f + abs(v.z))) * v.x;
    ret.y = (f/(f + abs(v.z))) * v.y;

    return ret;
}

void display(void) {
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    // limpa a janela
    glClear(GL_COLOR_BUFFER_BIT);

    //Cria os componentes dos eixos.
    vertex2D xAxisLeft = {-WINDOW_WIDTH/2, 0};
    vertex2D xAxisRight = {WINDOW_WIDTH/2, 0};
    vertex2D yAxisTop = {0, WINDOW_HEIGHT/2};
    vertex2D yAxisBottom = {0, -WINDOW_HEIGHT/2};
    color3i xAxisColor = {235, 0, 0};
    color3i yAxisColor = {0, 235, 0};

    //Desenha os eixos.
    if (DEBUG) printf("\n[INFO] DRAWING X AXIS.\n");
    drawLine(xAxisLeft, xAxisRight, xAxisColor);
    if (DEBUG) printf("\n[INFO] DRAWING Y AXIS.\n");
    drawLine(yAxisTop, yAxisBottom, yAxisColor);
    
    color3i white = {255,255,255};
    color3i red = {255,0,0};

    // vertices do cubo em 3d
    //                      A0      B1        C2        D3        E4         F5         G6        H7
    vertex3D cube3d[] = {{0,0,0},{200,0,0},{200,200,0},{0,200,0},{0,200,-200},{200,200,-200},{200,0,-200},{0,0,-200}};
    vertex2D cube2d[8]; // vertices do cubo em 2d perspectiva

    // transforma os vertices 3d para 2d em perspectiva
    int i;
    for (i = 0; i < 8; i++) {
        cube2d[i] = vtx3d2d (cube3d[i], 400);
    }

    int edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, // face frontal
                      {3, 4}, {2, 5}, {1, 6}, {0, 7}, // arestas em profundidae (paralelas)
                      {4, 5}, {5, 6}, {6, 7}, {7, 4}}; // face traseira

    for (i = 0; i < 12; i++) {
    // Cria um vértice 2D com as coordenadas x e y dos vértices3D que compõem a aresta.
        vertex2D v1 = {cube2d[ edges[i][0] ].x, cube2d[ edges[i][0] ].y};
        vertex2D v2 = {cube2d[ edges[i][1] ].x, cube2d[ edges[i][1] ].y};
    //     // desenha uma linha entre eles.
        drawLine(v1, v2, white);
        if (DEBUG) printf("Desenhada uma reta de (%d, %d) a (%d, %d).\n", v1.x, v1.y, v2.x, v2.y);
    }

    glFlush();
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
    glutCreateWindow("Desenho de circunferencia");
    glutDisplayFunc(display);
    glClearColor(0,0,0,0); // Define a cor de limpeza da tela.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2); // Estabelece a área de visualização.
    printf("Projection Bounds:  (%d, %d, %d, %d).\n", -WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutMainLoop();
}
