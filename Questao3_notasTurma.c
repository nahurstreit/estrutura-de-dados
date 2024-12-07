#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define QTY_STUDENTS 5
#define QTY_TESTS 4
#define MAX_NAME_SIZE 50

//3 – Notas da turma - Fazer um programa para ler as notas de 4 provas para 5 alunos de uma turma e calcular a média do aluno e média da turma

float calculateStudentAvg(float student[QTY_TESTS]);
float calculateClassAvg(float students[QTY_STUDENTS][QTY_TESTS]);

void scanAllGrades(float studentsArr[QTY_STUDENTS][QTY_TESTS]);
void scanSpecificGrade(float student[QTY_TESTS]);
int scanMenuOpt();

void showScreen(void (*screen)());
void showStudents(char students[QTY_STUDENTS][MAX_NAME_SIZE]);
void showSpecificStudent(int id, char student[MAX_NAME_SIZE]);
void showStudentOption();

void menuScreen();
void addGradesScreen();
void avgScreen(float students[QTY_STUDENTS][QTY_TESTS]);

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float studentsGrade[QTY_STUDENTS][QTY_TESTS];
	
	int nav = 6;
	do {
		showScreen(menuScreen);
		nav = scanMenuOpt();
		switch(nav) {
			case 1:
				showScreen(addGradesScreen);
				scanAllGrades(studentsGrade);
				break;
			case 2:
				showScreen(NULL);
				avgScreen(studentsGrade);
				system("pause");
				break;
			case 0:
				break;
			default:
			;
		}
	} while(nav != 0);
	
	return 0;
}

void showScreen(void (*screen)()) {
	system("cls");
	if(screen != NULL) {
		screen();	
	}
}

void menuScreen() {
	printf("########## MENU ##########");
	printf("\n[1] - Adicionar notas de todos os alunos");
	printf("\n[2] - Calcular médias");
	printf("\n[0] - Sair\n\n");
}

void addGradesScreen() {
	printf("########## NOTAS ##########\n\n");
}

void avgScreen(float students[QTY_STUDENTS][QTY_TESTS]) {
	int i;
	printf("########## MÉDIAS ##########\n\n");
	for(i = 0; i < QTY_STUDENTS; i++) {
		printf("%dº aluno: %.2f\n", i+1, calculateStudentAvg(students[i]));
	}
	
	printf("\n\nMédia da classe: %.2f\n\n", calculateClassAvg(students));
}

void scanAllGrades(float studentsArr[QTY_STUDENTS][QTY_TESTS]) {
	int i, j;
	for(i = 0; i < QTY_STUDENTS; i++) {
		printf("%dº aluno: \n", i+1);
		scanSpecificGrade(studentsArr[i]);
		printf("\n");
	}
}

int scanMenuOpt() {
	int opt;
	printf("Opção: ");
	scanf("%d", &opt);
	return opt;
}

void scanSpecificGrade(float student[QTY_TESTS]) {
	int i;
	for(i = 0; i < QTY_TESTS; i++) {
		printf("\t%dª nota: ", i+1);
		scanf("%f", &student[i]);
	}
}

float calculateStudentAvg(float student[QTY_TESTS]) {
	int i;
	float total = 0;
	
	for(i = 0; i < QTY_TESTS; i++) {
		total += student[i];	
	}
	
	return total / QTY_TESTS;
}

float calculateClassAvg(float students[QTY_STUDENTS][QTY_TESTS]) {
	int i;
	float total = 0;
	
	for(i = 0; i < QTY_STUDENTS; i++) {
		total += calculateStudentAvg(students[i]);
	}
	
	return total / QTY_STUDENTS;
}
