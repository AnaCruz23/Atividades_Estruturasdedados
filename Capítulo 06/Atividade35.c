#include <stdio.h>
#include <string.h>

#define N 10
#define TAM_NOME 30


typedef struct {
    long comparacoes;
    long deslocamentos;
} Metricas;

void inserir_em_prefixo(int v[], int pos, Metricas *m) {
    int chave = v[pos];
    int j = pos - 1;

    while (j >= 0) {
        m->comparacoes++;
        if (v[j] > chave) {
            v[j + 1] = v[j];
            m->deslocamentos++;
            j--;
        } else {
            break;
        }
    }
    v[j + 1] = chave;
}

Metricas insertion_sort(int v[], int n) {
    Metricas m = {0, 0};
    for (int i = 1; i < n; i++) {
        inserir_em_prefixo(v, i, &m);
    }
    return m;
}

int validar(const int original[], const int ordenado[], int n) {
    long soma_o = 0, soma_s = 0;
    for (int i = 0; i < n; i++) {
        soma_o += original[i];
        soma_s += ordenado[i];
        if (i > 0 && ordenado[i - 1] > ordenado[i]) return 0;
    }
    return soma_o == soma_s;
}

void imprimir(const char *titulo, const int v[], int n) {
    printf("%s: ", titulo);
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void opcao_inteiros(void) {
    int original[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};
    int copia[N];
    memcpy(copia, original, sizeof(original));

    imprimir("Original", original, N);
    Metricas m = insertion_sort(copia, N);
    imprimir("Ordenado", copia, N);

    printf("Comparacoes: %ld | Deslocamentos: %ld\n", m.comparacoes, m.deslocamentos);
    printf("Validacao: %s\n", validar(original, copia, N) ? "OK" : "FALHOU");
}


typedef struct {
    int  id;
    char nome[TAM_NOME];
    int  pontuacao;
} Jogador;

int comparar_jogadores(const Jogador *a, const Jogador *b) {
    int r = strcmp(a->nome, b->nome);
    if (r != 0) return r;
    return (a->id > b->id) - (a->id < b->id);
}

Metricas insertion_sort_jogadores(Jogador v[], int n) {
    Metricas m = {0, 0};

    for (int i = 1; i < n; i++) {
        Jogador chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            m.comparacoes++;
            if (comparar_jogadores(&v[j], &chave) > 0) {
                v[j + 1] = v[j];
                m.deslocamentos++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
    return m;
}

int validar_jogadores(const Jogador original[], const Jogador ordenado[], int n) {
    for (int i = 1; i < n; i++) {
        if (comparar_jogadores(&ordenado[i - 1], &ordenado[i]) > 0) return 0;
    }
    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int k = 0; k < n; k++) {
            if (original[k].id == ordenado[i].id) {
                if (strcmp(original[k].nome, ordenado[i].nome) != 0 ||
                    original[k].pontuacao != ordenado[i].pontuacao) return 0;
                achou = 1;
                break;
            }
        }
        if (!achou) return 0;
    }
    return 1;
}

void imprimir_jogadores(const char *titulo, const Jogador v[], int n) {
    printf("%s\n", titulo);
    printf("  %-4s %-12s %s\n", "ID", "Nome", "Pontos");
    for (int i = 0; i < n; i++) {
        printf("  %-4d %-12s %d\n", v[i].id, v[i].nome, v[i].pontuacao);
    }
}

void opcao_jogadores(void) {
    Jogador original[N] = {
        {105, "Carlos", 870}, {102, "Ana",    950}, {108, "Bruno",  720},
        {101, "Ana",    640}, {110, "Davi",   990}, {103, "Carlos", 410},
        {107, "Bruno",  830}, {104, "Ana",    775}, {109, "Elisa",  560},
        {106, "Bruno",  300}
    };
    Jogador copia[N];
    memcpy(copia, original, sizeof(original));

    imprimir_jogadores("Antes da ordenacao:", original, N);
    Metricas m = insertion_sort_jogadores(copia, N);
    printf("\n");
    imprimir_jogadores("Depois da ordenacao (nome, desempate por id):", copia, N);

    printf("\nComparacoes: %ld | Deslocamentos: %ld\n", m.comparacoes, m.deslocamentos);
    printf("Validacao: %s\n", validar_jogadores(original, copia, N) ? "OK" : "FALHOU");
}



typedef struct {
    long comparacoes;
    long trocas;
    long passagens;
} MetricasBubble;

/* Bubble Sort com indicador de troca e faixa util decrescente. */
MetricasBubble bubble_sort(int v[], int n) {
    MetricasBubble m = {0, 0, 0};
    int limite = n;                       /* faixa util: v[0..limite-1] */

    while (limite > 1) {
        int trocou = 0;                   /* indicador de troca da passagem */
        m.passagens++;

        for (int j = 0; j < limite - 1; j++) {
            m.comparacoes++;              /* compara vizinhos v[j] e v[j+1] */
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                m.trocas++;
                trocou = 1;
            }
        }

        if (!trocou) break;               /* nenhuma troca: ja esta ordenado */
        limite--;                         /* o maior da passagem ja esta no lugar */
    }
    return m;
}

/* Executa o Bubble Sort sobre uma copia e exibe as metricas do formato. */
void testar_bubble(const char *rotulo, const int original[], int n) {
    int copia[N];
    memcpy(copia, original, n * sizeof(int));

    printf("--- %s ---\n", rotulo);
    imprimir("Entrada ", original, n);
    MetricasBubble m = bubble_sort(copia, n);
    imprimir("Saida   ", copia, n);
    printf("Passagens: %ld | Comparacoes: %ld | Trocas: %ld\n", m.passagens, m.comparacoes, m.trocas);
    printf("Validacao: %s\n\n", validar(original, copia, n) ? "OK" : "FALHOU");
}

void opcao_bubble(void) {
    int ordenado[N]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int inverso[N]   = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int aleatorio[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};

    testar_bubble("Vetor ordenado",       ordenado,  N);
    testar_bubble("Vetor em ordem inversa", inverso,   N);
    testar_bubble("Vetor aleatorio",      aleatorio, N);
}



int main(void) {
    int opcao;
    do {
        printf("\n=== CENTRAL DE ORDENACAO ===\n");
        printf("1 - Insertion Sort em numeros (Questao 1)\n");
        printf("2 - Insertion Sort em jogadores por nome (Questao 2)\n");
        printf("3 - Bubble Sort com parada antecipada (Questao 3)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        printf("\n");

        switch (opcao) {
            case 1: opcao_inteiros();  break;
            case 2: opcao_jogadores(); break;
            case 3: opcao_bubble();    break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}