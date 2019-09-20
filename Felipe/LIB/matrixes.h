#include <math.h>
#include <stdlib.h>

typedef struct matrix{ 	// Estrutura de dados para armazenar uma matriz.
	int rows; 		// Número de linhas da Matriz.
	int columns;	// Número de colunas da Matriz.
	float* data;	// Array de dados da matriz.
} matrix;

matrix* create(matrix m);
matrix* remove(matrix m);

matrix* matrix_copy(matrix m){
	/*
	Copia uma matriz e retorna o ponteiro para a cópia.
	*/
	matrix* copy = malloc(sizeof(matrix));			// Cria uma nova matriz para receber os dados.
	copy.rows = m.rows;								// Copia o número de linhas.
	copy.columns = m.columns;						// Copia o número de colunas.
	int size = copy.rows * copy.columns;			// Calcula o tamanho da matriz.
	float* data = malloc(sizeof(float) * size);		// Cria um array para guardar os dados.
	
	int i;
	for(i = 0; i < size; i++){
		data[i] = m.data[i];						// Copia os dados.
	}
	return copy;
}

matrix* sum(matrix a, matrix b);
matrix* matrix_multiply(matrix a, matrix b);
matrix* transpose(matrix m);
