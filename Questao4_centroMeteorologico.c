#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define QTY_CITIES 7
#define QTY_MONTHS 6
#define MAX_NAME_SIZE 50
#define TABLE_STD_WITDH 12


//4 – Centro meterológico - Um centro meteorológico distribuiu dispositivos para registrar índices pluviométricos em um conjunto de 7 cidades
//de uma região (identificadas por códigos numéricos de 1 a 7) durante 6 meses(Jan a Jun), onde, para cada mês foi registrado um valor real 
//que corresponde ao índice pluviométrico total do mês.

char monthNames[QTY_MONTHS][MAX_NAME_SIZE] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho"};
int currentAvaiableSpace = 0;

void menuScreen();
void cityMenu();
void showScreen(void (*screen)());
void showMessageAndPause(char message[50]);
void showCities(char names[QTY_CITIES][MAX_NAME_SIZE]);
void showCity(int index, float pluviometric[QTY_MONTHS], char name[MAX_NAME_SIZE]);
void showPluviometric(float pluviometric[QTY_MONTHS]);
void printHorizontalLine(int length, int repeat);

void avgScreen(float students[QTY_CITIES][QTY_MONTHS]);

void scanCity(float pluviometric[QTY_MONTHS], char name[MAX_NAME_SIZE]);
void scanCities(float pluviometrics[QTY_CITIES][QTY_MONTHS], char names[QTY_CITIES][MAX_NAME_SIZE]);
void scanSpecificCityPluviometric(float city[QTY_MONTHS]);

int scanOpt();

float calculateAvgPluviometric(float pluviometric[QTY_MONTHS]);

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float citiesPluviometrics[QTY_CITIES][QTY_MONTHS];
	char citiesNames[QTY_CITIES][MAX_NAME_SIZE];
	
	int nav = 6;
	
	char repeat;
	
	int cityChoice = 0;
	bool showMessage = false;
	char message[14] = "ID inválido.";
	
	int cityInteractionChoice = 0;
	int monthChoice;
	float holderNewPluviometric = 0.0;
	
	do {
		showScreen(menuScreen);
		nav = scanOpt();
		switch(nav) {
			case 1:
				system("cls");
				printf("##### CADASTRAMENTO DE CIDADES #####\n\n");
				scanCity(citiesPluviometrics[currentAvaiableSpace], citiesNames[currentAvaiableSpace]);
				break;
			case 2:
				do {
					showScreen(NULL);
					if(showMessage) printf("%s\n", message);
					showCities(citiesNames);
					printf("\n\nDigite o id para mais detalhes de uma cidade ou [0] para voltar. ");
					cityChoice = scanOpt();
					if(cityChoice > QTY_CITIES || cityChoice < 0 || cityChoice - 1 >= currentAvaiableSpace) {
						showMessage = true;
						continue;
					}
					else if(cityChoice != 0) {
						do {
							system("cls");
							showCity(cityChoice, citiesPluviometrics[cityChoice-1], citiesNames[cityChoice-1]);
							cityMenu();
							cityInteractionChoice = scanOpt();
							switch(cityInteractionChoice) {
								case 1:
									printf("\nDigite o novo nome:");
									scanf("%s", citiesNames[cityChoice-1]);
									showMessageAndPause("Nome alterado!\n");
									break;
								case 2:
									printf("\nDigite número do mês que você quer alterar (apenas números) ");
									monthChoice = scanOpt();
									if(monthChoice > 6 || monthChoice < 0) {
										printf("Mês inválido.\n");
									} else {
										printf("Digite o novo índice para o mês de %s: ", monthNames[monthChoice-1]);
										scanf("%f", &holderNewPluviometric);
										citiesPluviometrics[cityChoice-1][monthChoice-1] = holderNewPluviometric;
										printf("Mês alterado!\n");
									}
									showMessageAndPause("");
									break;
							}
							
						} while(cityInteractionChoice != 0);
					}
					showMessage = false;
				} while(cityChoice != 0);

				break;
			case 0:
				break;
			default:
			;
		}
	} while(nav != 0);
	
	return 0;
}

void showMessageAndPause(char message[50]) {
	printf("%s", message);
	system("pause");
}

void showScreen(void (*screen)()) {
	system("cls");
	if(screen != NULL) {
		screen();	
	}
}

void menuScreen() {
	printf("########## MENU ##########");
	printf("\n[1] - Cadastrar cidade");
	printf("\n[2] - Ver cidades");
	printf("\n[0] - Sair\n\n");
}

void cityMenu() {
	printf("\n[1] - Alterar Nome");
	printf("\n[2] - Alterar Mês");
	printf("\n[0] - Voltar\n\n");
}

void scanCity(float pluviometric[QTY_MONTHS], char name[MAX_NAME_SIZE]) {
	printf("Nome da cidade: ");
	scanf("%s", name);
	scanSpecificCityPluviometric(pluviometric);
	showMessageAndPause("\nDados registrados!\n");
	currentAvaiableSpace++;
}

int scanOpt() {
	int opt;
	printf("Opção: ");
	scanf("%d", &opt);
	return opt;
}

void scanSpecificCityPluviometric(float city[QTY_MONTHS]) {
	int i;
	printf("\nÍndice pluviométrico mensal:\n");
	for(i = 0; i < QTY_MONTHS; i++) {
		printf("%s: ", monthNames[i]);
		scanf("%f", &city[i]);
	}
}

void showCities(char names[QTY_CITIES][MAX_NAME_SIZE]) {
	if(currentAvaiableSpace <= 0) {
		printf("Ainda não existem registros de cidade.");
	} else {
		int width = 15;
		printHorizontalLine(width, 2);
		
		int i;
		for(i = 0; i < currentAvaiableSpace; i++) {
			printf("|%-*d|%-*s|\n", width, i+1, width, names[i]);
		}
		
		printHorizontalLine(width, 2);
	}

}

void showCity(int index, float pluviometric[QTY_MONTHS], char name[MAX_NAME_SIZE]) {	
    printf("(%d) Cidade: %s\n", index, name);
    int i;
    printf("\níndices pluviométricos mensais: \n");
    showPluviometric(pluviometric);
    printf("%*s%.2f\n", TABLE_STD_WITDH*QTY_MONTHS, "Média: ", calculateAvgPluviometric(pluviometric));
}

void showPluviometric(float pluviometric[QTY_MONTHS]) {
	int i;
	int width = TABLE_STD_WITDH;
	
	printHorizontalLine(width, QTY_MONTHS);
    printf("|");
    for(i = 0; i < QTY_MONTHS; i++) {
        printf("%-*s|", width, monthNames[i]);
    }
    
    printf("\n|");
    for(i = 0; i < QTY_MONTHS; i++) {
        printf("%-*.2f|", width, pluviometric[i]);
    }
  	printf("\n");
    printHorizontalLine(width, QTY_MONTHS);
}

float calculateAvgPluviometric(float pluviometric[QTY_MONTHS]) {
	int i;
	float total = 0.0;
	for(i = 0; i < QTY_MONTHS; i++) {
		total += pluviometric[i];
	}
	return total / QTY_MONTHS;
}

void printHorizontalLine(int length, int repeat) {
	int i, j;
	for(i = 0; i < repeat; i++) {
		printf("+");
	    for(j = 0; j < length; j++) {
	        printf("-");
	    }
	}
	printf("+\n");
}

float calculatetAvg(float city[QTY_MONTHS]) {
	int i;
	float total = 0;
	
	for(i = 0; i < QTY_MONTHS; i++) {
		total += city[i];	
	}
	
	return total / QTY_MONTHS;
}
