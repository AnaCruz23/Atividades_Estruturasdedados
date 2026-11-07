#include <stdio.h>

#define N 10

typedef struct {
    long comparacoes;
    long deslocamentos;
} Metricas;

/* Insere v[pos] no prefixo já ordenado v[0..pos-1]. */
void inserir_em_prefixo(int v[], int pos, Metricas *m) {
    int chave = v[pos];          /* guarda o valor a inserir */
    int j = pos - 1;

    while (j >= 0) {             /* respeita o limite inferior */
        m->comparacoes++;
        if (v[j] > chave) {
            v[j + 1] = v[j];     /* desloca sem perder o elemento */
            m->deslocamentos++;
            j--;
        } else {
            break;               /* achou a posição */
        }
    }
    v[j + 1] = chave;            /* coloca o valor na posição correta */
}

/* Generaliza a inserção para o vetor inteiro. */
Metricas insertion_sort(int v[], int n) {
    Metricas m = {0, 0};
    for (int i = 1; i < n; i++) {
        inserir_em_prefixo(v, i, &m);
    }
    return m;
}

/* Validação: ordenado e com os mesmos elementos (soma preservada). */
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

int main(void) {
    /* Demonstração: inserir um valor em um prefixo ordenado */
    int prefixo[5] = {2, 5, 8, 11, 6};     /* prefixo {2,5,8,11} + novo valor 6 */
    Metricas mp = {0, 0};
    imprimir("Antes da insercao ", prefixo, 5);
    inserir_em_prefixo(prefixo, 4, &mp);
    imprimir("Depois da insercao", prefixo, 5);
    printf("Comparacoes: %ld | Deslocamentos: %ld\n\n", mp.comparacoes, mp.deslocamentos);

    /* Ordenação completa sobre uma cópia da entrada original */
    int original[N] = {42, 7, 19, 88, 7, 3, 56, 31, 64, 10};
    int copia[N];
    memcpy(copia, original, sizeof(original));

    imprimir("Original", original, N);
    Metricas m = insertion_sort(copia, N);
    imprimir("Ordenado", copia, N);

    printf("Comparacoes: %ld | Deslocamentos: %ld\n", m.comparacoes, m.deslocamentos);
    printf("Validacao: %s\n", validar(original, copia, N) ? "OK" : "FALHOU");
    return 0;
}