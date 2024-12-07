#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


/**6 – Fazer um programa em Linguagem C que criem uma estrutura de dados voo(struct voo) para a empresa VOEBEM, que servirá para implementar funções para controle da lista
dos voos. A estrutura voo deve ser implementada de forma dinâmica e deve conter os seguintes dados:
 - número do voo - inteiro;
 - data do voo - inteiro: (1 - seg, 2 - ter, 3 - qua, 4- qui, 5 - sex, 6 - sab, 7 - dom, 8 - diario);
 - horário do voo - hora inteiro, min inteiro;
 - aeroporto de Saída - inteiro - id do aeroporto;
 - aeroporto de Chegada - inteiro - id do aeroporto;
 - rota - inteiro id;
 - tempo estimado de voo - float;
 - passageiros a bordo - inteiro;
*/

typedef struct Flight {
    int flightNumber;
    int flightDate;
    int hour;
    int minute;
    int departureAirport;
    int arrivalAirport;
    int routeId;
    float estimatedTime;
    int passengers;
    struct Flight *next;
} Flight;


void showTitle(const char *title, const char *message) {
    printf("\n########## %s ##########\n\n", title);
    if (message != NULL && strlen(message) > 0) {
        int messageLength = strlen(message);
        int totalLength = messageLength + 6;
        int i;

        char cleanedMessage[messageLength + 1];
        int cleanedLength = 0;
        
        for (i = 0; i < messageLength; i++) {
            if (message[i] != '\n' && message[i] != '\0') {
                cleanedMessage[cleanedLength++] = message[i];
            }
        }
        cleanedMessage[cleanedLength] = '\0';

        messageLength = cleanedLength;
        totalLength = messageLength + 6;

        for (i = 0; i < totalLength; i++) {
            printf("*");
        }
        printf("\n");

        int padding = (totalLength - 6 - messageLength) / 2;
        printf("||%*s%s%*s||\n", padding, " ", cleanedMessage, padding, " ");

        for (i = 0; i < totalLength; i++) {
            printf("*");
        }
        printf("\n\n");
    }
}




int isNumber(const char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; //Não é um número
        }
    }
    return 1; //É um número
}

Flight *createFlight(int flightNumber, int flightDate, int hour, int minute, int departureAirport, int arrivalAirport, int routeId, float estimatedTime, int passengers) {
    Flight *newFlight = (Flight *)malloc(sizeof(Flight));
    if (newFlight == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    (*newFlight).flightNumber = flightNumber;
    (*newFlight).flightDate = flightDate;
    (*newFlight).hour = hour;
    (*newFlight).minute = minute;
    (*newFlight).departureAirport = departureAirport;
    (*newFlight).arrivalAirport = arrivalAirport;
    (*newFlight).routeId = routeId;
    (*newFlight).estimatedTime = estimatedTime;
    (*newFlight).passengers = passengers;
    (*newFlight).next = NULL;
    return newFlight;
}

Flight *findFlight(Flight *head, int flightNumber) {
    while (head != NULL) {
        if ((*head).flightNumber == flightNumber) {
        	return head;
		}
        head = (*head).next;
    }
    return NULL;
}

const char* getDayOfWeek(int day) {
    switch (day) {
        case 1: return "Segunda-feira";
        case 2: return "Terça-feira";
        case 3: return "Quarta-feira";
        case 4: return "Quinta-feira";
        case 5: return "Sexta-feira";
        case 6: return "Sábado";
        case 7: return "Domingo";
        case 8: return "Todos os dias";
        default: return "Data inválida";
    }
}

void printFlight(Flight *flight) {
	printf("\n=====================================\n");
    printf("           DETALHES DO VOO          \n");
    printf("=====================================\n");
	
    printf("Número do Voo: %d\n", (*flight).flightNumber);
    printf("Data do Voo: %d - %s\n", (*flight).flightDate, getDayOfWeek((*flight).flightDate));
    printf("Horário: %02d:%02d\n", (*flight).hour, (*flight).minute);
    printf("Aeroporto de Saída: %d\n", (*flight).departureAirport);
    printf("Aeroporto de Chegada: %d\n", (*flight).arrivalAirport);
    printf("Rota: %d\n", (*flight).routeId);
    printf("Tempo Estimado: %.2f horas\n", (*flight).estimatedTime);
    printf("Passageiros a Bordo: %d\n", (*flight).passengers);
    printf("=====================================\n");
}


//7 - Implementar a função cadastrarVoo() que deve permitir o cadastro de um novo voo;
void cadastrarVoo(Flight **flights) {
	int flightNumber, flightDate, hour, minute, departureAirport, arrivalAirport, routeId, passengers;
    float estimatedTime;
    showTitle("CADASTRO DE VOO", NULL);
    printf("Número do Voo: ");
    scanf("%d", &flightNumber);
    
    //Verificar se o voo já existe
    Flight *existingFlight = findFlight(*flights, flightNumber);
    if (existingFlight != NULL) {
        char choice;
        printf("Voo com o número %d já cadastrado.\n", flightNumber);
        printf("Deseja alterar os dados deste voo? (S/N): ");
        scanf(" %c", &choice);

        if (choice == 'S' || choice == 's') {
            printf("Alterando os dados do voo...\n");
            printf("Data do Voo (1 a 8): ");
            scanf("%d", &flightDate);
            printf("Hora e Minuto do Voo: ");
            scanf("%d %d", &hour, &minute);
            printf("ID do Aeroporto de Saída: ");
            scanf("%d", &departureAirport);
            printf("ID do Aeroporto de Chegada: ");
            scanf("%d", &arrivalAirport);
            printf("ID da Rota: ");
            scanf("%d", &routeId);
            printf("Tempo Estimado (em horas): ");
            scanf("%f", &estimatedTime);
            printf("Número de Passageiros: ");
            scanf("%d", &passengers);

            (*existingFlight).flightDate = flightDate;
            (*existingFlight).hour = hour;
            (*existingFlight).minute = minute;
            (*existingFlight).departureAirport = departureAirport;
            (*existingFlight).arrivalAirport = arrivalAirport;
            (*existingFlight).routeId = routeId;
            (*existingFlight).estimatedTime = estimatedTime;
            (*existingFlight).passengers = passengers;
            printf("\nDados do voo alterados com sucesso!");
        } else {
            printf("Operação cancelada.\n");
        }
        return;
    }
    
    
    printf("Data do Voo (1 a 8): ");
    scanf("%d", &flightDate);
    printf("Hora e Minuto do Voo: ");
    scanf("%d %d", &hour, &minute);
    printf("ID do Aeroporto de Saída: ");
    scanf("%d", &departureAirport);
    printf("ID do Aeroporto de Chegada: ");
    scanf("%d", &arrivalAirport);
    printf("ID da Rota: ");
    scanf("%d", &routeId);
    printf("Tempo Estimado (em horas): ");
    scanf("%f", &estimatedTime);
    printf("Número de Passageiros: ");
    scanf("%d", &passengers);
    Flight *newFlight = createFlight(flightNumber, flightDate, hour, minute, departureAirport, arrivalAirport, routeId, estimatedTime, passengers);
    (*newFlight).next = *flights;
    *flights = newFlight;
    printf("\nVoo cadastrado com sucesso!");
}


//8 - Implementar a função consultaVoo() que deve permitir obter as informações do voo com base na digitação do número do voo;
void consultaVoo(Flight *flights) {
    int flightNumber;
    char message[30] = "";
    int consultedBefore = 0;

    do {
        system("cls");
        showTitle("CONSULTA DE VOO", message);

        if (!consultedBefore) {
            printf("Digite o número do Voo (ou 0 para voltar ao menu): ");
            scanf("%d", &flightNumber);
        }

        if (flightNumber == 0) {
            printf("Voltando ao menu principal...\n");
            break;
        }

        Flight *flight = findFlight(flights, flightNumber);
        if (flight == NULL) {
            strcpy(message, "Voo não encontrado");
            printf("%s\n", message);
            consultedBefore = 0;
        } else {
            printFlight(flight);
            consultedBefore = 1;
        }

        printf("\nDeseja consultar outro voo? (Digite o número do voo ou 0 para voltar ao menu)\n");
        if (consultedBefore) {
            scanf("%d", &flightNumber);
            if(flightNumber == 0);
            printf("Voltando ao menu principal...\n");
        }
    } while (flightNumber != 0);
}

//9 - Implementar a função removeVoo() que permita a exclusão de um determinado voo.
void removeVoo(Flight **flights) {
	showTitle("REMOVER VOO", NULL);
    int flightNumber;
    printf("Digite o número do Voo: ");
    scanf("%d", &flightNumber);
    
	Flight *current = *flights;
    Flight *previous = NULL;
    while (current != NULL && (*current).flightNumber != flightNumber) {
        previous = current;
        current = (*current).next;
    }
    if (current == NULL) {
        printf("Voo não encontrado\n");
        return;
    }
    
    if (previous == NULL) {
    	*flights = (*current).next;
	} else {
		(*previous).next = (*current).next;
	}
        
    free(current);
    printf("Voo removido com sucesso\n");
}



int main() {
	setlocale(LC_ALL, "Portuguese");
    Flight *flights = NULL;
    int option;
    
    do {
    	system("cls");
		printf("\033[1;32m__     _____  _____   ____  _____ __  __\033[0m\n");
		printf("\033[1;32m\\ \\   / / _ \\| ____| | __ )| ____|  \\/  |\033[0m\n");
		printf("\033[1;32m \\ \\ / / | | |  _|   |  _ \\|  _| | |\\/| |\033[0m\n");
		printf("\033[1;32m  \\ V /| |_| | |___  | |_) | |___| |  | |\033[0m\n");
		printf("\033[1;32m   \\_/  \\___/|_____| |____/|_____|_|  |_|\033[0m\n");
        printf("\n[1] - Cadastrar Voo");
        printf("\n[2] - Consultar Voo");
        printf("\n[3] - Remover Voo");
        printf("\n[0] - Sair");
        printf("\n\nEscolha uma opção: ");
        scanf("%d", &option);
        system("cls");
        switch(option) {
        	case 1:
        		cadastrarVoo(&flights);
        		break;
        	case 2:
        		consultaVoo(flights);
        		break;
        	case 3:
        		removeVoo(&flights);
        		break;
        	default: 
        		printf("Opção inválida, digite novamente!");
        	break;
		}
		
		printf("\n\n");
		system("pause");
    } while (option != 0);
    return 0;
}

