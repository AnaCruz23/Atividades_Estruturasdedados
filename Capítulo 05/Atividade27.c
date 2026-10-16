#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para armazenar as métricas de execução
typedef struct {
    long long acessos;
    long long comparacoes;
} Contadores;

bool acesso_direto(int vetor[], int tamanho, int indice, int *valor_saida, Contadores *c) {
    // 1 comparação de validação de limite inferior
    c->comparacoes++;
    if (indice < 0) return false;

    // 1 comparação de validação de limite superior
    c->comparacoes++;
    if (indice >= tamanho) return false;

    // 1 acesso ao vetor na posição informada
    *valor_saida = vetor[indice];
    c->acessos++;

    return true;
}

int buscar_maior(int vetor[], int tamanho, Contadores *c) {
    if (tamanho <= 0) return -1;

    // Acesso inicial para definir o primeiro candidato a maior
    int maior = vetor[0];
    c->acessos++;

    // Percorre todos os 'n' elementos
    for (int i = 0; i < tamanho; i++) {
        // Acesso ao elemento atual
        c->acessos++;
        int elemento_atual = vetor[i];

        // Comparação para atualizar o maior elemento
        c->comparacoes++;
        if (elemento_atual > maior) {
            maior = elemento_atual;
        }
    }

    return maior;
}

void zerar_contadores(Contadores *c) {
    c->acessos = 0;
    c->comparacoes = 0;
}

/**
 * Encontra todos os pares distintos cuja soma é igual ao 'alvo'.
 * Para evitar pares duplicados e a combinação de um elemento consigo mesmo,
 * o laço interno (j) começa sempre em (i + 1).
 * Complexidade Esperada: O(n²)
 */
int buscar_pares_soma(int vetor[], int tamanho, int alvo, Contadores *c) {
    int total_pares = 0;

    // Primeiro laço: escolhe o primeiro elemento do par
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            
            // Acessos aos dois elementos para realizar a soma
            c->acessos += 2;
            int soma = vetor[i] + vetor[j];

            // Compara a soma obtida com o valor alvo
            c->comparacoes++;
            if (soma == alvo) {
                total_pares++;
            }
        }
    }

    return total_pares;
}

int main() {

    int tamanhos[] = {10, 1000, 100000};
    int num_testes = 3;
    int alvo_teste = 50;

    printf("======================================================================\n");
    printf("        LABORATÓRIO DE ALGORITMOS: ANÁLISE DE COMPLEXIDADE 0(1) e 0 (n) e 0 (n²)           \n");
    printf("======================================================================\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));

        // Preenche o vetor com valores arbitrários
        for (int i = 0; i < n; i++) {
            vetor[i] = i * 2;
        }

        Contadores c_acesso, c_busca;
        zerar_contadores(&c_acesso);
        zerar_contadores(&c_busca);

        // 1. Teste de Acesso Direto (Buscando o elemento do meio)
        int valor_res;
        int idx_teste = n / 2;
        acesso_direto(vetor, n, idx_teste, &valor_res, &c_acesso);

        // 2. Teste de Busca do Maior
        int maior_res = buscar_maior(vetor, n, &c_busca);
        Contadores c_pares;
        zerar_contadores(&c_pares);

        // Executa a busca de pares
        int pares_encontrados = buscar_pares_soma(vetor, n, alvo_teste, &c_pares);

        // Exibição dos resultados
        printf(">>> TAMANHO DO VETOR (N = %d) <<<\n", n);
        printf("[Acesso Direto - O(1)]   Acessos: %-6lld | Comparações: %-6lld | Total Op: %lld\n",
               c_acesso.acessos, c_acesso.comparacoes, c_acesso.acessos + c_acesso.comparacoes);
        printf("[Busca do Maior - O(n)]  Acessos: %-6lld | Comparações: %-6lld | Total Op: %lld\n",
               c_busca.acessos, c_busca.comparacoes, c_busca.acessos + c_busca.comparacoes);
        printf("Pares Encontrados : %d\n", pares_encontrados);
        printf("Acessos à Memória : %lld\n", c_pares.acessos);
        printf("Comparações (Alvo): %lld\n", c_pares.comparacoes);
        printf("Total de Operações: %lld\n", c_pares.acessos + c_pares.comparacoes);
        printf("----------------------------------------------------------------------\n\n");


        free(vetor);
        (void)maior_res; // evita warning de variável não usada
    }

    return 0;
}