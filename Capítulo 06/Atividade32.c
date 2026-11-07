#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10
#define TAM_NOME 30


typedef struct {
    long comparacoes;
    long trocas;
} Metricas;

typedef struct {
    int  id;                 /* identificador unico */
    char nome[TAM_NOME];
    int  pontuacao;
} Jogador;

/* Entradas ORIGINAIS: nunca sao ordenadas. Toda ordenacao roda numa copia. */
static const int ORIGINAL_NUMEROS[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};

/* Pontuacoes e nomes repetidos de proposito, para testar o desempate. */
static const Jogador ORIGINAL_JOGADORES[N] = {
    {101, "Ana",    850}, {102, "Bruno",  920}, {103, "Carlos", 850},
    {104, "Ana",    850}, {105, "Davi",   700}, {106, "Elisa",  920},
    {107, "Bruno",  920}, {108, "Fabio",  610}, {109, "Gabi",   700},
    {110, "Hugo",   990}
};

void imprimir_numeros(const char *titulo, const int v[], int n) {
    printf("%s: ", titulo);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void imprimir_jogadores(const char *titulo, const Jogador v[], int n) {
    printf("%s\n", titulo);
    printf("  %-4s %-8s %s\n", "ID", "Nome", "Pontos");
    for (int i = 0; i < n; i++) {
        printf("  %-4d %-8s %d\n", v[i].id, v[i].nome, v[i].pontuacao);
    }
}



/* ---- Numeros (ordem crescente) ---- */

/* Devolve o indice do menor valor em v[inicio..n-1]. */
int encontrar_menor(const int v[], int inicio, int n, Metricas *m) {
    int menor = inicio;
    for (int j = inicio + 1; j < n; j++) {
        m->comparacoes++;
        if (v[j] < v[menor]) menor = j;
    }
    return menor;
}

Metricas selection_sort(int v[], int n) {
    Metricas m = {0, 0};

    for (int i = 0; i < n - 1; i++) {
        int menor = encontrar_menor(v, i, n, &m);
        if (menor != i) {                    /* so troca se for preciso */
            int tmp = v[i];
            v[i] = v[menor];
            v[menor] = tmp;
            m.trocas++;
        }
    }
    return m;
}


/* Retorna <0 se 'a' deve vir ANTES de 'b', >0 se depois.
   1o criterio: pontuacao decrescente.
   2o criterio: nome (strcmp) crescente.
   3o criterio: id crescente (unico, entao nunca ha empate total). */
int comparar_jogadores(const Jogador *a, const Jogador *b) {
    if (a->pontuacao != b->pontuacao)
        return (a->pontuacao < b->pontuacao) - (a->pontuacao > b->pontuacao);

    int r = strcmp(a->nome, b->nome);
    if (r != 0) return r;

    return (a->id > b->id) - (a->id < b->id);
}

/* Devolve o indice do jogador que deve ficar primeiro em v[inicio..n-1]. */
int encontrar_melhor_jogador(const Jogador v[], int inicio, int n, Metricas *m) {
    int melhor = inicio;
    for (int j = inicio + 1; j < n; j++) {
        m->comparacoes++;
        if (comparar_jogadores(&v[j], &v[melhor]) < 0) melhor = j;
    }
    return melhor;
}

Metricas selection_sort_jogadores(Jogador v[], int n) {
    Metricas m = {0, 0};

    for (int i = 0; i < n - 1; i++) {
        int melhor = encontrar_melhor_jogador(v, i, n, &m);
        if (melhor != i) {
            Jogador tmp = v[i];              /* troca a estrutura INTEIRA */
            v[i] = v[melhor];
            v[melhor] = tmp;
            m.trocas++;
        }
    }
    return m;
}



static int cmp_int_qsort(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Ordenado e identico a uma ordenacao de referencia (mesmos elementos). */
int validar_numeros(const int original[], const int ordenado[], int n) {
    int ref[N];
    memcpy(ref, original, (size_t)n * sizeof(int));
    qsort(ref, (size_t)n, sizeof(int), cmp_int_qsort);
    return memcmp(ref, ordenado, (size_t)n * sizeof(int)) == 0;
}

/* Ordem correta pelo criterio + cada jogador da entrada aparece uma
   unica vez na saida, com id, nome e pontuacao juntos. */
int validar_jogadores(const Jogador original[], const Jogador ordenado[], int n) {
    int usado[N] = {0};

    for (int i = 1; i < n; i++) {
        if (comparar_jogadores(&ordenado[i - 1], &ordenado[i]) > 0) return 0;
    }
    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int k = 0; k < n; k++) {
            if (!usado[k] &&
                original[k].id == ordenado[i].id &&
                strcmp(original[k].nome, ordenado[i].nome) == 0 &&
                original[k].pontuacao == ordenado[i].pontuacao) {
                usado[k] = 1;
                achou = 1;
                break;
            }
        }
        if (!achou) return 0;
    }
    return 1;
}


void opcao_selection_numeros(void) {
    int copia[N];
    memcpy(copia, ORIGINAL_NUMEROS, sizeof(copia));      /* copia de trabalho */

    imprimir_numeros("Original", ORIGINAL_NUMEROS, N);
    Metricas m = selection_sort(copia, N);
    imprimir_numeros("Ordenado", copia, N);
    imprimir_numeros("Original (inalterado)", ORIGINAL_NUMEROS, N);

    printf("Comparacoes: %ld | Trocas: %ld\n", m.comparacoes, m.trocas);
    printf("Validacao: %s\n", validar_numeros(ORIGINAL_NUMEROS, copia, N) ? "OK" : "FALHOU");
}

void opcao_selection_jogadores(void) {
    Jogador copia[N];
    memcpy(copia, ORIGINAL_JOGADORES, sizeof(copia));    /* copia de trabalho */

    imprimir_jogadores("Antes (original):", ORIGINAL_JOGADORES, N);
    Metricas m = selection_sort_jogadores(copia, N);
    printf("\n");
    imprimir_jogadores("Depois (pontuacao decrescente, desempate por nome e id):", copia, N);

    printf("\nComparacoes: %ld | Trocas: %ld\n", m.comparacoes, m.trocas);
    printf("Validacao: %s\n",
           validar_jogadores(ORIGINAL_JOGADORES, copia, N) ? "OK" : "FALHOU");
}



int main(void) {
    int opcao;
    do {
        printf("\n=== CENTRAL DE ORDENACAO ===\n");
        printf("1 - Selection Sort em numeros (Questao 1)\n");
        printf("2 - Selection Sort em jogadores por pontuacao (Questao 1)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        printf("\n");

        switch (opcao) {
            case 1: opcao_selection_numeros();   break;
            case 2: opcao_selection_jogadores(); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}