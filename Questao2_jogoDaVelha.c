#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define TABLE_WITDH 9


//2 – Faça um jogo da velha

void printTable();

void printDivisor();

void printLine(char line[3]);
void printPartLine(char line[3]);
void printPartEmptyLine();

void printCell(char c);
void printEmptyCell();

bool checkWinner();
void play();

int scanMove(char c);

char table[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

bool makeMove(char userChar);

int positions[3][3] = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3}
};

bool validateMove(int row, int col);

int main() {
	setlocale(LC_ALL, "Portuguese");
	play();
	return 0;
}

void play() {
    char currentPlayer = 'X';
    bool gameEnded = false;

    while(!gameEnded) {
    	system("cls");
        printTable();
        if(makeMove(currentPlayer)) {
            if(checkWinner()) {
            	system("cls");
            	printTable();
                printf("O Jogador %c ganhou!!\n", currentPlayer);
                gameEnded = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            printf("Movimento inválido. Tente novamente.\n");
            system("pause");
        }
    }
}

bool checkWinner() {
	int i;
    for(i = 0; i < 3; i++) {
        if(table[i][0] != ' ' && table[i][0] == table[i][1] && table[i][1] == table[i][2]) {
            return true;
        }
    }

    for(i = 0; i < 3; i++) {
        if(table[0][i] != ' ' && table[0][i] == table[1][i] && table[1][i] == table[2][i]) {
            return true;
        }
    }

    if(table[0][0] != ' ' && table[0][0] == table[1][1] && table[1][1] == table[2][2]) return true;
    
    if(table[0][2] != ' ' && table[0][2] == table[1][1] && table[1][1] == table[2][0]) return true;

    return false;
}

int scanMove(char c) {
	int move;
	printf("É a vez do jogador %c. Faça seu movimento: ", c);
	scanf("%d", &move);
	return move;
}

bool makeMove(char userChar) {
	int move = scanMove(userChar);
	int row, col;
	bool found = false;
	
	for(row = 0; row < 3; row++) {
		for(col = 0; col < 3; col++) {
			if(move == positions[row][col]) {
				found = true;
				break;
			};
		}
		if(found) break;
	}
	
	
	if(validateMove(row, col)) {
		table[row][col] = userChar;
		return true;
	}
	return false;
}

bool validateMove(int row, int col) {
	if(table[row][col] == ' ') return true;
	return false;
}

void printTable() {
	int i;
	
	printDivisor();
	for(i = 0; i < 3; i++) {
		printLine(table[i]);
		printDivisor();
	}
}

void printLine(char line[3]) {
	printPartEmptyLine();
	printPartLine(line);
	printPartEmptyLine();
}

void printPartLine(char line[3]) {
	int i, j;
	printf("|");
	for(i = 0; i < 3; i++) {
		printCell(line[i]);
	}
	printf("\n");
}

void printPartEmptyLine() {
	int i;
	printf("|");
	for(i = 0; i < 3; i++) {
		printEmptyCell();
	}
	printf("\n");
}

void printCell(char c) {
	printf(" %*c", TABLE_WITDH/2, c);
	printf(" %*c", TABLE_WITDH/2, '|');
}

void printEmptyCell() {
	printCell(' ');
}

void printDivisor() {
	int i, j;
	for(i = 0; i < 3; i++) {
		printf("+");
	    for(j = 0; j < TABLE_WITDH; j++) {
	        printf("-");
	    }
	}
	printf("+\n");
}
