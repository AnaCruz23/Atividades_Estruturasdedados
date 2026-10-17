// Fatorial Iterativo - O(n)
#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar as métricas de execução
typedef struct {
    long long acessos;
    long long comparacoes;
    long long chamadas_recursivas;
} Contadores;

void zerar_contadores(Contadores *c) {
    c->acessos = 0;
    c->comparacoes = 0;
    c->chamadas_recursivas = 0;
}

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

bool esta_ordenado(int vetor[], int tamanho, Contadores *c) {
    for (int i = 0; i < tamanho - 1; i++) {
        c->acessos += 2;
        c->comparacoes++;
        if (vetor[i] > vetor[i + 1]) {
            return false;
        }
    }
    return true;
}

int busca_binaria(int vetor[], int tamanho, int alvo, Contadores *c) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        c->acessos++;
        int valor_meio = vetor[meio];

        c->comparacoes++;
        if (valor_meio == alvo) {
            return meio;
        }

        c->comparacoes++;
        if (valor_meio < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

int busca_linear(int vetor[], int tamanho, int alvo, Contadores *c) {
    for (int i = 0; i < tamanho; i++) {
        c->acessos++;
        c->comparacoes++;
        if (vetor[i] == alvo) {
            return i; // Primeira posição encontrada
        }
    }
    return -1; // Não encontrado
}
// Função auxiliar para imprimir os resultados comparativos lado a lado
void testar_e_comparar(const char *label, int vetor[], int n, int alvo) {
    Contadores c_lin, c_bin;
    zerar_contadores(&c_lin);
    zerar_contadores(&c_bin);

    int pos_lin = busca_linear(vetor, n, alvo, &c_lin);
    int pos_bin = busca_binaria(vetor, n, alvo, &c_bin);

    printf("Testando [%s] (Alvo: %d)\n", label, alvo);
    printf("  -> Linear : Pos = %2d | Comp = %2lld | Acessos = %2lld\n", 
           pos_lin, c_lin.comparacoes, c_lin.acessos);
    printf("  -> Binaria: Pos = %2d | Comp = %2lld | Acessos = %2lld\n\n", 
           pos_bin, c_bin.comparacoes, c_bin.acessos);
}

long long fatorial_iterativo(int n, Contadores *c) {
    long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        c->comparacoes++;
        resultado *= i;
    }
    c->comparacoes++; // Comparação final do loop
    return resultado;
}

// Fatorial Recursivo - O(n)
long long fatorial_recursivo(int n, Contadores *c) {
    
    c->chamadas_recursivas++;
    
    // CASO-BASE: N <= 1
    c->comparacoes++;
    if (n <= 1) {
        return 1;
    }
    
    // PASSO RECURSIVO: n * fatorial(n - 1)
    return n * fatorial_recursivo(n - 1, c);
}

// ============================================================================
// 2. FUNÇÃO EM VETOR: SOMA DOS ELEMENTOS (Iterativo vs Recursivo)
// ============================================================================

// Soma Iterativa - O(n)
int soma_vetor_iterativa(int vetor[], int tamanho, Contadores *c) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        c->comparacoes++;
        c->acessos++;
        soma += vetor[i];
    }
    c->comparacoes++; // Comparação final do loop
    return soma;
}

// Soma Recursiva - O(n)
// Processa do índice 0 até (tamanho - 1) de forma segura
int soma_vetor_recursiva(int vetor[], int tamanho, int indice, Contadores *c) {
    c->chamadas_recursivas++;
    
    // CASO-BASE: alcançou o fim do vetor (índice fora do limite)
    c->comparacoes++;
    if (indice >= tamanho || indice < 0) {
        return 0;
    }
    
    c->acessos++;
    // PASSO RECURSIVO: elemento_atual + soma(restante_do_vetor)
    return vetor[indice] + soma_vetor_recursiva(vetor, tamanho, indice + 1, c);
}

// ============================================================================
// EXPERIMENTO 1: BUSCA LINEAR E BINÁRIA ITERATIVA
// ============================================================================
int busca_linear(int vetor[], int tamanho, int alvo, Contadores *c) {
    for (int i = 0; i < tamanho; i++) {
        c->acessos++;
        c->comparacoes++;
        if (vetor[i] == alvo) return i;
    }
    return -1;
}

int busca_binaria_iterativa(int vetor[], int tamanho, int alvo, Contadores *c) {
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        c->acessos++;
        int valor_meio = vetor[meio];
        c->comparacoes++;
        if (valor_meio == alvo) return meio;
        
        c->comparacoes++;
        if (valor_meio < alvo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ============================================================================
// EXPERIMENTO 2: RECURSÃO SIMPLES (FATORIAL E SOMA DE VETOR)
// ============================================================================
long long fatorial_recursivo(int n, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (n <= 1) return 1; // Caso-base
    return n * fatorial_recursivo(n - 1, c);
}

int soma_vetor_recursiva(int vetor[], int tamanho, int indice, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    if (indice >= tamanho || indice < 0) return 0; // Caso-base seguro
    c->acessos++;
    return vetor[indice] + soma_vetor_recursiva(vetor, tamanho, indice + 1, c);
}

// ============================================================================
// EXPERIMENTO 3: RECURSÃO RAMIFICADA vs RECURSÃO LOGARÍTMICA
// ============================================================================

/**
 * Fibonacci Ingênuo (Recursão Ramificada - 2 chamadas por nó)
 * Complexidade de Chamadas: O(2^n)
 */
long long fibonacci_ramificado(int n, Contadores *c) {
    c->chamadas_recursivas++;
    c->comparacoes++;
    
    // Casos-base indispensáveis para interromper a ramificação
    if (n <= 0) return 0;
    c->comparacoes++;
    if (n == 1) return 1;

    // Duas chamadas por execução!
    return fibonacci_ramificado(n - 1, c) + fibonacci_ramificado(n - 2, c);
}

/**
 * Busca Binária Recursiva (Recursão Logarítmica - 1 chamada por nível)
 * Complexidade de Chamadas: O(log n)
 */
int busca_binaria_recursiva(int vetor[], int inicio, int fim, int alvo, Contadores *c) {
    c->chamadas_recursivas++;

    // Caso-base 1: Elemento não encontrado (intervalo vazio)
    c->comparacoes++;
    if (inicio > fim) {
        return -1;
    }

    // Cálculo seguro do meio
    int meio = inicio + (fim - inicio) / 2;

    c->acessos++;
    int valor_meio = vetor[meio];

    // Caso-base 2: Elemento encontrado
    c->comparacoes++;
    if (valor_meio == alvo) {
        return meio;
    }

    // Passo recursivo: Apenas UMA das metades é chamada
    c->comparacoes++;
    if (valor_meio < alvo) {
        return busca_binaria_recursiva(vetor, meio + 1, fim, alvo, c);
    } else {
        return busca_binaria_recursiva(vetor, inicio, meio - 1, alvo, c);
    }
}

// ============================================================================
// PROCEDIMENTOS DO MENU INTERATIVO
// ============================================================================

void executar_exp1() {
    int v[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 10, alvo = 70;
    Contadores c_lin, c_bin;
    zerar_contadores(&c_lin); zerar_contadores(&c_bin);

    busca_linear(v, n, alvo, &c_lin);
    busca_binaria_iterativa(v, n, alvo, &c_bin);

    printf("\n=== EXPERIMENTO 1: BUSCA LINEAR vs BINÁRIA ITERATIVA ===\n");
    printf("Procurando alvo %d em vetor ordenado de tamanho %d:\n", alvo, n);
    printf("Busca Linear  -> Comparaçoes: %lld | Acessos: %lld\n", c_lin.comparacoes, c_lin.acessos);
    printf("Busca Binária -> Comparaçoes: %lld | Acessos: %lld\n", c_bin.comparacoes, c_bin.acessos);
}

void executar_exp2() {
    int v[] = {5, 10, 15, 20, 25};
    Contadores c_fat, c_soma;
    zerar_contadores(&c_fat); zerar_contadores(&c_soma);

    long long res_fat = fatorial_recursivo(5, &c_fat);
    int res_soma = soma_vetor_recursiva(v, 5, 0, &c_soma);

    printf("\n=== EXPERIMENTO 2: RECURSÃO SIMPLES ===\n");
    printf("Fatorial de 5 = %lld (Chamadas Recursivas: %lld)\n", res_fat, c_fat.chamadas_recursivas);
    printf("Soma do vetor = %d   (Chamadas Recursivas: %lld)\n", res_soma, c_soma.chamadas_recursivas);
}

void executar_exp3() {
    printf("\n=== EXPERIMENTO 3: RECURSÃO RAMIFICADA vs LOGARÍTMICA ===\n");
    
    // 1. Fibonacci Ramificado (Entrada LIMITADA a N <= 30 para evitar travamentos)
    int n_fib;
    printf("Digite um valor para o Fibonacci (Recomendado entre 5 e 30): ");
    if (scanf("%d", &n_fib) != 1) return;

    if (n_fib > 35) {
        printf("[ALERTA] Valor limitado a 35 para evitar estouro de tempo/memória devido ao O(2^n)!\n");
        n_fib = 35;
    }

    Contadores c_fib;
    zerar_contadores(&c_fib);
    long long res_fib = fibonacci_ramificado(n_fib, &c_fib);

    printf("\n[Fibonacci Ramificado - O(2^n)]\n");
    printf("  Resultado Fib(%d)     : %lld\n", n_fib, res_fib);
    printf("  Chamadas Recursivas  : %lld  <-- CRESCIMENTO EXPONENCIAL!\n", c_fib.chamadas_recursivas);

    // 2. Busca Binária Recursiva
    int v_grande[1024];
    for (int i = 0; i < 1024; i++) v_grande[i] = i * 2; // Vetor ordenado de 1024 elementos

    Contadores c_bin_rec;
    zerar_contadores(&c_bin_rec);
    int alvo = 1500;
    int pos = busca_binaria_recursiva(v_grande, 0, 1023, alvo, &c_bin_rec);

    printf("\n[Busca Binária Recursiva - O(log n)]\n");
    printf("  Tamanho do Vetor (N) : 1024 elementos\n");
    printf("  Alvo Procurado       : %d\n", alvo);
    printf("  Posicao Retornada    : %d\n", pos);
    printf("  Chamadas Recursivas  : %lld  <-- APENAS log2(1024) + 1!\n", c_bin_rec.chamadas_recursivas);
}

int main() {

    int opcao;

    do {
        printf("\n======================================================================\n");
        printf("       PAINEL DO LABORATÓRIO DE ALGORITMOS E ESTRUTURA DE DADOS       \n");
        printf("======================================================================\n");
        printf("1. Experimento 1: Busca Linear vs. Busca Binaria (Iterativa)\n");
        printf("2. Experimento 2: Recursão Simples (Fatorial e Soma)\n");
        printf("3. Experimento 3: Recursão Ramificada (Fibonacci) vs Logarítmica (Busca Binária)\n");
        printf("0. Sair do Laboratório\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                executar_exp1();
                break;
            case 2:
                executar_exp2();
                break;
            case 3:
                executar_exp3();
                break;
            case 0:
                printf("\nEncerrando o laboratório... Até a próxima aula!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    printf("======================================================================\n");
    printf("   LABORATÓRIO DE ALGORITMOS: BUSCA LINEAR O(n) vs BUSCA BINÁRIA O(log n) \n");
    printf("======================================================================\n\n");

    // ------------------------------------------------------------------
    // PARTE 1: Testes em Vetor ORDENADO (Comparação Direta de Custos)
    // ------------------------------------------------------------------
    int v_ordenado[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n_ord = sizeof(v_ordenado) / sizeof(v_ordenado[0]);

    printf("--- DEMONSTRAÇÃO 1: Vetor Ordenado (N = %d) ---\n", n_ord);
    
    // Requisito: Testar início, meio, fim e valor ausente
    testar_e_comparar("Elemento no Inicio", v_ordenado, n_ord, 10);
    testar_e_comparar("Elemento no Meio  ", v_ordenado, n_ord, 50);
    testar_e_comparar("Elemento no Fim   ", v_ordenado, n_ord, 100);
    testar_e_comparar("Elemento Ausente  ", v_ordenado, n_ord, 45);

    // ------------------------------------------------------------------
    // PARTE 2: Demonstração da FALHA da Busca Binária em Vetor DESORDENADO
    // ------------------------------------------------------------------
    printf("----------------------------------------------------------------------\n");
    printf("--- DEMONSTRAÇÃO 2: Vetor NÃO Ordenado (Mostrando a Falha Binária) ---\n");
    printf("----------------------------------------------------------------------\n");

    // O valor 25 está visivelmente no vetor (índice 2), mas a sequência não está ordenada
    int v_desordenado[] = {80, 10, 25, 90, 5, 40, 70};
    int n_des = sizeof(v_desordenado) / sizeof(v_desordenado[0]);
    int alvo_desordenado = 25;

    Contadores c_lin_des, c_bin_des;
    zerar_contadores(&c_lin_des);
    zerar_contadores(&c_bin_des);

    int pos_lin_err = busca_linear(v_desordenado, n_des, alvo_desordenado, &c_lin_des);
    int pos_bin_err = busca_binaria(v_desordenado, n_des, alvo_desordenado, &c_bin_des);

    printf("Vetor: {80, 10, 25, 90, 5, 40, 70}\n");
    printf("Procurando valor existente: %d\n\n", alvo_desordenado);
    
    printf("[Busca Linear]  -> Encontrou na posição: %d (CORRETO)\n", pos_lin_err);
    printf("[Busca Binária] -> Encontrou na posição: %d (INCORRETO/FALHA!)\n\n", pos_bin_err);

    printf("======================================================================\n");
    printf("RESUMO DAS PRÉ-CONDIÇÕES E CUSTOS:\n");
    printf("1. Busca Linear:\n");
    printf("   - Pré-condição: NENHUMA (funciona em dados desordenados/brutos).\n");
    printf("   - Custo: O(n) no pior caso (percorre o vetor inteiro).\n\n");
    printf("2. Busca Binária:\n");
    printf("   - Pré-condição: OBRIGATÓRIO estar ordenado.\n");
    printf("   - Custo: O(log n) no pior caso (divisão sucessiva do espaço).\n");
    printf("   - Alerta: Aplicá-la em dados não ordenados gera FALHAS SILENCIOSAS.\n");
    printf("======================================================================\n");


    int vetor[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91, 100, 115, 130, 148, 160};
    int n = sizeof(vetor) / sizeof(vetor[0]);

    Contadores c_ord, c_busca;
    zerar_contadores(&c_ord);
    zerar_contadores(&c_busca);

    printf("======================================================================\n");
    printf("         LABORATÓRIO DE ALGORITMOS: BUSCA BINÁRIA O(log n)           \n");
    printf("======================================================================\n");


    int alvo_presente = 56;
    printf(">>> TESTE 1: Valor Presente (%d) <<<\n", alvo_presente);
    int pos1 = busca_binaria(vetor, n, alvo_presente, &c_busca);
    printf("Posição Retornada : %d\n", pos1);
    printf("Comparações       : %lld\n", c_busca.comparacoes);
    printf("Acessos à Memória : %lld\n", c_busca.acessos);

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

    printf("======================================================================\n");
    printf("     LABORATÓRIO DE ALGORITMOS: RECURSÃO vs ITERAÇÃO                  \n");
    printf("======================================================================\n\n");

    // ------------------------------------------------------------------------
    // TESTE 1: Problema Numérico (Fatorial)
    // ------------------------------------------------------------------------
    int num = 5;
    Contadores c_fat_it, c_fat_rec;
    zerar_contadores(&c_fat_it);
    zerar_contadores(&c_fat_rec);

    long long res_fat_it = fatorial_iterativo(num, &c_fat_it);
    long long res_fat_rec = fatorial_recursivo(num, &c_fat_rec);

    printf(">>> DEMONSTRAÇÃO 1: Fatorial de N = %d <<<\n", num);
    printf("  [Iterativo] Resultado: %lld | Comparações: %lld | Chamadas: 1\n", 
           res_fat_it, c_fat_it.comparacoes);
    printf("  [Recursivo] Resultado: %lld | Comparações: %lld | Chamadas: %lld (Profundidade)\n\n", 
           res_fat_rec, c_fat_rec.comparacoes, c_fat_rec.chamadas_recursivas);

    // ------------------------------------------------------------------------
    // TESTE 2: Processamento de Vetor (Soma)
    // ------------------------------------------------------------------------

    Contadores c_soma_it, c_soma_rec;
    zerar_contadores(&c_soma_it);
    zerar_contadores(&c_soma_rec);

    int res_soma_it = soma_vetor_iterativa(vetor, n, &c_soma_it);
    int res_soma_rec = soma_vetor_recursiva(vetor, n, 0, &c_soma_rec);

    printf(">>> DEMONSTRAÇÃO 2: Soma de Vetor (N = %d elementos) <<<\n", n);
    printf("  [Iterativo] Resultado: %d | Acessos: %lld | Comparações: %lld | Chamadas: 1\n", 
           res_soma_it, c_soma_it.acessos, c_soma_it.comparacoes);
    printf("  [Recursivo] Resultado: %d | Acessos: %lld | Comparações: %lld | Chamadas: %lld (Profundidade)\n", 
           res_soma_rec, c_soma_rec.acessos, c_soma_rec.comparacoes, c_soma_rec.chamadas_recursivas);

    printf("\n======================================================================\n");
    printf("ANÁLISE COMPARATIVA:\n");
    printf("1. Correção dos Resultados: Ambas as abordagens geram os mesmos valores.\n");
    printf("2. Custo de Memória:\n");
    printf("   - Iterativo: Memória O(1) constante (usa apenas variáveis locais).\n");
    printf("   - Recursivo: Memória O(n) na Pilha de Execução (Stack Frames).\n");
    printf("3. Segurança do Limite: A verificação (indice >= tamanho) no caso-base\n");
    printf("   garante que a função nunca acesse memória fora do vetor.\n");
    printf("======================================================================\n");

    return 0;
}