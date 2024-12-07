#include <stdio.h>

//1 - Suponha uma matriz de 3 linhas por 3 colunas do tipo inteiro.
//Leia os valores dessa matriz, depois informe qual é o maior e o menor elemento.


void printMatrix(int rows, int cols, int matrix[rows][cols]);
void scanMatrix(int rows, int cols, int matrix[rows][cols]);
int getMinor(int rows, int cols, int matrix[rows][cols]);
int getMajor(int rows, int cols, int matrix[rows][cols]);

void printBorder(int width, int repeat);

int main() {
	int rows = 3, cols = 3;
	int matrix[rows][cols];
	
	scanMatrix(rows, cols, matrix);
	
	printf("\nMatriz criada: \n");
	printMatrix(rows, cols, matrix);
	
	printf("\nMenor Valor: %d", getMinor(rows, cols, matrix));
	printf("\nMaior Valor: %d", getMajor(rows, cols, matrix));
	
	return 0;
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
	int i, j;
	printBorder(12, cols);
	for(i = 0; i < rows; i++) {
		printf("%c", '|');
		for(j = 0; j < cols; j++) {
			printf("%-12d|", matrix[i][j]);
		}
		printf("\n");  
		printBorder(12, cols);
	}
}

void printBorder(int width, int repeat) {
	int i, j;
	for(i = 0; i < repeat; i++) {
		printf("+");
		for(j = 0; j < width; j++) {
			printf("-");
		}
	}
	printf("+\n");

}

void scanMatrix(int rows, int cols, int matrix[rows][cols]) {
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			printf("Digite o valor em: [%d][%d]: ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
}

int getMinor(int rows, int cols, int matrix[rows][cols]) {
	int minor = matrix[0][0];
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if(matrix[i][j] < minor) {
				minor = matrix[i][j];
			}
		}
	}
	return minor;
}

int getMajor(int rows, int cols, int matrix[rows][cols]) {
	int major = matrix[0][0];
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if(matrix[i][j] > major) major = matrix[i][j];
		}
	}
	return major;
}
