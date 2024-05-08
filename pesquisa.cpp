#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int gostou;
    char proxima[4];
} Pesquisa;

void realizarPesquisa(Pesquisa* resposta) {
    FILE* arquivo;
    fopen_s(&arquivo, "pesquisa.csv", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pesquisa.\n");
        return;
    }

    int validInput;
    do {
        printf("De 1 a 10, quanto gostou da exposicao?\n ");
        validInput = scanf_s("%d", &(resposta->gostou));
        if (validInput != 1 || resposta->gostou < 1 || resposta->gostou > 10) {
            printf("Valor fora do intervalo permitido (1 a 10). Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    } while (validInput != 1 || resposta->gostou < 1 || resposta->gostou > 10);

    char proximaExposicao[4] = { 0 }; // Inicializa o array com zeros
    int validaProxima = 0;

    do {
        printf("A proxima exposicao eh daqui a 5 dias, podera comparecer? (sim ou nao):\n ");
        if (scanf_s("%3s", proximaExposicao, sizeof(proximaExposicao)) != 1) {
            printf("Resposta invalida. Digite 'sim' ou 'nao'.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        // Converter para minúsculas
        for (int i = 0; proximaExposicao[i]; i++) {
            proximaExposicao[i] = tolower(proximaExposicao[i]);
        }

        if (strcmp(proximaExposicao, "sim") == 0) {
            strcpy_s(resposta->proxima, sizeof(resposta->proxima), "sim");
            validaProxima = 1;
        }
        else if (strcmp(proximaExposicao, "nao") == 0) {
            strcpy_s(resposta->proxima, sizeof(resposta->proxima), "nao");
            validaProxima = 1;
        }
        else {
            printf("Resposta invalida. Digite 'sim' ou 'nao'.\n");
        }
    } while (!validaProxima);

    fprintf(arquivo, "%d,%s\n", resposta->gostou, resposta->proxima);
    fclose(arquivo);
    printf("Pesquisa registrada com sucesso.\n");
}

int main() {
    Pesquisa resposta;
    int escolha;
    int validInput;

    printf(" *");
    printf("\n _Bem-vindo a pesquisa de satisfacao!_ \n");
    printf(" \n");
    printf(" *");

    do {
        printf("\n Deseja realizar a pesquisa de satisfacao?\n");
        printf(" 1. Sim\n");
        printf(" 2. Nao\n");
        printf("Escolha uma opcao: ");
        validInput = scanf_s("%d", &escolha);

        if (validInput != 1 || escolha < 1 || escolha > 2) {
            system("cls");
            printf("Opcao invalida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
        else {
            switch (escolha) {
            case 1:
                realizarPesquisa(&resposta);
                break;
            case 2:
                printf("Obrigado por visitar o museu PIM!\n");
                return 0;
            }
        }
    } while (escolha != 2);

    return 0;
}