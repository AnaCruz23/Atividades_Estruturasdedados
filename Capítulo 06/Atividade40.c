#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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


typedef int (*Comparador)(const Jogador *a, const Jogador *b);

static int cmp_int(int x, int y) { return (x > y) - (x < y); }

int cmp_vida_cresc(const Jogador *a, const Jogador *b) {
    int r = cmp_int(a->vida, b->vida);
    return (r != 0) ? r : cmp_int(a->id, b->id);
}

int cmp_vida_decr(const Jogador *a, const Jogador *b) {
    int r = cmp_int(b->vida, a->vida);
    return (r != 0) ? r : cmp_int(a->id, b->id);
}

int cmp_id_cresc(const Jogador *a, const Jogador *b) {
    return cmp_int(a->id, b->id);
}

int cmp_id_decr(const Jogador *a, const Jogador *b) {
    return cmp_int(b->id, a->id);
}

MetricasBubble bubble_sort_jogadores(Jogador v[], int n, Comparador cmp) {
    MetricasBubble m = {0, 0, 0};
    int limite = n;

    while (limite > 1) {
        int trocou = 0;
        m.passagens++;

        for (int j = 0; j < limite - 1; j++) {
            m.comparacoes++;
            if (cmp(&v[j], &v[j + 1]) > 0) {
                Jogador tmp = v[j];
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


typedef struct {
    long comparacoes;
    long copias;
} MetricasMerge;

void intercalar(const int a[], int na, const int b[], int nb,
                int saida[], MetricasMerge *m) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < na && j < nb) {
        m->comparacoes++;
        if (a[i] <= b[j]) {
            saida[k++] = a[i++];
        } else {
            saida[k++] = b[j++];
        }
    }

    while (i < na) saida[k++] = a[i++];
    while (j < nb) saida[k++] = b[j++];
}

long dividir_intervalo(int ini, int fim, int nivel) {
    long chamadas = 1;

    for (int e = 0; e < nivel; e++) printf("  ");

    if (ini >= fim) {
        printf("[%d..%d] caso-base (resolvido)\n", ini, fim);
        return chamadas;
    }

    int meio = ini + (fim - ini) / 2;
    printf("[%d..%d] meio=%d -> [%d..%d] e [%d..%d]\n",
           ini, fim, meio, ini, meio, meio + 1, fim);

    chamadas += dividir_intervalo(ini, meio, nivel + 1);
    chamadas += dividir_intervalo(meio + 1, fim, nivel + 1);

    return chamadas;
}

int validar_intercalacao(const int a[], int na, const int b[], int nb,
                         const int saida[]) {
    long soma_entradas = 0, soma_saida = 0;
    for (int i = 0; i < na; i++) soma_entradas += a[i];
    for (int i = 0; i < nb; i++) soma_entradas += b[i];
    for (int i = 0; i < na + nb; i++) {
        soma_saida += saida[i];
        if (i > 0 && saida[i - 1] > saida[i]) return 0;
    }
    return soma_entradas == soma_saida;
}

void testar_intercalacao(const char *rotulo, const int a[], int na,
                         const int b[], int nb) {
    int saida[2 * N];
    MetricasMerge m = {0};

    printf("--- %s ---\n", rotulo);
    imprimir("Vetor A", a, na);
    imprimir("Vetor B", b, nb);
    intercalar(a, na, b, nb, saida, &m);
    imprimir("Saida  ", saida, na + nb);
    printf("Comparacoes: %ld | Elementos na saida: %d (esperado %d)\n",
           m.comparacoes, na + nb, na + nb);
    printf("Validacao: %s\n\n",
           validar_intercalacao(a, na, b, nb, saida) ? "OK" : "FALHOU");
}

void opcao_merge_base(void) {
    int a1[] = {2, 5, 9, 14, 20};
    int b1[] = {1, 5, 7, 14, 30, 41};

    int a2[] = {1, 2, 3};
    int b2[] = {10, 20, 30, 40};

    int a3[] = {50, 60, 70, 80};
    int b3[] = {5, 6};

    testar_intercalacao("Valores repetidos entre A e B", a1, 5, b1, 6);
    testar_intercalacao("A termina primeiro",            a2, 3, b2, 4);
    testar_intercalacao("B termina primeiro",            a3, 4, b3, 2);

    printf("--- Divisao recursiva do intervalo [0..%d] ---\n", N - 1);
    long chamadas = dividir_intervalo(0, N - 1, 0);
    printf("Total de chamadas recursivas: %ld\n", chamadas);
}


typedef int (*ComparadorGen)(const void *a, const void *b);

static void intercalar_intervalo(char *base, char *aux, size_t tam,
                                 long ini, long meio, long fim,
                                 ComparadorGen cmp, MetricasMerge *m) {
    long i = ini;
    long j = meio + 1;
    long k = 0;

    while (i <= meio && j <= fim) {
        m->comparacoes++;
        if (cmp(base + i * tam, base + j * tam) <= 0) {
            memcpy(aux + k * tam, base + i * tam, tam);
            i++;
        } else {
            memcpy(aux + k * tam, base + j * tam, tam);
            j++;
        }
        k++;
        m->copias++;
    }

    while (i <= meio) {
        memcpy(aux + k * tam, base + i * tam, tam);
        i++; k++; m->copias++;
    }
    while (j <= fim) {
        memcpy(aux + k * tam, base + j * tam, tam);
        j++; k++; m->copias++;
    }

    memcpy(base + ini * tam, aux, (size_t)k * tam);
}

static void ordenar_recursivo(char *base, char *aux, size_t tam,
                              long ini, long fim,
                              ComparadorGen cmp, MetricasMerge *m) {
    if (ini >= fim) return;

    long meio = ini + (fim - ini) / 2;

    ordenar_recursivo(base, aux, tam, ini, meio, cmp, m);
    ordenar_recursivo(base, aux, tam, meio + 1, fim, cmp, m);

    intercalar_intervalo(base, aux, tam, ini, meio, fim, cmp, m);
}

int merge_sort_generico(void *base, size_t n, size_t tam,
                        ComparadorGen cmp, MetricasMerge *m) {
    if (n <= 1) return 0;

    char *aux = malloc(n * tam);
    if (aux == NULL) return -1;

    ordenar_recursivo((char *)base, aux, tam, 0, (long)n - 1, cmp, m);

    free(aux);
    return 0;
}

static int cmp_int_gen(const void *a, const void *b) {
    return cmp_int(*(const int *)a, *(const int *)b);
}

int merge_sort_inteiros(int v[], int n, MetricasMerge *m) {
    return merge_sort_generico(v, (size_t)n, sizeof(int), cmp_int_gen, m);
}

static int cmp_nome_gen(const void *a, const void *b) {
    return comparar_jogadores((const Jogador *)a, (const Jogador *)b);
}

static int cmp_pontuacao_decr_gen(const void *a, const void *b) {
    const Jogador *x = (const Jogador *)a;
    const Jogador *y = (const Jogador *)b;
    int r = cmp_int(y->pontuacao, x->pontuacao);
    return (r != 0) ? r : cmp_int(x->id, y->id);
}

int merge_sort_jogadores(Jogador v[], int n, ComparadorGen criterio, MetricasMerge *m) {
    return merge_sort_generico(v, (size_t)n, sizeof(Jogador), criterio, m);
}

int validar_merge_inteiros(const int original[], const int saida[], int n) {
    int ref[N];
    if (n > N) return 0;
    memcpy(ref, original, (size_t)n * sizeof(int));
    insertion_sort(ref, n);
    return memcmp(ref, saida, (size_t)n * sizeof(int)) == 0;
}

int validar_merge_jogadores(const Jogador original[], const Jogador saida[],
                            int n, ComparadorGen cmp) {
    int usado[N] = {0};

    for (int i = 1; i < n; i++) {
        if (cmp(&saida[i - 1], &saida[i]) > 0) return 0;
    }
    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int k = 0; k < n; k++) {
            if (!usado[k] && memcmp(&original[k], &saida[i], sizeof(Jogador)) == 0) {
                usado[k] = 1;
                achou = 1;
                break;
            }
        }
        if (!achou) return 0;
    }
    return 1;
}

void testar_merge_inteiros(const char *rotulo, const int original[], int n) {
    int copia[N];
    MetricasMerge m = {0, 0};

    if (n > 0) memcpy(copia, original, (size_t)n * sizeof(int));

    printf("--- %s ---\n", rotulo);
    imprimir("Entrada", original, n);
    if (merge_sort_inteiros(copia, n, &m) != 0) {
        printf("Erro: falha ao alocar memoria auxiliar.\n\n");
        return;
    }
    imprimir("Saida  ", copia, n);
    printf("Comparacoes: %ld | Copias para o auxiliar: %ld\n", m.comparacoes, m.copias);
    printf("Validacao: %s\n\n", validar_merge_inteiros(original, copia, n) ? "OK" : "FALHOU");
}

void testar_merge_jogadores(const char *rotulo, ComparadorGen criterio) {
    Jogador original[N];
    Jogador copia[N];
    MetricasMerge m = {0, 0};

    memcpy(original, DADOS_JOGADORES, sizeof(original));
    memcpy(copia, original, sizeof(original));

    printf("--- %s ---\n", rotulo);
    imprimir_jogadores("Antes:", original, N);
    if (merge_sort_jogadores(copia, N, criterio, &m) != 0) {
        printf("Erro: falha ao alocar memoria auxiliar.\n\n");
        return;
    }
    printf("\n");
    imprimir_jogadores("Depois:", copia, N);
    printf("\nComparacoes: %ld | Copias para o auxiliar: %ld\n", m.comparacoes, m.copias);
    printf("Validacao: %s\n\n",
           validar_merge_jogadores(original, copia, N, criterio) ? "OK" : "FALHOU");
}

void opcao_merge_sort(void) {
    int aleatorio[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};
    int ordenado[N]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int inverso[N]   = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    int vazio[1]     = {0};
    int unico[1]     = {99};
    int repetidos[8] = {3, 1, 3, 1, 2, 2, 3, 1};

    printf("===== Merge Sort em numeros =====\n\n");
    testar_merge_inteiros("Aleatorio (com 7 repetido)", aleatorio, N);
    testar_merge_inteiros("Ja ordenado",                ordenado,  N);
    testar_merge_inteiros("Ordem inversa",              inverso,   N);
    testar_merge_inteiros("Muitos repetidos",           repetidos, 8);
    testar_merge_inteiros("Caso-base: 0 elementos",     vazio,     0);
    testar_merge_inteiros("Caso-base: 1 elemento",      unico,     1);

    printf("===== Merge Sort em jogadores =====\n\n");
    testar_merge_jogadores("Criterio: nome (desempate por id)", cmp_nome_gen);
    testar_merge_jogadores("Criterio: pontuacao decrescente (desempate por id)",
                           cmp_pontuacao_decr_gen);
}



typedef struct {
    long comparacoes;
    long trocas;
} MetricasQuick;

int particao_auxiliar(const int v[], int n, int saida[], MetricasQuick *m) {
    int pivo = v[n - 1];
    int esq = 0;
    int dir = n;

    for (int i = 0; i < n - 1; i++) {
        m->comparacoes++;
        if (v[i] < pivo) saida[esq++] = v[i];
        else             saida[--dir] = v[i];
    }
    saida[esq] = pivo;

    for (int a = esq + 1, b = n - 1; a < b; a++, b--) {
        int t = saida[a]; saida[a] = saida[b]; saida[b] = t;
    }
    return esq;
}

static void trocar_int(int *a, int *b, MetricasQuick *m) {
    int t = *a; *a = *b; *b = t;
    m->trocas++;
}

int particao_in_place(int v[], int ini, int fim, MetricasQuick *m) {
    int pivo = v[fim];
    int i = ini;

    for (int j = ini; j < fim; j++) {
        m->comparacoes++;
        if (v[j] < pivo) {
            if (i != j) trocar_int(&v[i], &v[j], m);
            i++;
        }
    }
    if (i != fim) trocar_int(&v[i], &v[fim], m);
    return i;
}

void quick_sort(int v[], int ini, int fim, MetricasQuick *m) {
    if (ini >= fim) return;

    int p = particao_in_place(v, ini, fim, m);

    if (p - 1 > ini) quick_sort(v, ini, p - 1, m);
    if (p + 1 < fim) quick_sort(v, p + 1, fim, m);
}

static int mesmos_elementos(const int a[], const int b[], int n) {
    int ra[N], rb[N];
    if (n > N) return 0;
    memcpy(ra, a, (size_t)n * sizeof(int));
    memcpy(rb, b, (size_t)n * sizeof(int));
    insertion_sort(ra, n);
    insertion_sort(rb, n);
    return memcmp(ra, rb, (size_t)n * sizeof(int)) == 0;
}

static int validar_particao(const int v[], int n, int pos, int pivo) {
    if (pos < 0 || pos >= n || v[pos] != pivo) return 0;
    for (int i = 0; i < pos; i++)  if (v[i] >= pivo) return 0;
    for (int i = pos + 1; i < n; i++) if (v[i] < pivo) return 0;
    return 1;
}

void testar_particoes(const char *rotulo, const int original[], int n) {
    int pivo = original[n - 1];
    int aux_saida[N];
    int in_place[N];
    MetricasQuick ma = {0, 0};
    MetricasQuick mi = {0, 0};

    memcpy(in_place, original, (size_t)n * sizeof(int));

    printf("--- %s ---\n", rotulo);
    imprimir("Entrada          ", original, n);
    printf("Pivo (ultimo elemento): %d\n", pivo);

    int pa = particao_auxiliar(original, n, aux_saida, &ma);
    imprimir("Particao auxiliar", aux_saida, n);
    printf("  Posicao final do pivo: %d | Comparacoes: %ld\n", pa, ma.comparacoes);
    printf("  Validacao: %s\n",
           (validar_particao(aux_saida, n, pa, pivo) &&
            mesmos_elementos(original, aux_saida, n)) ? "OK" : "FALHOU");

    int pi = particao_in_place(in_place, 0, n - 1, &mi);
    imprimir("Particao in-place", in_place, n);
    printf("  Posicao final do pivo: %d | Comparacoes: %ld | Trocas: %ld\n",
           pi, mi.comparacoes, mi.trocas);
    printf("  Validacao: %s\n\n",
           (validar_particao(in_place, n, pi, pivo) &&
            mesmos_elementos(original, in_place, n)) ? "OK" : "FALHOU");
}

void testar_quick(const char *rotulo, const int original[], int n) {
    int copia[N];
    MetricasQuick m = {0, 0};

    memcpy(copia, original, (size_t)n * sizeof(int));

    printf("--- %s ---\n", rotulo);
    imprimir("Entrada", original, n);
    quick_sort(copia, 0, n - 1, &m);
    imprimir("Saida  ", copia, n);
    printf("Comparacoes: %ld | Trocas: %ld\n", m.comparacoes, m.trocas);
    printf("Validacao: %s\n\n",
           (validar(original, copia, n) && mesmos_elementos(original, copia, n))
               ? "OK" : "FALHOU");
}

void opcao_quick_sort(void) {
    int aleatorio[N]  = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};
    int ordenado[N]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int inverso[N]    = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int repetidos[N]  = {5, 3, 5, 1, 5, 2, 5, 4, 5, 5};
    int iguais[6]     = {4, 4, 4, 4, 4, 4};

    printf("===== Particoes isoladas =====\n\n");
    testar_particoes("Aleatorio (pivo 10)",              aleatorio, N);
    testar_particoes("Valores repetidos (pivo 5)",       repetidos, N);
    testar_particoes("Todos iguais (pivo 4)",            iguais,    6);

    printf("===== Quick Sort recursivo =====\n\n");
    testar_quick("Aleatorio (com 7 repetido)", aleatorio, N);
    testar_quick("Ja ordenado",                ordenado,  N);
    testar_quick("Ordem inversa",              inverso,   N);
    testar_quick("Valores repetidos",          repetidos, N);
    testar_quick("Todos iguais",               iguais,    6);
}


#define MAXD 1000            /* maximo de elementos na central final */

/* ---- Pivo aleatorio ---- */

/* Sorteia uma posicao DENTRO de [ini, fim]. O gerador (srand) e
   inicializado uma unica vez, em main(). */
static int escolher_pivo_aleatorio(int ini, int fim) {
    return ini + rand() % (fim - ini + 1);
}

/* Particao com pivo aleatorio (numeros): leva o pivo sorteado para a
   posicao esperada pela particao (o ultimo indice do intervalo) e
   reaproveita a particao in-place da Questao 7. */
int particao_aleatoria_inteiros(int v[], int ini, int fim, MetricasQuick *m) {
    int p = escolher_pivo_aleatorio(ini, fim);
    if (p != fim) trocar_int(&v[p], &v[fim], m);
    return particao_in_place(v, ini, fim, m);
}

void quick_sort_aleatorio(int v[], int ini, int fim, MetricasQuick *m) {
    if (ini >= fim) return;

    int p = particao_aleatoria_inteiros(v, ini, fim, m);

    if (p - 1 > ini) quick_sort_aleatorio(v, ini, p - 1, m);
    if (p + 1 < fim) quick_sort_aleatorio(v, p + 1, fim, m);
}

/* ---- Quick Sort para jogadores ---- */

/* Troca a estrutura inteira e conta a troca. */
static void trocar_jogadores(Jogador *a, Jogador *b, MetricasQuick *m) {
    Jogador t = *a;
    *a = *b;
    *b = t;
    m->trocas++;
}

/* Particao (Lomuto) em v[ini..fim] usando o criterio 'cmp'. O pivo e o
   ultimo elemento. Como todos os criterios desempatam por id, nao existem
   dois jogadores equivalentes: a ordem final e unica. */
int particao_jogadores(Jogador v[], int ini, int fim, Comparador cmp, MetricasQuick *m) {
    Jogador pivo = v[fim];
    int i = ini;

    for (int j = ini; j < fim; j++) {
        m->comparacoes++;
        if (cmp(&v[j], &pivo) < 0) {
            if (i != j) trocar_jogadores(&v[i], &v[j], m);
            i++;
        }
    }
    if (i != fim) trocar_jogadores(&v[i], &v[fim], m);
    return i;
}

/* Quick Sort para jogadores. Se 'aleatorio' for 1, sorteia o pivo dentro
   do subintervalo atual e o leva para a ultima posicao antes de particionar. */
void quick_sort_jogadores(Jogador v[], int ini, int fim, Comparador cmp,
                          int aleatorio, MetricasQuick *m) {
    if (ini >= fim) return;

    if (aleatorio) {
        int p = escolher_pivo_aleatorio(ini, fim);
        if (p != fim) trocar_jogadores(&v[p], &v[fim], m);
    }

    int pos = particao_jogadores(v, ini, fim, cmp, m);

    if (pos - 1 > ini) quick_sort_jogadores(v, ini, pos - 1, cmp, aleatorio, m);
    if (pos + 1 < fim) quick_sort_jogadores(v, pos + 1, fim, cmp, aleatorio, m);
}

/* ---- Insertion Sort para jogadores com criterio escolhido ---- */
/* (a funcao da Questao 2 continua intacta e fixa em "nome") */

Metricas insertion_sort_jogadores_cmp(Jogador v[], int n, Comparador cmp) {
    Metricas m = {0, 0};

    for (int i = 1; i < n; i++) {
        Jogador chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            m.comparacoes++;
            if (cmp(&v[j], &chave) > 0) {
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

/* ---- Criterios de jogadores disponiveis na central (todos com desempate por id) ---- */

static int cmp_pontuacao_decr(const Jogador *a, const Jogador *b) {
    int r = cmp_int(b->pontuacao, a->pontuacao);
    return (r != 0) ? r : cmp_int(a->id, b->id);
}

/* Adaptador: o Merge Sort generico (Questao 6) recebe void*, entao o
   criterio escolhido e consultado por esta funcao. */
static Comparador g_criterio_atual = NULL;

static int cmp_criterio_gen(const void *a, const void *b) {
    return g_criterio_atual((const Jogador *)a, (const Jogador *)b);
}

/* ---- Dados da central ---- */

static int      g_n = 0;                 /* quantidade de elementos carregados */
static int      g_orig_int[MAXD];        /* entrada ORIGINAL (nunca ordenada) */
static Jogador  g_orig_jog[MAXD];
static int      g_saida_int[MAXD];       /* copia de trabalho */
static Jogador  g_saida_jog[MAXD];
static int      g_ref_int[MAXD];         /* saida do 1o algoritmo, p/ comparar */
static Jogador  g_ref_jog[MAXD];
static int      g_usado[MAXD];

static const char *NOMES_GERADOS[] = {
    "Ana", "Bruno", "Carlos", "Davi", "Elisa", "Fabio", "Gabi", "Hugo"
};
#define QTD_NOMES 8

/* Relatorio comparavel entre todos os algoritmos. */
typedef struct {
    long comparacoes;
    long trocas;
    long deslocamentos;      /* Insertion Sort */
    long copias;             /* Merge Sort (copias para o auxiliar) */
} Relatorio;

enum { ALG_INSERTION = 1, ALG_BUBBLE, ALG_MERGE, ALG_QUICK_FIXO, ALG_QUICK_ALEATORIO };
#define QTD_ALG 5

static const char *NOME_ALG[QTD_ALG + 1] = {
    "", "Insertion Sort", "Bubble Sort", "Merge Sort",
    "Quick Sort (pivo fixo)", "Quick Sort (pivo aleatorio)"
};

/* ---- Geracao e carga ---- */

/* Gera n elementos. 'disposicao' vale para os numeros:
   1 = aleatorio, 2 = ja ordenado, 3 = ordem inversa.
   Os jogadores sao sempre sorteados (ids unicos, nomes repetidos). */
static void gerar_dados(int n, int disposicao) {
    g_n = n;

    for (int i = 0; i < n; i++) g_orig_int[i] = rand() % 1000;

    if (disposicao != 1) {
        MetricasMerge mm = {0, 0};
        merge_sort_inteiros(g_orig_int, n, &mm);          /* deixa crescente */
        if (disposicao == 3) {
            for (int a = 0, b = n - 1; a < b; a++, b--) {
                int t = g_orig_int[a]; g_orig_int[a] = g_orig_int[b]; g_orig_int[b] = t;
            }
        }
    }

    /* ids unicos embaralhados (Fisher-Yates) */
    for (int i = 0; i < n; i++) g_usado[i] = 1000 + i;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = g_usado[i]; g_usado[i] = g_usado[j]; g_usado[j] = t;
    }
    for (int i = 0; i < n; i++) {
        g_orig_jog[i].id = g_usado[i];
        strcpy(g_orig_jog[i].nome, NOMES_GERADOS[rand() % QTD_NOMES]);
        g_orig_jog[i].pontuacao = rand() % 1000;
        g_orig_jog[i].vida = rand() % 101;
    }
}

/* Carrega as mesmas entradas usadas nas opcoes 1 a 7. */
static void carregar_dados_central(void) {
    int base[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};
    g_n = N;
    memcpy(g_orig_int, base, sizeof(base));
    memcpy(g_orig_jog, DADOS_JOGADORES, sizeof(DADOS_JOGADORES));
}

/* ---- Validacao (para qualquer tamanho ate MAXD) ---- */

static int validar_final_inteiros(const int orig[], const int saida[], int n) {
    static int ref[MAXD];
    for (int i = 1; i < n; i++) {
        if (saida[i - 1] > saida[i]) return 0;
    }
    memcpy(ref, orig, (size_t)n * sizeof(int));
    qsort(ref, (size_t)n, sizeof(int), cmp_int_gen);       /* referencia independente */
    return memcmp(ref, saida, (size_t)n * sizeof(int)) == 0;
}

static int jogadores_iguais(const Jogador *a, const Jogador *b) {
    return a->id == b->id && strcmp(a->nome, b->nome) == 0 &&
           a->pontuacao == b->pontuacao && a->vida == b->vida;
}

static int validar_final_jogadores(const Jogador orig[], const Jogador saida[],
                                   int n, Comparador cmp) {
    static int usado[MAXD];

    for (int i = 1; i < n; i++) {
        if (cmp(&saida[i - 1], &saida[i]) > 0) return 0;
    }
    memset(usado, 0, (size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int k = 0; k < n; k++) {
            if (!usado[k] && jogadores_iguais(&orig[k], &saida[i])) {
                usado[k] = 1;
                achou = 1;
                break;
            }
        }
        if (!achou) return 0;
    }
    return 1;
}

/* ---- Execucao de UM algoritmo sobre uma COPIA da entrada original ----
   tipo: 1 = numeros, 2 = jogadores. O resultado fica em g_saida_*.
   Retorna 0 em sucesso e -1 se faltar memoria (Merge Sort). */
static int rodar(int tipo, int alg, Comparador cmp, Relatorio *r, int *valido) {
    memset(r, 0, sizeof(*r));

    if (tipo == 1) {
        memcpy(g_saida_int, g_orig_int, (size_t)g_n * sizeof(int));

        switch (alg) {
            case ALG_INSERTION: {
                Metricas mm = insertion_sort(g_saida_int, g_n);
                r->comparacoes = mm.comparacoes;
                r->deslocamentos = mm.deslocamentos;
                break;
            }
            case ALG_BUBBLE: {
                MetricasBubble mb = bubble_sort(g_saida_int, g_n);
                r->comparacoes = mb.comparacoes;
                r->trocas = mb.trocas;
                break;
            }
            case ALG_MERGE: {
                MetricasMerge mg = {0, 0};
                if (merge_sort_inteiros(g_saida_int, g_n, &mg) != 0) return -1;
                r->comparacoes = mg.comparacoes;
                r->copias = mg.copias;
                break;
            }
            case ALG_QUICK_FIXO: {
                MetricasQuick mq = {0, 0};
                quick_sort(g_saida_int, 0, g_n - 1, &mq);
                r->comparacoes = mq.comparacoes;
                r->trocas = mq.trocas;
                break;
            }
            case ALG_QUICK_ALEATORIO: {
                MetricasQuick mq = {0, 0};
                quick_sort_aleatorio(g_saida_int, 0, g_n - 1, &mq);
                r->comparacoes = mq.comparacoes;
                r->trocas = mq.trocas;
                break;
            }
        }
        *valido = validar_final_inteiros(g_orig_int, g_saida_int, g_n);
    } else {
        memcpy(g_saida_jog, g_orig_jog, (size_t)g_n * sizeof(Jogador));

        switch (alg) {
            case ALG_INSERTION: {
                Metricas mm = insertion_sort_jogadores_cmp(g_saida_jog, g_n, cmp);
                r->comparacoes = mm.comparacoes;
                r->deslocamentos = mm.deslocamentos;
                break;
            }
            case ALG_BUBBLE: {
                MetricasBubble mb = bubble_sort_jogadores(g_saida_jog, g_n, cmp);
                r->comparacoes = mb.comparacoes;
                r->trocas = mb.trocas;
                break;
            }
            case ALG_MERGE: {
                MetricasMerge mg = {0, 0};
                g_criterio_atual = cmp;
                if (merge_sort_jogadores(g_saida_jog, g_n, cmp_criterio_gen, &mg) != 0) return -1;
                r->comparacoes = mg.comparacoes;
                r->copias = mg.copias;
                break;
            }
            case ALG_QUICK_FIXO:
            case ALG_QUICK_ALEATORIO: {
                MetricasQuick mq = {0, 0};
                quick_sort_jogadores(g_saida_jog, 0, g_n - 1, cmp,
                                     alg == ALG_QUICK_ALEATORIO, &mq);
                r->comparacoes = mq.comparacoes;
                r->trocas = mq.trocas;
                break;
            }
        }
        *valido = validar_final_jogadores(g_orig_jog, g_saida_jog, g_n, cmp);
    }
    return 0;
}

/* ---- Interacao com o usuario ---- */

static int escolher_tipo(void) {
    int t;
    printf("Tipo de dado: 1 - Numeros | 2 - Jogadores: ");
    if (scanf("%d", &t) != 1 || (t != 1 && t != 2)) {
        printf("Tipo invalido.\n");
        return 0;
    }
    return t;
}

static int escolher_criterio(Comparador *cmp, const char **nome) {
    int c;
    printf("Criterio dos jogadores (todos desempatam por id):\n");
    printf("  1 - Nome (strcmp)\n");
    printf("  2 - Pontuacao decrescente\n");
    printf("  3 - Vida crescente\n");
    printf("  4 - Identificador crescente\n");
    printf("Criterio: ");
    if (scanf("%d", &c) != 1) return 0;
    switch (c) {
        case 1: *cmp = comparar_jogadores; *nome = "nome";                  return 1;
        case 2: *cmp = cmp_pontuacao_decr; *nome = "pontuacao decrescente"; return 1;
        case 3: *cmp = cmp_vida_cresc;     *nome = "vida crescente";        return 1;
        case 4: *cmp = cmp_id_cresc;       *nome = "id crescente";          return 1;
    }
    printf("Criterio invalido.\n");
    return 0;
}

static void executar_um_algoritmo(void) {
    if (g_n == 0) { printf("Nenhum dado carregado. Gere ou carregue dados primeiro.\n"); return; }

    int tipo = escolher_tipo();
    if (!tipo) return;

    Comparador cmp = NULL;
    const char *nome_criterio = "";
    if (tipo == 2 && !escolher_criterio(&cmp, &nome_criterio)) return;

    printf("Algoritmo: ");
    for (int a = 1; a <= QTD_ALG; a++) printf("%d - %s%s", a, NOME_ALG[a], a < QTD_ALG ? " | " : "\n");
    printf("Opcao: ");
    int alg;
    if (scanf("%d", &alg) != 1 || alg < 1 || alg > QTD_ALG) { printf("Algoritmo invalido.\n"); return; }

    printf("\n");
    if (g_n <= 20) {
        if (tipo == 1) imprimir("Original", g_orig_int, g_n);
        else imprimir_jogadores("Original:", g_orig_jog, g_n);
    }

    Relatorio r; int valido;
    if (rodar(tipo, alg, cmp, &r, &valido) != 0) {
        printf("Erro: falha ao alocar memoria auxiliar.\n");
        return;
    }

    if (g_n <= 20) {
        if (tipo == 1) imprimir("Ordenado", g_saida_int, g_n);
        else imprimir_jogadores("Ordenado:", g_saida_jog, g_n);
    }
    printf("\n%s | %d elementos%s%s\n", NOME_ALG[alg], g_n,
           tipo == 2 ? " | criterio: " : "", nome_criterio);
    printf("Comparacoes: %ld | Trocas: %ld | Deslocamentos: %ld | Copias aux: %ld\n",
           r.comparacoes, r.trocas, r.deslocamentos, r.copias);
    printf("Validacao: %s\n", valido ? "OK" : "FALHOU");
}

/* Executa TODOS os algoritmos sobre a mesma entrada original e imprime
   o relatorio final. */
static void relatorio_final(void) {
    if (g_n == 0) { printf("Nenhum dado carregado. Gere ou carregue dados primeiro.\n"); return; }

    int tipo = escolher_tipo();
    if (!tipo) return;

    Comparador cmp = NULL;
    const char *nome_criterio = "";
    if (tipo == 2 && !escolher_criterio(&cmp, &nome_criterio)) return;

    printf("\n===== RELATORIO FINAL =====\n");
    printf("Entrada: %d %s%s%s (a mesma para todos os algoritmos)\n\n", g_n,
           tipo == 1 ? "numeros" : "jogadores",
           tipo == 2 ? ", criterio: " : "", nome_criterio);
    printf("%-28s %12s %9s %14s %11s  %s\n",
           "Algoritmo", "Comparacoes", "Trocas", "Deslocamentos", "Copias aux", "Validacao");

    int todos_iguais = 1;

    for (int alg = 1; alg <= QTD_ALG; alg++) {
        Relatorio r; int valido;
        if (rodar(tipo, alg, cmp, &r, &valido) != 0) {
            printf("%-28s erro de memoria\n", NOME_ALG[alg]);
            continue;
        }
        printf("%-28s %12ld %9ld %14ld %11ld  %s\n", NOME_ALG[alg],
               r.comparacoes, r.trocas, r.deslocamentos, r.copias,
               valido ? "OK" : "FALHOU");

        /* Compara a saida de cada algoritmo com a do primeiro. */
        if (alg == 1) {
            if (tipo == 1) memcpy(g_ref_int, g_saida_int, (size_t)g_n * sizeof(int));
            else memcpy(g_ref_jog, g_saida_jog, (size_t)g_n * sizeof(Jogador));
        } else if (tipo == 1) {
            if (memcmp(g_ref_int, g_saida_int, (size_t)g_n * sizeof(int)) != 0) todos_iguais = 0;
        } else {
            for (int i = 0; i < g_n; i++)
                if (!jogadores_iguais(&g_ref_jog[i], &g_saida_jog[i])) { todos_iguais = 0; break; }
        }
    }

    printf("\nSaidas identicas entre os algoritmos: %s\n", todos_iguais ? "SIM" : "NAO");
    printf("Obs.: 'Deslocamentos' = Insertion Sort; 'Copias aux' = Merge Sort;\n");
    printf("      no Quick Sort, as trocas incluem a troca do pivo sorteado.\n");
}

void opcao_central_final(void) {
    int op;
    do {
        printf("\n--- CENTRAL FINAL (Questao 8) ---\n");
        if (g_n > 0) printf("Dados carregados: %d elementos\n", g_n);
        else         printf("Dados carregados: nenhum\n");
        printf("1 - Gerar dados aleatorios\n");
        printf("2 - Carregar dados da central (10 elementos)\n");
        printf("3 - Executar UM algoritmo sobre uma copia\n");
        printf("4 - Relatorio comparativo (todos os algoritmos)\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) return;
        printf("\n");

        switch (op) {
            case 1: {
                int n, disp;
                printf("Quantidade de elementos (1 a %d): ", MAXD);
                if (scanf("%d", &n) != 1 || n < 1 || n > MAXD) { printf("Quantidade invalida.\n"); break; }
                printf("Disposicao dos numeros: 1 - Aleatoria | 2 - Ja ordenada | 3 - Inversa: ");
                if (scanf("%d", &disp) != 1 || disp < 1 || disp > 3) { printf("Disposicao invalida.\n"); break; }
                gerar_dados(n, disp);
                printf("Dados gerados: %d numeros e %d jogadores.\n", n, n);
                break;
            }
            case 2:
                carregar_dados_central();
                printf("Dados da central carregados (%d elementos).\n", g_n);
                break;
            case 3: executar_um_algoritmo(); break;
            case 4: relatorio_final();       break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);
}

int main(void) {
    srand((unsigned)time(NULL));     /* gerador pseudoaleatorio inicializado UMA unica vez */

    int opcao;
    do {
        printf("\n=== CENTRAL DE ORDENACAO ===\n");
        printf("1 - Insertion Sort em numeros (Questao 1)\n");
        printf("2 - Insertion Sort em jogadores por nome (Questao 2)\n");
        printf("3 - Bubble Sort com parada antecipada (Questao 3)\n");
        printf("4 - Bubble Sort em jogadores por vida/id (Questao 4)\n");
        printf("5 - Intercalacao e divisao recursiva (Questao 5)\n");
        printf("6 - Merge Sort em numeros e jogadores (Questao 6)\n");
        printf("7 - Particao e Quick Sort (Questao 7)\n");
        printf("8 - Quick Sort aleatorio e central final (Questao 8)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        printf("\n");

        switch (opcao) {
            case 1: opcao_inteiros();         break;
            case 2: opcao_jogadores();        break;
            case 3: opcao_bubble();           break;
            case 4: opcao_bubble_jogadores(); break;
            case 5: opcao_merge_base();       break;
            case 6: opcao_merge_sort();       break;
            case 7: opcao_quick_sort();       break;
            case 8: opcao_central_final();    break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}