#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void limparBuffer() {
    while (getchar() != '\n');
}

void pressionarEnter() {
    printf("Pressione Enter para continuar...");
    limparBuffer();
}

void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", total);
    printf("-----------------------------------------------\n");
    printf("NOME               | TIPO          | QUANTIDADE\n");
    printf("-----------------------------------------------\n");

    if (total == 0) {
        printf("A mochila está vazia.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("%-18s | %-13s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }

    printf("-----------------------------------------------\n\n");
}

void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia. Gerencie seu loot com atenção.\n\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Novo Item (Loot) ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem '%s' coletado com sucesso.\n", novo.nome);

    listarItens(mochila, *total);
}

void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia. Não há itens para remover.\n\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem não encontrado na mochila.\n");
        return;
    }

    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("\nItem '%s' removido com sucesso.\n", nomeRemover);

    listarItens(mochila, *total);
}

void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia. Nada para buscar.\n\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado.\n\n");
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n==============================================\n");
        printf("   MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA \n");
        printf("==============================================\n");
        printf("\nItens na Mochila: %d/10\n\n", total);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                pressionarEnter();
                break;
            case 2:
                removerItem(mochila, &total);
                pressionarEnter();
                break;
            case 3:
                listarItens(mochila, total);
                pressionarEnter();
                break;
            case 4:
                buscarItem(mochila, total);
                pressionarEnter();
                break;
            case 0:
                printf("\nSaindo do sistema...\n\n");
                break;
            default:
                printf("\nOpção inválida. Escolha novamente.\n");
                pressionarEnter();
        }

    } while (opcao != 0);

    return 0;
}