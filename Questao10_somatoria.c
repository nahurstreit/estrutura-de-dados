#include <stdio.h>
#include <locale.h>

int sum(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + sum(n - 1);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int N;
    
    while (1) {
        printf("Digite o valor de N (ou 0 para sair): ");
        scanf("%d", &N);

        if (N == 0) {
            break;
        }

        printf("A somatória dos números de 1 a %d é %d\n\n", N, sum(N));
    }

    return 0;
}

