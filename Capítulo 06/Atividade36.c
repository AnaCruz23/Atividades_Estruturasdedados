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
    int  vida;              
} Jogador;

/* Dados de exemplo compartilhados (nomes e vidas repetidos de proposito). */
static const Jogador DADOS_JOGADORES[N] = {
    {105, "Carlos", 870, 60}, {102, "Ana",    950, 100}, {108, "Bruno",  720, 45},
    {101, "Ana",    640, 100}, {110, "Davi",   990, 80}, {103, "Carlos", 410, 25},
    {107, "Bruno",  830, 60}, {104, "Ana",    775, 90}, {109, "Elisa",  560, 45},
    {106, "Bruno",  300, 10}
};

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
    printf("  %-4s %-12s %-7s %s\n", "ID", "Nome", "Pontos", "Vida");
    for (int i = 0; i < n; i++) {
        printf("  %-4d %-12s %-7d %d\n", v[i].id, v[i].nome, v[i].pontuacao, v[i].vida);
    }
}

void opcao_jogadores(void) {
    Jogador original[N];
    Jogador copia[N];
    memcpy(original, DADOS_JOGADORES, sizeof(original));
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

MetricasBubble bubble_sort(int v[], int n) {
    MetricasBubble m = {0, 0, 0};
    int limite = n;

    while (limite > 1) {
        int trocou = 0;
        m.passagens++;

        for (int j = 0; j < limite - 1; j++) {
            m.comparacoes++;
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                m.trocas++;
                trocou = 1;
            }
        }

        if (!trocou) break;
        limite--;
    }
    return m;
}

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

    testar_bubble("Vetor ordenado",         ordenado,  N);
    testar_bubble("Vetor em ordem inversa", inverso,   N);
    testar_bubble("Vetor aleatorio",        aleatorio, N);
}


/* Tipo da regra de comparacao: retorna >0 se 'a' deve vir DEPOIS de 'b'. */
typedef int (*Comparador)(const Jogador *a, const Jogador *b);

static int cmp_int(int x, int y) { return (x > y) - (x < y); }

/* Regras de comparacao (a logica de ordenacao nao conhece nenhuma delas).
   Em todas, o desempate e pelo id crescente, para o resultado ser unico. */
int cmp_vida_cresc(const Jogador *a, const Jogador *b) {
    int r = cmp_int(a->vida, b->vida);
    return (r != 0) ? r : cmp_int(a->id, b->id);
}

int cmp_vida_decr(const Jogador *a, const Jogador *b) {
    int r = cmp_int(b->vida, a->vida);          /* inverte a direcao */
    return (r != 0) ? r : cmp_int(a->id, b->id);
}

int cmp_id_cresc(const Jogador *a, const Jogador *b) {
    return cmp_int(a->id, b->id);
}

int cmp_id_decr(const Jogador *a, const Jogador *b) {
    return cmp_int(b->id, a->id);
}

/* Bubble Sort generico: recebe a regra por ponteiro de funcao. */
MetricasBubble bubble_sort_jogadores(Jogador v[], int n, Comparador cmp) {
    MetricasBubble m = {0, 0, 0};
    int limite = n;                               /* faixa util */

    while (limite > 1) {
        int trocou = 0;
        m.passagens++;

        for (int j = 0; j < limite - 1; j++) {
            m.comparacoes++;
            if (cmp(&v[j], &v[j + 1]) > 0) {
                Jogador tmp = v[j];               /* troca TODOS os membros */
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                m.trocas++;
                trocou = 1;
            }
        }

        if (!trocou) break;                       /* parada antecipada */
        limite--;
    }
    return m;
}

/* Valida: ordem final segundo a regra usada + cada id com os mesmos dados. */
int validar_ordem_jogadores(const Jogador original[], const Jogador ordenado[],
                            int n, Comparador cmp) {
    for (int i = 1; i < n; i++) {
        if (cmp(&ordenado[i - 1], &ordenado[i]) > 0) return 0;
    }
    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int k = 0; k < n; k++) {
            if (original[k].id == ordenado[i].id) {
                if (strcmp(original[k].nome, ordenado[i].nome) != 0 ||
                    original[k].pontuacao != ordenado[i].pontuacao ||
                    original[k].vida != ordenado[i].vida) return 0;
                achou = 1;
                break;
            }
        }
        if (!achou) return 0;
    }
    return 1;
}

void executar_bubble_jogadores(const char *campo, const char *direcao, Comparador cmp) {
    Jogador original[N];
    Jogador copia[N];
    memcpy(original, DADOS_JOGADORES, sizeof(original));
    memcpy(copia, original, sizeof(original));

    printf("Campo: %s | Direcao: %s\n\n", campo, direcao);
    imprimir_jogadores("Antes da ordenacao:", original, N);

    MetricasBubble m = bubble_sort_jogadores(copia, N, cmp);

    printf("\n");
    imprimir_jogadores("Depois da ordenacao:", copia, N);
    printf("\nPassagens: %ld | Comparacoes: %ld | Trocas: %ld\n",
           m.passagens, m.comparacoes, m.trocas);
    printf("Validacao: %s\n",
           validar_ordem_jogadores(original, copia, N, cmp) ? "OK" : "FALHOU");
}

void opcao_bubble_jogadores(void) {
    int escolha;

    printf("--- Bubble Sort em jogadores ---\n");
    printf("1 - Vida crescente\n");
    printf("2 - Vida decrescente\n");
    printf("3 - Identificador crescente\n");
    printf("4 - Identificador decrescente\n");
    printf("Criterio: ");
    if (scanf("%d", &escolha) != 1) return;
    printf("\n");

    switch (escolha) {
        case 1: executar_bubble_jogadores("vida", "crescente",   cmp_vida_cresc); break;
        case 2: executar_bubble_jogadores("vida", "decrescente", cmp_vida_decr);  break;
        case 3: executar_bubble_jogadores("id",   "crescente",   cmp_id_cresc);   break;
        case 4: executar_bubble_jogadores("id",   "decrescente", cmp_id_decr);    break;
        default: printf("Criterio invalido.\n");
    }
}

int main(void) {
    int opcao;
    do {
        printf("\n=== CENTRAL DE ORDENACAO ===\n");
        printf("1 - Insertion Sort em numeros (Questao 1)\n");
        printf("2 - Insertion Sort em jogadores por nome (Questao 2)\n");
        printf("3 - Bubble Sort com parada antecipada (Questao 3)\n");
        printf("4 - Bubble Sort em jogadores por vida/id (Questao 4)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        printf("\n");

        switch (opcao) {
            case 1: opcao_inteiros();         break;
            case 2: opcao_jogadores();        break;
            case 3: opcao_bubble();           break;
            case 4: opcao_bubble_jogadores(); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}