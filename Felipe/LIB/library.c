#include <GL/glut.h>
#include <math.h>

typedef struct vertex{	// Estrutura de dados para armazenar um vértice.
	int x;			// Coordenada X do vértice.
	int y;			// Coordenada Y do vértice.
} vertex;

typedef struct edge{	// Estrutura de dados que representa uma aresta.
	int first_vertex_index;		// Primeiro vértice da aresta.
	int second_vertex_index;	// Segundo vértice da aresta.
} edge;

typedef struct polygon{		// Estrutura de dados que representa um polígono.
	matrix vertexes;			// Matriz de vértices do polígono.
	edge* edges_list;			// Array de arestas do polígono.
	vertex pivot;				// Ponto central do polígono.
	matrix translation;			// Matriz de translação.
	matrix rotation;			// Matriz de rotação.
	matrix scaling;				// Matriz de escala.
} polygon;

polygon createPolygon(matrix* vertexes){
	/*
	Cria um polígono à partir de uma matriz de vértices ordenados.
	Cada vértice será ligado ao próximo e o último será ligado ao primeiro.
	*/
	polygon new_polygon;
	new_polygon.vertexes = vertexes;
	edge* edges = malloc(sizeof(edge) * vertexes.rows);
	int i;
	for(i = 0; i < vertexes.rows; i++){
		edges[0].first_vertex_index = i;
		edges[0].second_vertex_index = (i+1)%vertexes.rows;
	}
	return new_polygon;
}
