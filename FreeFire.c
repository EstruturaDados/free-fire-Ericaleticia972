
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

Componente mochila[MAX];
int total = 0;
int ordenadoPorNome = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pausar() {
    printf("Pressione Enter para continuar...");
    limparBuffer();
}

void mostrarComponentes() {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n--- INVENTARIO ATUAL (%d/10) ---\n", total);
    printf("NOME              | TIPO               | PRIORIDADE\n");

    for (int i = 0; i < total; i++) {
        printf("%-18s %-20s %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].prioridade);
    }
}

void bubbleSortNome(int *comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < total; i++) {
        Componente atual = mochila[i];
        int j = i - 1;

        while (j >= 0 && strcmp(mochila[j].tipo, atual.tipo) > 0) {
            (*comparacoes)++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = atual;
    }
}

void selectionSortPrioridade(int *comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < total - 1; i++) {
        int min = i;

        for (int j = i + 1; j < total; j++) {
            (*comparacoes)++;
            if (mochila[j].prioridade < mochila[min].prioridade) {
                min = j;
            }
        }

        Componente temp = mochila[i];
        mochila[i] = mochila[min];
        mochila[min] = temp;
    }
}

int buscaBinaria(char chave[]) {
    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(chave, mochila[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

void adicionarComponente() {
    if (total >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }

    Componente c;

    printf("\nColetando Novo Componente ---\n");

    printf("Nome: ");
    limparBuffer();
    fgets(c.nome, 30, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(c.tipo, 20, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = 0;

    printf("Prioridade de Montagem (1-10): ");
    scanf("%d", &c.prioridade);

    mochila[total++] = c;
    ordenadoPorNome = 0;

    printf("Componente '%s' adicionado!\n", c.nome);
    pausar();
}

void descartarComponente() {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nome[30];
    printf("\nNome para remover: ");
    limparBuffer();
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            total--;
            printf("Componente removido.\n");
            pausar();
            return;
        }
    }

    printf("Componente nao encontrado.\n");
    pausar();
}

void organizarMochila() {
    int escolha;
    int comparacoes = 0;
    clock_t inicio, fim;

    printf("\nEstrategia de Organizacao ---\n");
    printf("1. Por Nome (Bolha)\n");
    printf("2. Por Tipo (Insercao)\n");
    printf("3. Por Prioridade (Selecao)\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &escolha);

    inicio = clock();

    switch (escolha) {
        case 1:
            bubbleSortNome(&comparacoes);
            ordenadoPorNome = 1;
            break;
        case 2:
            insertionSortTipo(&comparacoes);
            ordenadoPorNome = 0;
            break;
        case 3:
            selectionSortPrioridade(&comparacoes);
            ordenadoPorNome = 0;
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida.\n");
            return;
    }

    fim = clock();

    mostrarComponentes();

    printf("\nComparacoes: %d\n", comparacoes);
    printf("Tempo: %.5f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    pausar();
}

void buscaComponenteChave() {
    if (!ordenadoPorNome) {
        printf("\nPrecisa ordenar pelo NOME antes de usar busca binaria!\n");
        pausar();
        return;
    }

    char chave[] = "NucleoMestre";

    int pos = buscaBinaria(chave);

    if (pos >= 0) {
        printf("\nComponente-chave '%s' encontrado!\n", chave);
    } else {
        printf("\nComponente-chave '%s' NAO encontrado.\n", chave);
    }

    pausar();
}

int main() {
    int opcao;

    do {
        system("clear || cls");

        printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("Itens na Mochila: %d/10\n", total);
        printf("Status da Ordenacao por Nome: %s\n",
               ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");

        printf("\n1. Adicionar Componente");
        printf("\n2. Descartar Componente");
        printf("\n3. Listar Componentes");
        printf("\n4. Organizar Mochila");
        printf("\n5. Busca Binaria por Componente-Chave");
        printf("\n0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("\nEscolha: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarComponente(); break;
            case 2: descartarComponente(); break;
            case 3: mostrarComponentes(); pausar(); break;
            case 4: organizarMochila(); break;
            case 5: buscaComponenteChave(); break;

            case 0:
                if (buscaBinaria("NucleoMestre") >= 0 && ordenadoPorNome) {
                    printf("\nTORRE DE FUGA ATIVADA!\n");
                } else {
                    printf("\nNao foi possivel ativar a torre.\n");
                }
                break;

            default:
                printf("Opcao invalida.\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}