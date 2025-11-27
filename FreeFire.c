#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* ----- LISTA ENCADEADA ----- */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

No* lista = NULL;

/* ----- BUFFER / ENTER ----- */
void limparBuffer() {
    while (getchar() != '\n');
}

void pressionarEnter() {
    printf("Pressione Enter para continuar...");
    limparBuffer();
}

/* ----- LISTAR (VETOR) ----- */
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

/* ----- INSERIR (LISTA) ----- */
void inserirLista(Item novo) {
    No* n = (No*)malloc(sizeof(No));
    n->dados = novo;
    n->proximo = lista;
    lista = n;
}

/* ----- REMOVER (LISTA) ----- */
void removerLista(char nome[]) {
    No* atual = lista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

/* ----- BUSCA SEQUENCIAL LISTA ----- */
int buscarLista(char nome[], Item* retorno, int* comparacoes) {
    *comparacoes = 0;
    No* atual = lista;

    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            *retorno = atual->dados;
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

/* ----- INSERIR (VETOR) ----- */
void inserirItem(Item mochila[], int* total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia.\n\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Novo Item (Loot) ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    inserirLista(novo);

    printf("\nItem '%s' coletado com sucesso.\n", novo.nome);

    listarItens(mochila, *total);
}

/* ----- REMOVER (VETOR) ----- */
void removerItem(Item mochila[], int* total) {
    if (*total == 0) {
        printf("\nA mochila está vazia.\n\n");
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

    removerLista(nomeRemover);

    for (int i = encontrado; i < *total - 1; i++)
        mochila[i] = mochila[i + 1];

    (*total)--;

    printf("\nItem '%s' removido com sucesso.\n", nomeRemover);

    listarItens(mochila, *total);
}

/* ----- ORDENAR (VETOR) ----- */
void ordenarVetor(Item mochila[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

/* ----- BUSCA SEQUENCIAL VETOR ----- */
int buscarSequencialVetor(Item mochila[], int total, char nome[], int* comparacoes, Item* retorno) {
    *comparacoes = 0;
    for (int i = 0; i < total; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            *retorno = mochila[i];
            return 1;
        }
    }
    return 0;
}

/* ----- BUSCA BINÁRIA VETOR ----- */
int buscarBinariaVetor(Item mochila[], int total, char nome[], int* comparacoes, Item* retorno) {
    *comparacoes = 0;
    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        (*comparacoes)++;
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            *retorno = mochila[meio];
            return 1;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return 0;
}

/* ----- BUSCAR ITEM (MENU) ----- */
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item na Mochila ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    ordenarVetor(mochila, total);

    int compSeqVetor, compBinVetor, compLista;
    Item retorno;

    int achouSeq = buscarSequencialVetor(mochila, total, nomeBusca, &compSeqVetor, &retorno);
    int achouBin = buscarBinariaVetor(mochila, total, nomeBusca, &compBinVetor, &retorno);
    int achouLista = buscarLista(nomeBusca, &retorno, &compLista);

    printf("\n--- RESULTADO DA BUSCA ---\n");

    if (achouSeq)
        printf("Item encontrado: %s (%s) x%d\n", retorno.nome, retorno.tipo, retorno.quantidade);
    else
        printf("Resultado: Item '%s' NAO foi encontrado na mochila.\n", nomeBusca);


}

/* ------------------ MAIN ------------------ */
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
        printf("4. Buscar Item por Nome\n");
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
                printf("\nOpção inválida.\n");
                pressionarEnter();
        }

    } while (opcao != 0);

    return 0;
}